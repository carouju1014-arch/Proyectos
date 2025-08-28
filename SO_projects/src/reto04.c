/*************************************************************
*            Pontificia Universidad Javeriana                *
*                                                            *
* Autor:     Carolina Ujueta Ricardo                         *
* Fecha:     26 de Agosto, 2025                              *
* Materia:   Sistemas Operativos                             *
* Profesor:  John Corredor                                   *
* Objetivo:  Challenge04                                     *
**************************************************************/
#include <stdio.h>
#include <stdlib.h>

int main(){
  int n, i, *ptr, sum = 0;                       // declara variables y suma
  printf("Enter number of elements: ");          // pide cantidad
  scanf("%d", &n);                               // lee n

  ptr = (int*)calloc(n, sizeof(int));            // reserva espacio inicializado en 0
  if(ptr == NULL){                               // comprueba error
    printf("Error! memory not allocated.");      // mensaje de error
    exit(0);                                     // termina el if
  }

  printf("Enter elements: ");                    // pide los elementos
  for(i = 0; i < n; ++i){                        // recorre n veces
    scanf("%d", ptr + i);                        // guarda en la posición i
    sum += *(ptr + i);                           // acumula en sum
  }

  printf("Sum = %d", sum);                       // imprime la suma
  free(ptr);                                     // libera memoria
  
  return 0;                                      // termina
}
