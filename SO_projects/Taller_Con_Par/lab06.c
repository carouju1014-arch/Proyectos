/*
 ============================================================================
 Nombre:       Carolina Ujueta
 Profesor:     John Corredor
 Universidad:  Pontificia Universidad Javeriana
 Asignatura:   Sistemas Operativos
 ============================================================================
 Objetivo del challenge:
    Implementar un programa en C que utiliza múltiples hilos (threads) 
    para calcular la suma de los cuadrados de los números del 1 al 20.

    Cada hilo calcula el cuadrado de un número específico y lo acumula 
    en una variable global compartida. Este ejercicio busca demostrar 
    el uso de la biblioteca pthread para la creación y sincronización 
    de hilos, evidenciando cómo el uso de exclusión mutua (mutex) 
    evita condiciones de carrera al acceder a recursos compartidos.
 ============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <pthread.h>

/*
 * Mutex para proteger el acceso concurrente a la variable compartida 'acumulado'.
 * Inicializado de forma estática mediante la macro PTHREAD_MUTEX_INITIALIZER.
 */
pthread_mutex_t acumuladoMutex = PTHREAD_MUTEX_INITIALIZER;

/*
 * Variable global compartida que almacenará la suma de los cuadrados.
 * Ahora estará protegida por el uso del mutex.
 */
int acumulado = 0;

/*
 ============================================================================
 Función: cuadrados
 Descripción:
    Calcula el cuadrado del número recibido como argumento (xi)
    y lo suma al acumulador global, utilizando un mutex para 
    evitar condiciones de carrera.
 ============================================================================
*/
void *cuadrados(void *x) {
    // Convierte el argumento genérico 'void*' al tipo entero
    int xi = (intptr_t)x;

    // Bloquea el mutex antes de modificar la variable compartida
    pthread_mutex_lock(&acumuladoMutex);

    // Sección crítica: actualización de la variable global 'acumulado'
    acumulado += xi * xi;

    // Libera el mutex para permitir que otros hilos accedan
    pthread_mutex_unlock(&acumuladoMutex);

    // El hilo no devuelve ningún resultado (NULL)
    return NULL;
}

/*
 ============================================================================
 Función principal: main
 Descripción:
    Crea 20 hilos, cada uno encargado de calcular el cuadrado de un número
    del 1 al 20. Luego, espera (join) a que todos los hilos terminen antes
    de mostrar el resultado final. El uso del mutex garantiza la coherencia
    de los datos en la variable compartida.
 ============================================================================
*/
int main() {

    pthread_t hilos[20]; // Arreglo que almacena los identificadores de los 20 hilos

    // Creación de los 20 hilos
    for(int i = 0; i < 20; i++) {
        pthread_create(&hilos[i], NULL, cuadrados, (void *)(intptr_t)(i + 1));
    }

    // Esperar a que todos los hilos finalicen su ejecución
    for(int i = 0; i < 20; i++) {
        pthread_join(hilos[i], NULL);
    }

    // Mostrar el resultado acumulado
    printf("Suma de cuadrados = %d\n", acumulado);

    return 0;
}

/*
 ============================================================================
 Nota:
    En esta versión, el acceso a la variable 'acumulado' está protegido 
    mediante un mutex, eliminando las condiciones de carrera presentes 
    en la versión anterior. Esto asegura que el resultado de la suma 
    de los cuadrados sea siempre el correcto y reproducible.
 ============================================================================
*/
