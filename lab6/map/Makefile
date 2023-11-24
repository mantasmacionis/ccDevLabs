# Author: Mantas Macionis
# License: Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License.
# Git: https://github.com/mantasmacionis/ccDevLabs/
# Makefile for saxpy program


CFILES= saxpy.cpp
HFILES=
CC=g++
CFLAGS= -std=c++11 -pthread -fopenmp

#.o and flag linking below
%.o: %.cpp
	$(CC) -c -o $@ $< $(CFLAGS) $(DEBUGFLAGS)

# Rule to build the SAXPY executable
SAXPY: saxpy.o
	$(CC) -o saxpy.out saxpy.o $(CFLAGS) $(DEBUGFLAGS)

# Rule to build the MANDEL executable
MANDEL: mandelbroit.o
	$(CC) -o mandelbroit.out mandelbroit.o $(CFLAGS) $(DEBUGFLAGS)

# Rule to build the SAXPY executable with debugging flags
DSAXPY: DEBUGFLAGS = -g -O0
DSAXPY: SAXPY

#this is customary and just deletes all .o files
CLEAN:
	rm *.o
