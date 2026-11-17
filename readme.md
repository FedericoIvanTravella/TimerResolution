##
Este programa surgio porque estaba aburrido.
Pero, tiene un uso muy bueno, el cual en pocas palabras beneficia el "delay", es un programa chiquito que le pide a Windows que revise el reloj del sistema más seguido, cada 0.5 milisegundos en vez de cada 1 o 15.6 que es el valor por default del mismo windows.

La idea de fondo: Windows tiene un “reloj interno” que marca cuándo puede despertar programas, ejecutar temporizadores, o pasar de una tarea a otra. Por defecto ese reloj hace “tic” cada 15.6 ms para ahorrar energía. Cuando un programa necesita más precisión (juegos, audio, video), le pide a Windows un “tic” más rápido, normalmente de 1 ms. Si ningún programa lo pide, queda lento.

Mi programa hace ese pedido por vos, pero con el valor más fino que tu hardware soporta: 0.5 ms. Por eso tenés que dejarlo abierto: mientras está corriendo, Windows mantiene el “tic” rápido, y al cerrarlo vuelve al valor anterior.
##

Para que este funcione necesitas que en tu windows (preferentemente win 11) tengas en el registro el comando GlobalTimerResolutionRequests en un valor hexadecimal "1"
La ubicacion de donde debe estar este registro es "HKLM\SYSTEM\CurrentControlSet\Control\Session Manager\kernel" 
Si este registro no esta, apretas click derecho, crear valor dword 32bits y pones ahi los datos anteriores