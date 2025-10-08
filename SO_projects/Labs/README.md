# Laboratorios en C – Sistemas Operativos

Esta carpeta contiene tres programas en C (`lab01.c`, `lab02.c`, `lab03.c`) como parte de los ejercicios de la materia de Sistemas Operativos.  
Cada laboratorio aborda diferentes aspectos del uso de la función `fork()` y la creación de procesos en un sistema operativo tipo Unix.

Estructura:

    lab01.c … lab03.c: código fuente de cada laboratorio, ubicados en el directorio raíz.
    Makefile: automatiza la compilación y limpieza de los ejecutables.
    README.md: documentación general del proyecto.

Descripción de los laboratorios:

    lab01.c: Muestra el uso básico de la función fork() y cómo se crean dos procesos (padre e hijo). 

    lab02.c: Demuestra la duplicidad de procesos al crear un hijo con fork(), mostrando cómo ambos 
             procesos ejecutan el mismo código y pueden imprimir resultados en desorden debido a la 
             concurrencia.

    lab03.c: Implementa la comunicación entre procesos mediante una tubería (pipe). El proceso padre 
             envía un mensaje y el proceso hijo lo recibe.

Uso del Makefile:

    Compilar todos los laboratorios: make
    Compilar uno a uno: make lab01
    Ejecutar un laboratorio: ./lab0*  (* es un número representativo del laboratorio)
    Limpiar ejecutables: make clean
