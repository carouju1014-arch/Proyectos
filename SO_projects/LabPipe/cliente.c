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
#include <unistd.h>    // read, write, close
#include <fcntl.h>     // open, O_CREAT, O_RDWR

#define FIFO_FILE "/tmp/fifo_twoway"

int main(void) {
   int fd;                 // descriptor del FIFO
   int end_process;        // bandera para terminar el ciclo
   int stringlen;          // longitud de la cadena ingresada
   int read_bytes;         // bytes leídos desde el FIFO
   char readbuf[80];       // buffer de E/S
   char end_str[5];        // "end" + '\0'

   printf("FIFO_CLIENT: Send messages, infinitely, to end enter \"end\"\n");

   // MISMA LÓGICA: abrir/crear FIFO en lectura/escritura
   fd = open(FIFO_FILE, O_CREAT | O_RDWR, 0640);

   // palabra de corte
   strcpy(end_str, "end");

   // bucle principal
   while (1) {
      printf("Enter string: ");
      if (!fgets(readbuf, sizeof(readbuf), stdin)) {
         // si stdin se cierra, salimos (no cambia la lógica normal)
         break;
      }

      stringlen = (int)strlen(readbuf);

      // quitar el '\n' final si existe (mantiene el comportamiento original)
      if (stringlen > 0 && readbuf[stringlen - 1] == '\n') {
         readbuf[stringlen - 1] = '\0';
      } else {
         // si el usuario llenó el buffer sin '\n', la longitud real es la actual
         // (no cambiamos la lógica; solo evitamos escribir fuera de rango)
      }

      end_process = strcmp(readbuf, end_str);

      //printf("end_process is %d\n", end_process);
      if (end_process != 0) {
         // enviar al servidor
         write(fd, readbuf, strlen(readbuf));
         printf("FIFOCLIENT: Sent string: \"%s\" and string length is %d\n",
                readbuf, (int)strlen(readbuf));

         // leer respuesta
         read_bytes = (int)read(fd, readbuf, sizeof(readbuf) - 1);
         if (read_bytes > 0) {
            readbuf[read_bytes] = '\0';
            printf("FIFOCLIENT: Received string: \"%s\" and length is %d\n",
                   readbuf, (int)strlen(readbuf));
         } else {
            // si no hay respuesta, seguimos igual (misma lógica de bucle)
         }
      } else {
         // enviar "end" y salir
         write(fd, readbuf, strlen(readbuf));
         printf("FIFOCLIENT: Sent string: \"%s\" and string length is %d\n",
                readbuf, (int)strlen(readbuf));
         close(fd);
         break;
      }
   }

   return 0;
}
