/*************************************************************
*            Pontificia Universidad Javeriana                *
*                                                            *
* Autor:     Carolina Ujueta Ricardo                         *
* Fecha:     26 de Agosto, 2025                              *
* Materia:   Sistemas Operativos                             *
* Profesor:  John Corredor                                   *
* Objetivo:  Challenge05                                     *
**************************************************************/
#include <stdio.h>
#include <stdlib.h>

int main(){
    int *ptr;   // puntero a int
    int n1, n2; // tamaños inicial y nuevo

    printf("Enter size: ");    // pide al usuario el tamaño inicial
    scanf("%d", &n1);          // lee ese tamaño y lo guarda en n1

    ptr = malloc(n1 * sizeof *ptr); // reserva memoria para n1 enteros

    printf("Addresses of previously allocated memory: "); // mensaje
    for (int i = 0; i < n1; ++i) {          // recorre los n1 enteros
        printf("\n\np = %p\n", ptr + i);    // imprime dirección de cada posición
    }

    printf("Enter the new size: "); // pide el nuevo tamaño
    scanf("%d", &n2);               // lo guarda en n2

    ptr = realloc(ptr, n2 * sizeof *ptr); // cambia el bloque al nuevo tamaño

    printf("Addresses after realloc:\n");  // mensaje
    for (int i = 0; i < n2; ++i) {         // recorre los n2 enteros
        printf("\n\np = %p\n", ptr + i);   // imprime dirección de cada posición
    }

    free(ptr);   // libera la memoria reservada
    return 0;    // fin del programa
}
