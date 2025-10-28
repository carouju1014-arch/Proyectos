/*
 ============================================================================
 Nombre:       Carolina Ujueta
 Profesor:     John Corredor
 Universidad:  Pontificia Universidad Javeriana
 Asignatura:   Sistemas Operativos
 ============================================================================
 Objetivo del challenge:
    Implementar un programa en C que cree múltiples hilos (threads) utilizando 
    la librería pthread. Cada hilo imprime su número de creación y su ID, y 
    posteriormente incrementa un contador global compartido de manera segura 
    mediante el uso de un mutex.

    Este ejercicio tiene como propósito comprender los conceptos de 
    sincronización de hilos, acceso concurrente a memoria compartida y el uso 
    de mecanismos de exclusión mutua (mutex) para evitar condiciones de carrera.
 ============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

/*
 * Constante que define el número total de hilos que se crearán.
 * En este caso, se crearán 10 hilos que se ejecutarán de manera concurrente.
 */
#define NTHREADS 10

/*
 * Declaración e inicialización de un mutex global.
 * El mutex se utiliza para proteger la variable 'counter' 
 * cuando es modificada por múltiples hilos simultáneamente.
 */
pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;

/*
 * Variable global compartida por todos los hilos.
 * Se incrementará dentro de cada hilo, protegida por el mutex.
 */
int counter = 0;

/*
 ============================================================================
 Función: thread_function
 Descripción:
    Esta función es ejecutada por cada hilo creado. 
    Recibe un puntero genérico 'arg' que apunta a un entero con el número 
    correspondiente al hilo. 
    Cada hilo imprime su número e ID, y luego incrementa el contador global.
 ============================================================================
*/
void *thread_function(void *arg) {
    int i = *(int *)(arg); // Se obtiene el número del hilo desde el argumento recibido

    // Se imprime el número del hilo y su ID interno asignado por pthread
    printf("Thread number: %d | Thread ID %ld\n", i, pthread_self());

    /*
     * Sección crítica protegida por el mutex.
     * Solo un hilo a la vez puede ejecutar las líneas entre lock y unlock,
     * evitando así condiciones de carrera sobre 'counter'.
     */
    pthread_mutex_lock(&mutex1);   // Bloquea el acceso al recurso compartido
    counter++;                     // Incrementa el contador global
    pthread_mutex_unlock(&mutex1); // Libera el acceso al recurso
}

/*
 ============================================================================
 Función principal: main
 Descripción:
    Es el punto de entrada del programa. Crea múltiples hilos (NTHREADS),
    cada uno ejecutando 'thread_function'. 
    Al finalizar, imprime el valor acumulado del contador global.
 ============================================================================
*/
void main() {
    pthread_t thread_id[NTHREADS]; // Arreglo que almacena los identificadores de los hilos
    int i, j;

    /*
     * Bucle que crea NTHREADS hilos.
     * Cada hilo ejecuta la función 'thread_function' y recibe como argumento
     * la dirección de la variable 'i'.
     *
     * NOTA IMPORTANTE:
     * Pasar la dirección de 'i' (&i) a todos los hilos puede producir 
     * comportamientos inesperados, ya que 'i' cambia en cada iteración 
     * y todos los hilos comparten la misma dirección de memoria.
     * Aun así, se mantiene el código original según las especificaciones del reto.
     */
    for (i = 0; i < NTHREADS; i++) {
        pthread_create(&thread_id[i], NULL, thread_function, &i);
    }

    /*
     * Finalmente, se imprime el valor del contador global.
     * En teoría, si todos los hilos incrementan correctamente el contador,
     * el resultado esperado sería igual al número total de hilos (NTHREADS).
     */
    printf("Final counter value: %d\n", counter);
}

