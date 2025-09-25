###########################################################################
# Makefile: bash ara automatizar instrucciones de compilación
# Se requiere automatizar la compilación
# Nombre: Carolina Ujueta
# Fecha: 12/08/2025
###########################################################################

GCC = gcc
BIBLIOTECAS = -lm
PROGRAMAS = mod_ujueta

all: $(PROGRAMAS)

mod_ujueta:
	$(GCC) modulo.c mod_ujueta.c -o $@ $(BIBLIOTECAS)

clean:
	rm -f $(PROGRAMAS) 
