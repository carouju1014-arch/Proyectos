/*******************************************
* Fecha: 07/10/2025
* Autor: Carolina Ujueta
* Materia: Sistemas Operativos
* Tema: Uso de la función FORK()
* Duplicidad de procesos
*******************************************/

#include <unistd.h>   // Para fork(), pipe(), read(), write(), close()
#include <stdio.h>    
#include <stdlib.h>   // Para exit(), EXIT_FAILURE
#include <string.h>  

int main (int argc, char *argv[]) {

    // Mensaje inicial del proceso principal
    printf("==> Inicio del proceso main o proceso principal <==\n\n");

    int pipefd[2];            // Arreglo con dos descriptores de archivo: [0] lectura, [1] escritura
    pid_t procesoHIJO_PID;    // Variable para almacenar el PID del proceso hijo

    // Creación del pipe (tubería)
    // Un pipe es un canal de comunicación unidireccional entre procesos.
    if (pipe(pipefd) == -1) {
        perror("PIPE");
        exit(EXIT_FAILURE);
    }

    // Creación del proceso hijo
    procesoHIJO_PID = fork();

    if (procesoHIJO_PID == -1) {
        perror("FORK");
        exit(EXIT_FAILURE);
    }

    // Proceso hijo
    if (procesoHIJO_PID == 0) {

        // Cierra el extremo de escritura del pipe, ya que solo va a leer
        close(pipefd[1]);
        char mensaje[100];
        int lecturaBYTES;

        // Lee el mensaje enviado por el proceso padre
        lecturaBYTES = read(pipefd[0], mensaje, sizeof(mensaje));

        if (lecturaBYTES == -1) {
            perror("LECTURA!!");
            exit(EXIT_FAILURE);
        }

        // Imprime el mensaje recibido desde el pipe
        // "%.*s" imprime solo la cantidad de bytes leídos
        printf("\t Proceso HIJO: Recibe mensaje del PADRE => %.*s \n", lecturaBYTES, mensaje);

        // Cierra el extremo de lectura del pipe
        close(pipefd[0]);
    } 
    // Proceso padre
    else {
        // Cierra el extremo de lectura del pipe, ya que solo escribirá
        close(pipefd[0]);

        char mensajeP[] = "Holi, bienvenido a OP";  // Mensaje que enviará al hijo
        int escribirBYTES;

        // Envía el mensaje al proceso hijo a través del pipe
        escribirBYTES = write(pipefd[1], mensajeP, strlen(mensajeP));

        if (escribirBYTES == -1) {
            perror("ESCRITURA");
            exit(EXIT_FAILURE);
        }

        // Cierra el extremo de escritura del pipe
        close(pipefd[1]);
    }

    /**************************************************************
    * Este programa demuestra comunicación entre procesos (IPC)
    * mediante un pipe. El proceso padre envía un mensaje, y el 
    * proceso hijo lo recibe.
    **************************************************************/

    return 0;
}
