/*
 ============================================================================
 Nombre:       Carolina Ujueta
 Profesor:     John Corredor
 Universidad:  Pontificia Universidad Javeriana
 Asignatura:   Sistemas Operativos
 ============================================================================
 Objetivo del challenge:
    Implementar un programa en C que cree varios hilos (threads) 
    utilizando la biblioteca pthread. Cada hilo ejecuta una tarea 
    simulada mediante un bucle largo, representando un trabajo pesado 
    (job). 
    
    El programa busca ilustrar la creación, ejecución y sincronización 
    de múltiples hilos en paralelo, así como la utilización de 
    pthread_join() para esperar la finalización de todos los hilos 
    antes de que termine el programa principal.
 ============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h> // Para la función strerror()

// Declaración de un arreglo de 3 identificadores de hilos
pthread_t tid[3];

// Variable global que actúa como contador de trabajos
int counter;

// Mutex para proteger el acceso a la variable 'counter'
pthread_mutex_t lock;

/*
 ============================================================================
 Función: compute
 Descripción:
    Esta función será ejecutada por cada hilo. 
    Incrementa un contador global de forma segura, imprime mensajes que 
    indican el inicio y fin del "trabajo" y ejecuta un bucle largo para 
    simular procesamiento.
 ============================================================================
*/
void *compute(void *arg)
{
    unsigned long i = 0;

    // Sección crítica: incremento del contador global
    pthread_mutex_lock(&lock);
    counter += 1;
    printf("\nJob %d has started\n", counter);
    pthread_mutex_unlock(&lock);

    // Simulación de una tarea pesada mediante un bucle extenso
    for(i = 0; i < 0xFFFFFFFF; i++);

    // Mensaje indicando que el trabajo terminó
    printf("\nJob %d has finished\n", counter);

    return NULL;
}

/*
 ============================================================================
 Función principal: main
 Descripción:
    Crea tres hilos, maneja posibles errores de creación y 
    espera a que todos finalicen antes de salir del programa.
 ============================================================================
*/
int main(void)
{
    int i = 0;
    int error;

    // Bucle para crear tres hilos
    while(i < 3)
    {
        error = pthread_create(&(tid[i]), NULL, &compute, NULL);
        // Verifica si ocurrió un error al crear el hilo
        if (error != 0)
            printf("\nThread can't be created: [%s]", strerror(error));
        i++;
    }

    // Espera a que los tres hilos terminen su ejecución
    pthread_join(tid[0], NULL);
    pthread_join(tid[1], NULL);
    pthread_join(tid[2], NULL);

    // Destruye el mutex al finalizar
    pthread_mutex_destroy(&lock);

    return 0;
}
