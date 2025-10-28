/*
 ============================================================================
 Nombre:       Carolina Ujueta
 Profesor:     John Corredor
 Universidad:  Pontificia Universidad Javeriana
 Asignatura:   Sistemas Operativos
 ============================================================================
 Objetivo del challenge:
    Implementar un programa en C que cree múltiples hilos (threads) usando la 
    librería pthread. Cada hilo imprime su número de creación y su ID, y 
    posteriormente incrementa un contador global compartido de manera segura 
    mediante el uso de un mutex.
    
    Este ejercicio tiene como propósito comprender los conceptos de 
    sincronización de hilos, acceso a memoria compartida y el uso de 
    mecanismos de exclusión mutua (mutex) para evitar condiciones de carrera.
 ============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

/*
 * Constante que define el número total de hilos que se crearán.
 * En este caso, se crearán 10 hilos concurrentes.
 */
#define NTHREADS 10

/*
 * Declaración e inicialización de un mutex global.
 * El mutex servirá para proteger la variable 'counter' 
 * cuando sea modificada por múltiples hilos simultáneamente.
 */
pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;

/*
 * Variable global compartida por todos los hilos.
 * Se incrementará dentro de cada hilo, protegida por el mutex.
 */
int counter = 0;

/*
 * Función que ejecutará cada hilo creado.
 * Recibe un puntero genérico 'arg' que se espera apunte a un entero
 * con el número del hilo.
 */
void *thread_function(void *arg) {
	int i = *(int *)(arg); // Se obtiene el número del hilo desde el argumento recibido

	// Se imprime el número del hilo y su ID interno asignado por pthread
	printf("Thread number: %d | Thread ID %ld\n", i, pthread_self());

	/*
	 * Sección crítica protegida por el mutex.
	 * Solo un hilo a la vez puede ejecutar el bloque entre lock y unlock,
	 * evitando así condiciones de carrera sobre 'counter'.
	 */
	pthread_mutex_lock(&mutex1);   // Bloquea el acceso al recurso compartido
	counter++;                     // Incrementa el contador global
	pthread_mutex_unlock(&mutex1); // Libera el acceso al recurso
}

/*
 * Función principal del programa (punto de entrada).
 * Crea múltiples hilos y muestra el valor final del contador.
 */
void main() {
	pthread_t thread_id[NTHREADS]; // Arreglo para almacenar los identificadores de los hilos
	int i, j;

	/*
	 * Bucle que crea NTHREADS hilos.
	 * Cada hilo ejecuta la función 'thread_function' y recibe la dirección de 'i' como argumento.
	 *
	 * NOTA IMPORTANTE:
	 * Pasar la dirección de 'i' (&i) a todos los hilos puede causar resultados inesperados,
	 * ya que 'i' cambia en cada iteración del for y todos los hilos comparten la misma dirección.
	 * Sin embargo, el código se deja intacto tal como fue solicitado.
	 */
	for(i = 0; i < NTHREADS; i++)
	{
		pthread_create(&thread_id[i], NULL, thread_function, &i);
	}

	/*
	 * Se imprime el valor final del contador global.
  */
	printf("Final counter value: %d\n", counter);
}
