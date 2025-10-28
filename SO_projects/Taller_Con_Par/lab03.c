/*
 ============================================================================
 Nombre:       Carolina Ujueta
 Profesor:     John Corredor
 Universidad:  Pontificia Universidad Javeriana
 Asignatura:   Programación Concurrente / Sistemas Operativos
 ============================================================================
 Objetivo del challenge:
    Implementar un programa en C que utilice hilos (threads), mutex y 
    variables de condición (pthread_cond) para coordinar la ejecución 
    entre dos funciones concurrentes: count01 y count02. 

    El objetivo es que ambos hilos incrementen de manera sincronizada 
    un contador global compartido, evitando condiciones de carrera y 
    controlando las secciones críticas donde el acceso al recurso debe 
    ser bloqueado temporalmente.

    Este challenge busca afianzar el entendimiento sobre el uso combinado 
    de mutex y variables de condición para la comunicación y sincronización 
    entre hilos, así como el manejo adecuado de bloqueos y señales en entornos 
    concurrentes.
 ============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

/*
 * Declaración e inicialización de los mutex y la variable de condición.
 * - count_mutex: protege el acceso al contador global.
 * - condition_mutex: controla la espera y señalización entre los hilos.
 * - condition_cond: variable de condición utilizada para despertar hilos en espera.
 */
pthread_mutex_t count_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t condition_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t condition_cond = PTHREAD_COND_INITIALIZER;

/*
 * Variable global compartida entre los hilos.
 * Será modificada por ambos hilos de forma sincronizada.
 */
int count = 0;

/*
 * Constantes de control que definen el comportamiento del contador.
 * COUNT_DONE  -> valor máximo al que el contador puede llegar.
 * COUNT_HALT1 -> umbral inferior del rango donde count01 se detiene.
 * COUNT_HALT2 -> umbral superior del rango donde count01 se detiene.
 */
#define COUNT_DONE 15
#define COUNT_HALT1 4
#define COUNT_HALT2 11

/*
 ============================================================================
 Función: count01
 Descripción:
    Esta función se ejecuta en un hilo separado. Su propósito es incrementar 
    el contador global 'count' mientras su valor NO se encuentre dentro del 
    rango COUNT_HALT1 - COUNT_HALT2. Si el contador se encuentra dentro de 
    ese rango, el hilo entra en espera (bloqueado) hasta recibir una señal 
    de otro hilo (count02).
 ============================================================================
*/
void *count01() {

    for(;;) { // Bucle infinito controlado por condición interna

        pthread_mutex_lock(&condition_mutex); // Bloquea el mutex de condición

        // Si el contador está dentro del rango de pausa, el hilo espera señal
        while(count >= COUNT_HALT1 && count <= COUNT_HALT2) {
            pthread_cond_wait(&condition_cond, &condition_mutex);
        }

        pthread_mutex_unlock(&condition_mutex); // Libera el mutex de condición

        // Sección crítica: incremento seguro del contador
        pthread_mutex_lock(&count_mutex);
        count++;
        printf("Counter value functionCount > 01 <==: %d\n", count);
        pthread_mutex_unlock(&count_mutex);

        // Si el contador alcanza el valor máximo, el hilo termina
        if(count > COUNT_DONE) return (NULL);
    }
}

/*
 ============================================================================
 Función: count02
 Descripción:
    Este hilo también incrementa el contador global 'count', pero además 
    envía señales (cond_signal) para despertar al hilo count01 cuando el 
    contador se encuentre fuera del rango COUNT_HALT1 - COUNT_HALT2.

    Es un ejemplo de comunicación entre hilos mediante variables de condición.
 ============================================================================
*/
void *count02() {

    for(;;) { // Bucle continuo

        pthread_mutex_lock(&condition_mutex); // Bloquea el mutex de condición

        // Si el contador está fuera del rango de pausa, envía señal
        if(count < COUNT_HALT1 || count > COUNT_HALT2) {
            pthread_cond_signal(&condition_cond);
        }

        pthread_mutex_unlock(&condition_mutex); // Libera el mutex de condición

        // Sección crítica: incremento seguro del contador
        pthread_mutex_lock(&count_mutex);
        count++;
        printf("Counter value functionCount ==> 02 <==: %d\n", count);
        pthread_mutex_unlock(&count_mutex);

        // Si se alcanzó el límite máximo, termina el hilo
        if(count >= COUNT_DONE) return (NULL);
    }
}

/*
 ============================================================================
 Función principal: main
 Descripción:
    Crea y ejecuta dos hilos (thread1 y thread2) asociados a las funciones 
    count01 y count02 respectivamente. Luego espera (join) a que ambos hilos 
    finalicen antes de terminar el programa principal.
 ============================================================================
*/
void main() {

    pthread_t thread1, thread2; // Identificadores de los dos hilos

    // Creación de los hilos
    pthread_create(&thread1, NULL, &count01, NULL);
    pthread_create(&thread2, NULL, &count02, NULL);

    // Espera a que ambos hilos finalicen su ejecución
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    // Finaliza el programa correctamente
    exit(0);
}
