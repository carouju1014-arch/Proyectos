/*************************************************************
*            Pontificia Universidad Javeriana                *
*                                                            *
* Autor:     Carolina Ujueta Ricardo                         *
* Fecha:     26 de Agosto, 2025                              *
* Materia:   Sistemas Operativos                             *
* Profesor:  John Corredor                                   *
* Objetivo:  Challenge01                                     *
**************************************************************/

/* En el codigo de la presentacion (es el que se encuentra a comentado) 
   No se le asignaba memoria a los punteros, provocando que no dieran respuesta.
int main(){
  char *p;
  char *q = NULL;
  printf("Address of p = %s\n",p);
  
  strcpy(p,"Hello, I'm the best in Operating Systems!!!");
  printf("%s\n",p);
  printf("About to copy \"Goodbye\" to q\n");
  strcpy(q,"Goodbye");
  printf("String copied\n");
  printf("%s\n",q);
  
  return 0;
}
*/

//Codigo corregido
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char *p; // puntero a char
    char *q; // segundo puntero a char

    p = malloc(strlen("Hello, I'm the best in Operating Systems!!!") + 1); // reserva espacio para la cadena y '\0'
    q = malloc(strlen("Goodbye") + 1);                                      // reserva espacio para "Goodbye" y '\0'

    printf("Address of p = %p\n", p); // imprime la dirección almacenada en p

    strcpy(p, "Hello, I'm the best in Operating Systems!!!"); // copia la cadena en p
    printf("%s\n", p);                                        // imprime el contenido de p

    printf("About to copy \"Goodbye\" to q\n"); // Mensaje descriptivo de que Goodbye se copiara a q
    strcpy(q, "Goodbye");                       // copia la cadena en q
    printf("String copied\n");                  // Mensaje descriptivo de que ya se copio
    printf("%s\n", q);                          // imprime el contenido de q

    free(p); // libera la memoria de p
    free(q); // libera la memoria de q

    return 0; // termina sin error
} // fin de main
