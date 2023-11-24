# Author: Mantas Macionis
# License: Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License.
# Git: https://github.com/mantasmacionis/ccDevLabs/
# Makefile for quicksort program

CPPFILES= quicksort.cpp
HFILES=
CC=g++
CFLAGS= -std=c++11  -fopenmp

#This rule says that each .o file depends on a .cpp file of the same name
%.o: %.cpp
	$(CC) -c -o $@ $< $(CFLAGS) $(DEBUGFLAGS)
# Rule to build the QUICK executable
QUICK: quicksort.o
	$(CC) -o qsort.out quicksort.o $(CFLAGS) $(DEBUGFLAGS)

# Rule to build the QUICK executable with debugging flags
DSORT: DEBUGFLAGS = -g -O0
DSORT: QUICK

#this is customary and just deletes all .o files
CLEAN:
	rm *.o
