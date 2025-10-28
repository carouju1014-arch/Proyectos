/*
 ============================================================================
 Nombre:       Carolina Ujueta
 Profesor:     John Corredor
 Universidad:  Pontificia Universidad Javeriana
 Asignatura:   Sistemas Operativos
 ============================================================================
 Objetivo del challenge:
    Implementar un programa en C que utiliza la sincronización de hilos 
    mediante variables de condición (pthread_cond_t) y mutex (pthread_mutex_t).

    El objetivo es coordinar dos hilos:
    - Uno asigna un nuevo valor a una variable compartida (`valor`).
    - El otro espera la notificación de que el valor ha sido modificado
      antes de imprimirlo en pantalla.

    Este ejercicio permite comprender cómo los hilos pueden comunicarse
    entre sí.
 ============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <pthread.h>
#include <stdbool.h>

/*
 * Declaración e inicialización de las estructuras de sincronización:
 * - `varCondition`: variable de condición utilizada para despertar a un hilo
 *   cuando ocurre un evento específico.
 * - `mutexVar`: mutex que protege la variable compartida `valor` y el flag `notificar`.
 */
pthread_cond_t varCondition = PTHREAD_COND_INITIALIZER;
pthread_mutex_t mutexVar = PTHREAD_MUTEX_INITIALIZER;

/*
 * Variables globales compartidas:
 * - `valor`: representa un dato que será modificado por un hilo y leído por otro.
 * - `notificar`: indica si el hilo productor ya actualizó el valor.
 */
int valor = 100;
bool notificar = false;

/*
 ============================================================================
 Función: reportar
 Descripción:
    Este hilo espera (bloqueado) hasta que otro hilo indique que el valor 
    compartido ha sido modificado. Una vez recibe la notificación, 
    imprime el nuevo valor de la variable `valor`.
 ============================================================================
*/
void *reportar(void *nousado) {
    pthread_mutex_lock(&mutexVar);

    // Mientras la variable no haya sido actualizada, el hilo espera la señal
    while (!notificar)
        pthread_cond_wait(&varCondition, &mutexVar);

    pthread_mutex_unlock(&mutexVar);

    // Una vez notificado, imprime el valor actualizado
    printf("El valor es: %d\n", valor);
    return NULL;
}

/*
 ============================================================================
 Función: asignar
 Descripción:
    Este hilo actúa como productor. Cambia el valor compartido `valor` y luego
    notifica a los demás hilos que la actualización fue realizada, 
    utilizando `pthread_cond_signal`.
 ============================================================================
*/
void *asignar(void *nousado) {
    // Actualiza la variable compartida
    valor = 20;

    pthread_mutex_lock(&mutexVar);
    notificar = true;

    // Envía una señal a los hilos que esperan la condición
    pthread_cond_signal(&varCondition);

    pthread_mutex_unlock(&mutexVar);
    return NULL;
}

/*
 ============================================================================
 Función principal: main
 Descripción:
    Crea dos hilos:
    - El primero (`reporte`) que espera el aviso para imprimir el valor.
    - El segundo (`asigne`) que modifica el valor y envía la señal.

    Finalmente, el programa espera (join) a que ambos hilos finalicen 
    antes de terminar la ejecución.
 ============================================================================
*/
int main() {
    pthread_t reporte, asigne;

    // Creación de los hilos
    pthread_create(&reporte, NULL, reportar, NULL);
    pthread_create(&asigne, NULL, asignar, NULL);

    void *nousado;

    // Esperar a que ambos hilos terminen
    pthread_join(reporte, &nousado);
    pthread_join(asigne, &nousado);

    return 0;
}

/*
 ============================================================================
 Nota:
    Este programa utiliza correctamente las funciones de sincronización de pthreads:
    - `pthread_mutex_lock` / `pthread_mutex_unlock` para proteger acceso concurrente.
    - `pthread_cond_wait` / `pthread_cond_signal` para coordinar el flujo entre hilos.

    De esta forma, se evita el uso de pausas activas y se garantiza que el hilo
    "reportar" solo ejecute su tarea después de la actualización realizada por 
    el hilo "asignar".
 ============================================================================
*/
