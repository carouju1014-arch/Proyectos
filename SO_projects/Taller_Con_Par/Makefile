# ============================================================================
# Makefile - Laboratorios de Sistemas Operativos
# Autor: Carolina Ujueta
# Universidad Javeriana
# Profesor: John Corredor
# ============================================================================
# Este Makefile compila los 8 laboratorios sin utilizar banderas adicionales.
# Cada laboratorio debe estar en un archivo labX.c (donde X es de 1 a 8).
# ============================================================================

# Compilador
CC = gcc

# Archivos fuente y ejecutables
LABS = lab1 lab2 lab3 lab4 lab5 lab6 lab7 lab8

# Regla principal
all: $(LABS)

# Regla genérica para compilar cada laboratorio
%: %.c
	$(CC) $< -o $@

# Limpieza de ejecutables
clean:
	rm -f $(LABS)
