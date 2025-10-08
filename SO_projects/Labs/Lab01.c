/****************************************
* Fecha: 07/10/2025
* Autor: Carolina Ujueta
* Materia: Sistemas Operativos
* Tema: Uso de la función FORK()
*****************************************/

#include <unistd.h>   // Librería que contiene la función fork() y getpid()
#include <stdio.h>  
#include <stdlib.h> 

int main (int argc, char *argv[]) {

    // Mensaje inicial indicando el comienzo del proceso principal (proceso padre original)
    printf("==> Inicio del proceso main o proceso principal <==\n\n");

    // Se crea un nuevo proceso con fork()
    // fork() devuelve:
    //  > 0  → Al proceso padre, con el PID del hijo.
    //  = 0  → Al proceso hijo, recién creado.
    //  < 0  → En caso de error.
    int processID = fork();

    // Condicional para diferenciar entre proceso padre e hijo
    if (processID > 0) {
        // Este bloque se ejecuta en el proceso padre
        printf("\t ==> Proceso Padre con ID %d \n", getpid());
    } 
    else {
        // Este bloque se ejecuta en el proceso hijo
        printf("\t ==> Proceso Hijo con ID %d \n", getpid());
    }
    printf("A partir de aqui es el proceso main o proceso principal \n");

    return 0;
  
  /**************************************************************
    * NOTA IMPORTANTE:
    * La salida puede aparecer en desorden debido a la concurrencia.
    * 
    * Cuando se ejecuta fork(), el proceso padre y el proceso hijo 
    * se ejecutan de manera casi simultánea e independiente.
    * 
    * El sistema operativo decide cuál proceso se ejecuta primero 
    * (planificador o scheduler). Por eso, los mensajes del padre 
    * y del hijo pueden mezclarse o aparecer en distinto orden 
    * cada vez que se ejecuta el programa.
    * 
    * Este comportamiento es completamente normal y esperado
    * en la ejecución concurrente de procesos.
    **************************************************************/
}
