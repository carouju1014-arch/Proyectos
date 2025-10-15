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
   int fd;                // descriptor del FIFO
   char readbuf[80];      // buffer para recibir y enviar mensajes
   char end[10];          // palabra clave "end"
   int to_end;            // bandera para verificar fin
   int read_bytes;        // cantidad de bytes leídos

   // Crear el FIFO si no existe (0640: lectura/escritura para usuario, lectura para grupo)
   mkfifo(FIFO_FILE, S_IFIFO | 0640);

   // Copiar palabra de cierre
   strcpy(end, "end");

   // Abrir el FIFO en modo lectura/escritura (evita bloqueo si el otro extremo no está listo)
   fd = open(FIFO_FILE, O_RDWR);
   if (fd == -1) {
      perror("Error abriendo FIFO");
      exit(1);
   }

   // Bucle principal: leer → procesar → responder
   while (1) {
      // Leer mensaje del cliente
      read_bytes = read(fd, readbuf, sizeof(readbuf) - 1);
      if (read_bytes <= 0)
         continue;  // si no hay datos, vuelve a intentar

      readbuf[read_bytes] = '\0';  // asegurar fin de cadena
      printf("FIFOSERVER: Received string: \"%s\" and length is %d\n",
             readbuf, (int)strlen(readbuf));

      // Verificar si es "end"
      to_end = strcmp(readbuf, end);
      if (to_end == 0) {
         printf("FIFOSERVER: Termination command received.\n");
         close(fd);
         break;
      }

      // Invertir la cadena recibida
      reverse_string(readbuf);
      printf("FIFOSERVER: Sending Reversed String: \"%s\" and length is %d\n",
             readbuf, (int)strlen(readbuf));

      // Enviar respuesta al cliente
      write(fd, readbuf, strlen(readbuf));

      // Pequeña pausa para que el cliente lea antes de la siguiente iteración
      sleep(2);
   }

   return 0;
}

// Invierte una cadena carácter por carácter
void reverse_string(char *str) {
   int first = 0;
   int last = (int)strlen(str) - 1;
   char temp;

   while (first < last) {
      temp = str[first];
      str[first] = str[last];
      str[last] = temp;
      first++;
      last--;
   }
}
