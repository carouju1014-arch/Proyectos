/*************************************************************
*            Pontificia Universidad Javeriana                *
*                                                            *
* Autor:     Carolina Ujueta Ricardo                         *
* Fecha:     26 de Agosto, 2025                              *
* Materia:   Sistemas Operativos                             *
* Profesor:  John Corredor                                   *
* Objetivo:  Challenge03                                     *
**************************************************************/
#include <stdio.h>
#include <stdlib.h>

int main(){
  int *ptr;                           // declara enteros y puntero
  ptr = malloc(15 * sizeof(*ptr));    // reserva espacio para 15 enteros

  if(ptr != NULL){                    // verifica que malloc no devolvió NULL
    *(ptr + 5) = 480;                  // asigna 480 en la posición 6 (índice 5)
    printf("ptr[5] = %d\n", ptr[5]);   // Esto se añadio para comprobar
  }

  free(ptr);                           // libera la memoria reservada
  return 0;                            // termina el programa correctamente
}
