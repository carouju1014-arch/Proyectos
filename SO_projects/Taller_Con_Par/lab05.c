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
    en una variable global compartida. Este ejercicio busca evidenciar 
    el uso de la biblioteca pthread para la creación y sincronización 
    de hilos, así como los riesgos de acceder a variables compartidas 
    sin protección de exclusión mutua.
 ============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <pthread.h>

/*
 * Variable global compartida que almacenará la suma de los cuadrados.
 * Dado que todos los hilos acceden a 'acumulado', esto puede generar
 * condiciones de carrera si no se protege con un mutex.
 */
int acumulado = 0;

/*
 ============================================================================
 Función: cuadrados
 Descripción:
    Calcula el cuadrado del número recibido como argumento (xi)
    y lo suma al acumulador global.
 ============================================================================
*/
void *cuadrados(void *x) {
    // Convierte el argumento genérico 'void*' al tipo entero
    int xi = (intptr_t)x;

    // Sección no protegida (posible condición de carrera)
    acumulado += xi * xi;

    // El hilo no devuelve ningún resultado (NULL)
    return NULL;
}

/*
 ============================================================================
 Función principal: main
 Descripción:
    Crea 20 hilos, cada uno encargado de calcular el cuadrado de un número
    del 1 al 20. Luego, espera (join) a que todos los hilos terminen antes
    de mostrar el resultado final.
 ============================================================================
*/
int main() {

    pthread_t hilos[20]; // Arreglo que almacena los identificadores de los 20 hilos

    // Creación de 20 hilos
    for(int i = 0; i < 20; i++) {
        pthread_create(&hilos[i], NULL, cuadrados, (void *)(intptr_t)(i + 1));
    }

    // Esperar a que todos los hilos finalicen
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
    Dado que todos los hilos acceden simultáneamente a la variable 'acumulado',
    el resultado puede variar en diferentes ejecuciones debido a condiciones
    de carrera. Para garantizar un resultado correcto, se recomienda proteger
    la sección crítica usando un mutex.
 ============================================================================
*/
