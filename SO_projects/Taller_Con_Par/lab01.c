/*
 ============================================================================
 Nombre:       Carolina Ujueta
 Profesor:     John Corredor
 Universidad:  Pontificia Universidad Javeriana
 Asignatura:   Sistemas Operativos
 ============================================================================
 Objetivo del challenge:
    Implementar un programa en C que demuestre la creación básica de hilos 
    (threads) utilizando la librería pthread. Cada hilo ejecuta una función 
    que imprime un mensaje, mostrando el funcionamiento concurrente de tareas 
    dentro de un mismo proceso. El ejercicio busca comprender la sintaxis, 
    estructura y comportamiento de los hilos en C.
 ============================================================================
*/

#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>

/*
 * Función que será ejecutada por cada hilo.
 * Recibe un puntero genérico (void *ptr), el cual se espera que apunte 
 * a una cadena de caracteres (char *) que representa el mensaje a imprimir.
 */
void *print_message_function(void *ptr){
	char *message;                // Declaración de puntero a cadena
	message = (char *) ptr;       // Conversión del puntero genérico a tipo char*
	printf("%s \n", message);     // Imprime el mensaje recibido por el hilo
}
/*
 * Función principal del programa (punto de entrada).
 * Crea dos hilos independientes, cada uno con un mensaje distinto.
 */
void main(){
	pthread_t thread1, thread2;   // Identificadores (handles) de los dos hilos
	char *message1 = "Thread 1";  // Mensaje asignado al hilo 1
	char *message2 = "Thread 2";  // Mensaje asignado al hilo 2
	int iret1, iret2;             // Variables para guardar el valor de retorno de pthread_create

	/* 
	 * Creación de hilos independientes:
	 * Cada hilo ejecuta la función 'print_message_function' con su respectivo mensaje.
	 * El primer parámetro es la referencia al hilo,
	 * el segundo son los atributos (NULL -> valores por defecto),
	 * el tercero es la función que ejecutará,
	 * y el cuarto el argumento que recibe la función.
	 */
	iret1 = pthread_create(&thread1, NULL, print_message_function, (void*) message1);
	iret2 = pthread_create(&thread2, NULL, print_message_function, (void*) message2);

	/*
	 * Los valores devueltos por pthread_create indican si la creación fue exitosa:
	 * 0  -> éxito
	 * !=0 -> error
	 */
	printf("Thread 1 returns: %d\n", iret1);
	printf("Thread 2 returns: %d\n", iret2);

	/*
	 * En este punto, ambos hilos se están ejecutando concurrentemente.
	 * Sin embargo, el uso de 'exit(0)' termina el proceso principal inmediatamente,
	 * lo que puede causar que los hilos no alcancen a ejecutar por completo
	 * su función antes de finalizar el programa.
	 * Para asegurar su ejecución completa, normalmente se usaría pthread_join.
	 */
	exit(0); // Termina el programa principal (y todos los hilos junto con él)
}
