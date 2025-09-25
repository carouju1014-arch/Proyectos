/**************************************************************************************
 * Fecha: 23 de Septiembre, 2025
 * Autor: Carolina Ujueta Ricardo
 * Materia: Sistemas Operativos
 * Tema: Concurrencia
 * Objetivo: Hacer una metodología para la implementación de la multiplicación de matrices.
***************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include "modulo.h"

/* Se declaran variables globales para medición de tiempo*/
struct timeval ini, fin;

/* Función para inicializar el conteo de tiempo */
void InicioMuestra(){
	gettimeofday(&ini, (void *)0);
}

/* Función para finalizar el conteo de tiempo y calcular la diferencia */
void FinMuestra(){
	gettimeofday(&fin, (void *)0);
	fin.tv_usec -= ini.tv_usec;
	fin.tv_sec  -= ini.tv_sec;
	double tiempo = (double) (fin.tv_sec*1000000 + fin.tv_usec);
	printf("%9.0f \n", tiempo);
}

/* Función para inicializar matrices con valores calculados
   m1 recibe valores de la forma i*2.3 + 1.3
   m2 recibe valores de la forma i*2.3 */
void iniMatriz(int n, double *m1, double *m2){
   	for(int i=0; i<n*n; i++){
	        m1[i] = i*2.3 + 1.3;
	        m2[i] = i*2.3;
	}
};

/* Función para imprimir matrices 
   Solo imprime en pantalla si la dimensión de la matriz es menor que 9 */
void imprMatrices(int n, double *matriz){
    if(n<9){
        printf("\n#######################################################\n");
   	for(int i=0; i<n*n; i++){
                if(i%n==0) printf("\n");
	        printf(" %f ", matriz[i]);
   }
    } else {
        printf("\n#######################################################\n");
    }
};

