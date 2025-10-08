/*******************************************
* Fecha: 07/10/2025
* Autor: Carolina Ujueta
* Materia: Sistemas Operativos
* Tema: Uso de la función FORK()
* Duplicidad de procesos
*******************************************/

#include <unistd.h>   // Para fork() y funciones relacionadas con procesos
#include <stdio.h> 
#include <stdlib.h> 

int main (int argc, char *argv[]) {

    // Mensaje inicial indicando el comienzo del proceso principal
    printf("==> Inicio del proceso main o proceso principal <==\n\n");

    // Se crea un nuevo proceso mediante fork()
    // - En el proceso hijo, fork() devuelve 0
    // - En el proceso padre, devuelve el PID del proceso hijo
    int processID = fork();

    // Diferenciamos entre proceso hijo y padre
    if (processID == 0) {
        printf("\t ==> Proceso Hijo recién creado \n");
    } 
    else {
        printf("\t ==> Proceso Padre \n");
    }

    // Ambos procesos ejecutan el resto del código de forma independiente
    printf("Imprimiendo ... \n");

    // Bucle de impresión, se ejecuta tanto por el padre como por el hijo
    for (int i = 0; i < 5; i++) {
        printf("\t\t == %d ==\n", i);
    }

    printf("Fin ... \n");

    /**************************************************************
    * NOTA IMPORTANTE:
    * En este programa, el proceso padre y el proceso hijo 
    * ejecutan el mismo bucle "for" de forma concurrente.
    *
    * Debido a que ambos procesos corren en paralelo, 
    * el sistema operativo (a través del planificador o scheduler)
    * decide en qué orden se ejecutan sus instrucciones. Por eso, 
    * las líneas de salida pueden aparecer mezcladas.
    *
    * Este fenómeno es conocido como "condición de carrera" 
    * (race condition) y es típico de la concurrencia entre procesos.
    **************************************************************/

    return 0;
}
