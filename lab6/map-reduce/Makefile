# Author: Mantas Macionis
# License: Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License.
# Git: https://github.com/mantasmacionis/ccDevLabs/
# Makefile for reduction program

CPPFILES= reduction.cpp
HFILES=
CC=g++
CFLAGS= -std=c++11  -fopenmp

#This rule says that each .o file depends on a .cpp file of the same name
%.o: %.cpp
	$(CC) -c -o $@ $< $(CFLAGS) -lgomp  $(DEBUGFLAGS)
# Rule to build the REDUCE executable
REDUCE: reduction.o
	$(CC) -o reduce.out reduction.o $(CFLAGS) $(DEBUGFLAGS)

# Rule to build the REDUCE executable with debugging flags
DREDUCE: DEBUGFLAGS = -g -O0
DREDUCE: REDUCE

#this is customary and just deletes all .o files
CLEAN:
	rm *.o
