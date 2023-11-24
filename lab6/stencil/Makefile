# Author: Mantas Macionis
# License: Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License.
# Git: https://github.com/mantasmacionis/ccDevLabs/
# Makefile for stencil program


CFILES= stencil.cpp
HFILES=
CC=g++
CFLAGS= -std=c++11  -fopenmp

#This rule says that each .o file depends on a .cpp file of the same name
%.o: %.cpp
	$(CC) -c -o $@ $< $(CFLAGS) $(DEBUGFLAGS)
# Rule to build the STENCIL executable
STENCIL: stencil.o
	$(CC) -o stencil.out stencil.o $(CFLAGS) $(DEBUGFLAGS)

MANDEL: mandelbroit.o
	$(CC) -o mandelbroit.out mandelbroit.o $(CFLAGS) $(DEBUGFLAGS)

# Rule to build the STENCIL executable with debugging flags
DSTENCIL: DEBUGFLAGS = -g -O0
DSTENCIL: STENCIL

#this is customary and just deletes all .o files
CLEAN:
	rm *.o
