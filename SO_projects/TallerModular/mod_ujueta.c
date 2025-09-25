/**************************************************************************************
 * Fecha: 23 de Septiembre, 2025
 * Autor: Carolina Ujueta Ricardo
 * Materia: Sistemas Operativos
 * Tema: Concurrencia
 * Objetivo: Hacer una metodología para la implementación de la multiplicación de matrices.
***************************************************************************************/

/*Bibliotecas incluidas para el funcionamiento del codigo*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include "modulo.h"

/*Declaracion de variables tipo puntero globales*/
double *mA, *mB, *mC;

/*Main, implementacion por medio de modulo.c y modulo.h*/
int main(int argc, char *argv[]) {

/*Si se es menor o igual a 2, se imprime que los argumentos son incorrectos*/
    if(argc<=2){
        printf("Numero argumentos incorrectos\n");
        printf("\n\t $ejecutable.exe DIM \n");
        return -1;
    }
/*Declaramos N que seria el tamaño de nuestras matrices*/
    int N = (int) atof(argv[1]);
    if(N<=0){
        printf("\n Valores deben ser mayor que cero\n");
        return -1;
    };
/*Inicializamos nuestras matrices por medio de malloc (Asignarles espacio) y calloc (Asignarles espacio y 
a su vez inicializarlo en 0)*/
    mA = (double *) malloc(N*N*sizeof(double));
    mB = (double *) malloc(N*N*sizeof(double));
    mC = (double *) calloc(N*N,sizeof(double));

	/* Se inicializan las 2 matrices */
	iniMatriz(N, mA, mB);
	
	/*Se imprimen nuestras matrices*/
	imprMatrices(N, mA);
	imprMatrices(N, mB);

/*Operamos nuestras matrices para generar la multiplicacion, se recorre por medio de dos fors,
filas y columnas por cada una, se multiplican y se suman al resultado final MC por medio de otro for*/
     for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            double sumaTemp, *pA, *pB;
            sumaTemp = 0.0;
            pA = mA + i*N;
            pB = mB + j;
            for(int k=0; k<N; k++, pA++, pB+=N){
                sumaTemp += *pA * *pB;
            }
            mC[j+i*N] = sumaTemp;
        }
    }

	/*Imprimimos la matriz resultado*/
	imprMatrices(N, mC);

        printf("\n\tFin del programa.............!\n");
	/*Se libera memoria entregando recursos al sistema*/
        free(mA);
        free(mB);
        free(mC);
        return 0;
}
