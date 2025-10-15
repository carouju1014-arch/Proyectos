/**************************************************************************************
 * Fecha: 14 de octubre de 2025
 * Autora: Carolina Ujueta
 * Materia: Sistemas Operativos
 * Tema: Comunicación entre procesos con FIFO (Named Pipes)
 *
 * Nota:
 * Cliente que se comunica con un servidor mediante una tubería con nombre.
 **************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

#define FIFO_FILE "/tmp/fifo_twoway"

int main(void) {
    int fd;                 // Descriptor del FIFO
    char buf[80];           // Buffer para enviar y recibir mensajes
    const char *end = "end"; // Palabra clave para finalizar la comunicación
    ssize_t nread;          // Bytes leídos desde el FIFO

    // Abre el FIFO (el servidor debe haberlo creado antes)
    // Se usa O_RDWR para evitar bloqueo si el otro extremo aún no está listo
    fd = open(FIFO_FILE, O_RDWR);
    if (fd == -1) {
        perror("Error abriendo FIFO");
        exit(1);
    }

    // Ciclo principal: enviar cadenas hasta escribir "end"
    while (1) {
        printf("Cliente: Ingresa una cadena: ");
        if (!fgets(buf, sizeof(buf), stdin)) {
            printf("\nCliente: fin de entrada detectado.\n");
            break;
        }

        // Elimina el salto de línea al final de la cadena (si lo hay)
        size_t len = strlen(buf);
        if (len > 0 && buf[len - 1] == '\n') {
            buf[len - 1] = '\0';
            len--;
        }

        // Evita enviar cadenas vacías
        if (len == 0) {
            printf("Cliente: (entrada vacía) no se envía nada.\n");
            continue;
        }

        // Envía la cadena al servidor a través del FIFO
        write(fd, buf, len);
        printf("Cliente: Enviado -> \"%s\"\n", buf);

        // Si se envía la palabra "end", se cierra el FIFO y se termina el programa
        if (strcmp(buf, end) == 0) {
            printf("Cliente: Finalizando comunicación.\n");
            close(fd);
            break;
        }

        // Espera la respuesta del servidor (cadena invertida)
        nread = read(fd, buf, sizeof(buf) - 1);
        if (nread <= 0) {
            printf("Cliente: No se recibió respuesta del servidor.\n");
            continue;
        }

        buf[nread] = '\0'; // Termina la cadena correctamente
        printf("Cliente: Respuesta del servidor -> \"%s\"\n", buf);
    }

    return 0;
}
