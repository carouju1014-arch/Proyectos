/*
 ============================================================================
 Nombre:       Carolina Ujueta
 Profesor:     John Corredor
 Universidad:  Pontificia Universidad Javeriana
 Asignatura:   Programación Concurrente / Sistemas Operativos
 ============================================================================
 Objetivo del challenge:
    Implementar un programa en C que demuestra el uso de variables de
    condición (pthread_cond_t) y mutex (pthread_mutex_t) para la sincronización 
    entre hilos.

    El programa tiene dos hilos:
    - Uno que modifica el valor de una variable compartida.
    - Otro que debe esperar hasta que dicha modificación ocurra para
      reportar el nuevo valor.
    
    Se incluyen secciones comentadas donde se utilizaría la sincronización
    real mediante `pthread_cond_wait` y `pthread_cond_signal`, para mostrar
    cómo se coordina la ejecución de los hilos y se evita el acceso no
    sincronizado a los datos compartidos.
 ============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <pthread.h>
#include <stdbool.h>

/*
 * Declaración de las variables de sincronización:
 * - `varCondition`: variable de condición utilizada para notificar a los hilos.
 * - `mutexVar`: mutex que protege el acceso a la variable compartida.
 */
pthread_cond_t varCondition = PTHREAD_COND_INITIALIZER;
pthread_mutex_t mutexVar = PTHREAD_MUTEX_INITIALIZER;

/*
 * Variable global compartida.
 * En este ejemplo, representa un valor que un hilo asigna y otro reporta.
 */
int valor = 100;
bool notificar = false;

/*
 ============================================================================
 Función: reportar
 Descripción:
    Esta función representa el hilo encargado de mostrar el valor de la
    variable compartida `valor`. En una implementación completa, este hilo
    esperaría la señal de que el valor fue modificado antes de imprimirlo.
 ============================================================================
*/
void *reportar(void *nousado) {
    /*
    pthread_mutex_lock(&mutexVar);
    while(!notificar)
        pthread_cond_wait(&varCondition, &mutexVar);
    pthread_mutex_unlock(&mutexVar);
    */

    // Imprime el valor actual (sin esperar la señal en esta versión)
    printf("El valor es: %d\n", valor);

    return NULL;
}

/*
 ============================================================================
 Función: asignar
 Descripción:
    Este hilo cambia el valor compartido `valor`. 
    En la versión comentada, notifica al otro hilo que la actualización ocurrió.
 ============================================================================
*/
void *asignar(void *nousado) {
    // Cambia el valor de la variable compartida
    valor = 20;

    /*
    pthread_mutex_lock(&mutexVar);
    notificar = true;
    pthread_cond_signal(&varCondition);
    pthread_mutex_unlock(&mutexVar);
    */

    return NULL;
}

/*
 ============================================================================
 Función principal: main
 Descripción:
    Crea dos hilos:
    - El primero (`reporte`) que debe mostrar el valor.
    - El segundo (`asigne`) que modifica el valor.
    Luego espera a que ambos hilos finalicen su ejecución.
 ============================================================================
*/
int main() {
    pthread_t reporte, asigne;

    // Creación de los dos hilos
    pthread_create(&reporte, NULL, reportar, NULL);
    pthread_create(&asigne, NULL, asignar, NULL);

    void *nousado;

    // Espera a que ambos hilos terminen
    pthread_join(reporte, &nousado);
    pthread_join(asigne, &nousado);

    return 0;
}

/*
 ============================================================================
 Nota:
    En esta versión, las funciones de sincronización (condiciones y mutex)
    se encuentran comentadas para fines ilustrativos. Si se activaran, se
    garantizaría que el hilo `reportar` solo imprima el valor una vez que
    `asignar` haya modificado correctamente la variable `valor`.
 ============================================================================
*/
