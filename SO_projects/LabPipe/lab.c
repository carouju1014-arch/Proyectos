/**************************************************************************************
 * Fecha: 14 de octubre de 2025
 * Autora: Carolina Ujueta
 * Materia: Sistemas Operativos
 * Tema: Comunicación entre procesos con FIFO (Named Pipes)
 *
 * Nota:
 * El servidor debe ejecutarse antes que el cliente.
 **************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <errno.h>

#define FIFO_FILE "/tmp/fifo_twoway"

void reverse_string(char *str);

int main(void) {
    int fd;
    char readbuf[80];
    const char *end = "end";
    ssize_t nread;

    // Crea el FIFO si no existe (0640: lectura/escritura para el usuario, lectura para el grupo)
    if (mkfifo(FIFO_FILE, 0640) == -1 && errno != EEXIST) {
        perror("Error creando FIFO");
        exit(1);
    }

    // Abre el FIFO en modo lectura y escritura (evita que se bloquee esperando al cliente)
    fd = open(FIFO_FILE, O_RDWR);
    if (fd == -1) {
        perror("Error abriendo FIFO");
        exit(1);
    }

    // Ciclo principal: lee mensajes y responde
    while (1) {
        // Lee datos enviados desde el cliente
        nread = read(fd, readbuf, sizeof(readbuf) - 1);
        if (nread <= 0) continue;  // Si no se leyó nada, vuelve a intentar

        readbuf[nread] = '\0';  // Agrega terminador de cadena
        printf("Servidor: Recibido -> \"%s\"\n", readbuf);

        // Si el cliente envía "end", se cierra la comunicación
        if (strcmp(readbuf, end) == 0) {
            printf("Servidor: Finalizando comunicación.\n");
            close(fd);
            break;
        }

        // Invierte el mensaje recibido
        reverse_string(readbuf);

        // Muestra y envía la cadena invertida de regreso al cliente
        printf("Servidor: Enviando invertido -> \"%s\"\n", readbuf);
        write(fd, readbuf, strlen(readbuf));

        sleep(2); // Pausa breve para sincronizar lectura y escritura
    }

    return 0;
}

// Invierte una cadena de texto carácter por carácter
void reverse_string(char *str) {
    int i = 0, j = strlen(str) - 1;
    char temp;
    while (i < j) {
        temp = str[i];
        str[i] = str[j];
        str[j] = temp;
        i++;
        j--;
    }
}
