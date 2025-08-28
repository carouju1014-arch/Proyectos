/*************************************************************
*            Pontificia Universidad Javeriana                *
*                                                            *
* Autor:     Carolina Ujueta Ricardo                         *
* Fecha:     26 de Agosto, 2025                              *
* Materia:   Sistemas Operativos                             *
* Profesor:  John Corredor                                   *
* Objetivo:  Challenge02                                     *
**************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
  char *q = NULL; // puntero a char, inicializado a NULL
  printf("Requesting space for \"Goodbye\"\n"); //mensaje descriptivo sobre el proceso a realizar
  q = (char*)malloc(strlen("Goodbye")+1); // reserva 7+1 bytes para "Goodbye" y '\0'

  if(!q){ // verifica si malloc falló
    perror("Failed to allocate space because"); // imprime la causa
    exit(1); // termina el programa con código de error
  }

  printf("About to copy \"Goodbye\" to q at address %p\n", q); // muestra la dirección contenida en q
  strcpy(q,"Goodbye"); // copia la cadena en la memoria apuntada por q
  printf("String copied\n"); // confirma la copia
  printf("%s\n",q); // imprime el contenido de q

  free(q); // libera la memoria asignada a q
  return 0; // fin normal del programa
}
