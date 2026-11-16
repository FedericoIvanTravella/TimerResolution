// El programa debe quedar abierto: al cerrarlo, Windows vuelve a la resolucion original(1.000 ms).

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>

typedef LONG (NTAPI *NtQueryTimerResolution_t)(PULONG MinimumResolution,
                                               PULONG MaximumResolution,
                                               PULONG CurrentResolution);
typedef LONG (NTAPI *NtSetTimerResolution_t)(ULONG DesiredResolution,
                                             BOOLEAN SetResolution,
                                             PULONG CurrentResolution);

int main(int argc, char **argv)
{
    HMODULE ntdll = GetModuleHandleA("ntdll.dll");
    if (!ntdll) {
        printf("No se pudo cargar ntdll.dll\n");
        return 1;
    }

    NtQueryTimerResolution_t NtQueryTimerResolution =
        (NtQueryTimerResolution_t)GetProcAddress(ntdll, "NtQueryTimerResolution");
    NtSetTimerResolution_t NtSetTimerResolution =
        (NtSetTimerResolution_t)GetProcAddress(ntdll, "NtSetTimerResolution");

    if (!NtQueryTimerResolution || !NtSetTimerResolution) {
        printf("No se encontraron las funciones Nt*TimerResolution\n");
        return 1;
    }

    ULONG minRes = 0, maxRes = 0, curRes = 0;
    NtQueryTimerResolution(&minRes, &maxRes, &curRes);

    // Unidades de 100 ns. "maxRes" es el valor mas fino que soporta el sistema
    // (normalmente 5000 = 0.5 ms).
    ULONG desired = 5000;
    if (argc > 1) desired = (ULONG)strtoul(argv[1], NULL, 10);

    printf("Minima (mas gruesa): %.4f ms\n", minRes / 10000.0);
    printf("Maxima (mas fina)  : %.4f ms\n", maxRes / 10000.0);
    printf("Actual             : %.4f ms\n", curRes / 10000.0);

    ULONG actual = 0;
    LONG status = NtSetTimerResolution(desired, TRUE, &actual);
    if (status != 0) {
        printf("NtSetTimerResolution fallo (0x%08lX)\n", (unsigned long)status);
        return 1;
    }

    NtQueryTimerResolution(&minRes, &maxRes, &curRes);
    printf("\nPedido : %.4f ms\n", desired / 10000.0);
    printf("Ahora  : %.4f ms\n", curRes / 10000.0);
    printf("\nDeja esta ventana abierta. Presiona Enter para salir y revertir.\n");

    getchar();

    NtSetTimerResolution(desired, FALSE, &actual);
    return 0;
}
