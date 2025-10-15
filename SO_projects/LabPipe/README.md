# Comunicación entre procesos con FIFO (Named Pipes)
Este proyecto muestra cómo dos procesos pueden comunicarse en Linux usando una pipe con nombre (FIFO).  
Está compuesto por dos programas en C:

- Servidor (servidor.c)  
  Crea la FIFO /tmp/fifo_twoway, espera mensajes del cliente y responde.  
  Si el mensaje recibido es "end", el servidor cierra la conexión y termina.  
  Si no, invierte la cadena y la envía de vuelta al cliente.

- Cliente (cliente.c)
  Abre la FIFO creada por el servidor, envía cadenas ingresadas por el usuario y muestra la respuesta del servidor.  
  Si el usuario escribe "end", el cliente envía ese mensaje y finaliza.

## Compilación

Uso del Makefile:

Para compilar ambos programas:
- make
Para limpiar:
-make clean
