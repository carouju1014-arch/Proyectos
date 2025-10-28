/*********************************************************************************************
 * Pontificia Universidad Javeriana
 *
 * Autor:       Carolina Ujueta Ricardo
 * Materia:     Sistemas Operativos
 * Docente:     J. Corredor, PhD
 * Fecha:       27/10/2025
 * Tema:        POSIX para la creación de hilos concurrentes
 *
 * Descripción general:
 *     Programa en C que utiliza la biblioteca pthread para dividir el trabajo de búsqueda
 *     del valor máximo en un vector entre varios hilos. Cada hilo calcula el máximo parcial
 *     de su segmento y luego se combina el resultado final.
 *********************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

/*
 ============================================================================
 Estructura: argHilos
 Descripción:
    Define los parámetros que se pasarán a cada hilo, incluyendo el índice de
    inicio y fin del segmento que debe procesar, el puntero al vector original
    y la variable donde se almacenará el máximo parcial encontrado.

    Campos:
      - inicio: índice de inicio (incluido) del segmento que procesará el hilo.
      - fin: índice de fin (excluido) del segmento que procesará el hilo.
      - vector: puntero al arreglo completo de enteros sobre el que se busca el máximo.
      - maxparcial: entero donde el hilo almacenará el máximo encontrado en su segmento.
 ============================================================================
*/
struct argHilos {
    int inicio;
    int fin;
    int *vector;
    int maxparcial;
};

/* Alias tipo para facilitar la lectura: param_H es struct argHilos */
typedef struct argHilos param_H;

/*
 ============================================================================
 Función: buscarMax
 Descripción:
    Rutina que ejecutará cada hilo. Recibe como parámetro un puntero a una
    estructura 'param_H' (cast desde void*). Dentro:
      1. Inicializa 'maxparcial' con el primer elemento del subarreglo asignado.
      2. Recorre el segmento [inicio, fin) comparando y actualizando el máximo parcial.
      3. Almacena el máximo en el campo 'maxparcial' de la estructura, para que
         el hilo padre (o quien creó los hilos) pueda leer dicho resultado al hacer join.

 Notas de uso:
    - Se asume que 'inicio' y 'fin' están dentro de los límites del vector.
    - El criterio usado es: recorrer índices desde 'inicio' hasta 'fin-1'.
 ============================================================================
*/
void *buscarMax(void *parametro) {
    /* Cast del argumento genérico al tipo esperado */
    param_H *argumentos = (param_H *)parametro;

    /* Inicializar el máximo parcial con el primer elemento del segmento asignado.
       Esto evita usar un valor "sentinel" externo y permite manejar segmentos de tamaño >= 1. */
    argumentos->maxparcial = argumentos->vector[argumentos->inicio];

    /* Recorre el segmento asignado y actualiza el máximo parcial.
       Atención: el bucle debe iterar desde inicio hasta fin-1 (índices válidos). */
    for (int i = 0; i < argumentos->fin; i++) {
        if (argumentos->vector[i] > argumentos->maxparcial)
            argumentos->maxparcial = argumentos->vector[i];
    }

    /* Finaliza la ejecución del hilo. pthread_exit(0) devuelve código 0 al join.
       También podríamos usar 'return NULL;' — ambas son válidas en este contexto. */
    pthread_exit(0);
    return NULL; /* Línea inalcanzable pero presente por claridad; mantiene la firma void*. */
}

/*
 ============================================================================
 Función principal: main
 Descripción:
    - Valida argumentos de entrada.
    - Abre el fichero de entrada y lee:
        1) el tamaño 'n' del vector
        2) los n elementos enteros del vector
    - Solicita (por argumento) el número de hilos a utilizar (nhilos).
    - Llama a la función maximoValor(...) para repartir el trabajo entre hilos
      y obtener el máximo global.
    - Imprime el máximo y libera recursos.

 Notas sobre el formato del fichero de entrada:
    - Se espera que el primer número del fichero sea 'n' (cantidad de elementos).
    - A continuación deben venir 'n' enteros separados por espacios o saltos de línea.
    - Ejemplo de fichero:
         6
         3 12 7 9 21 4
 ============================================================================
*/
int main(int argc, char *argv[]) {
    FILE *fichero;    /* Puntero al fichero con los datos */
    int n, nhilos, i; /* n: tamaño del vector, nhilos: número de hilos, i: índice de bucle */
    int *vec;         /* Puntero al vector dinámico que contendrá los n enteros */
    int ret, maximo;  /* ret: valor de retorno de fscanf; maximo: resultado final */

    /* Verifica número de argumentos (programa espera: ejecutable archivo.txt nhilos) */
    if (argc != 3) {
        fprintf(stderr, "Error en número de argumentos\n");
        exit(-1);
    }

    /* Abre el fichero de lectura en modo texto */
    fichero = fopen(argv[1], "r");
    if (fichero == NULL) {
        perror("No se puede abrir el fichero");
        exit(-2);
    }

    /* Lee el primer entero: el tamaño del vector 'n' */
    ret = fscanf(fichero, "%d", &n);
    if (ret != 1) {
        fprintf(stderr, "No se puede leer el tamaño\n");
        exit(-3);
    }

    /* Convierte el segundo argumento (string) a entero: número de hilos */
    nhilos = atoi(argv[2]);

    /* Reserva dinámica del vector de tamaño n */
    vec = malloc(sizeof(int) * n);
    if (vec == NULL) { /* comprobación mínima de malloc */
        fprintf(stderr, "Error reservando memoria\n");
        fclose(fichero);
        exit(-4);
    }

    /* Lectura de los n elementos del fichero hacia el vector.
       Si ocurre un error de lectura, se informa y se liberan recursos. */
    for (i = 0; i != n; ++i) {
        ret = fscanf(fichero, "%d", &vec[i]);
        if (ret != 1) {
            fprintf(stderr, "No se puede leer el elemento número %d\n", i);
            fclose(fichero);
            free(vec);
        }
    }

    /*
     * Llamada a la función que reparte el vector entre hilos y calcula el máximo.
     * maximoValor debe:
     *   - dividir el vector en segmentos
     *   - lanzar 'nhilos' hilos que ejecuten buscarMax en cada segmento
     *   - esperar a que terminen (pthread_join)
     *   - combinar los máximos parciales en el máximo global
     */
  
    maximo = maximoValor(vec, n, nhilos);

    /* Imprime el máximo encontrado */
    printf("Máximo: %d\n", maximo);

    /* Cierra el fichero y libera la memoria dinámica */
    fclose(fichero);
    free(vec);
    return 0;
}
