# Author: Mantas Macionis
# License: Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License.
# Git: https://github.com/mantasmacionis/ccDevLabs/
# Makefile for Dining Philosophers problem

CC = g++
CPPFILES = main.cpp 
HFILES = Semaphore.h
OBJFILES = $(CPPFILES:.cpp=.o)
CFLAGS = -std=c++11 -pthread -I.
DEBUGFLAGS =
EXECUTABLE = diningphilosophers 

# .o and flag linking below
%.o: %.cpp $(HFILES)
	$(CC) -c -o $@ $< $(CFLAGS) $(DEBUGFLAGS)

# Creating the executable file below
ALL: $(EXECUTABLE)

$(EXECUTABLE): $(OBJFILES)
	$(CC) -o $@ $(OBJFILES) $(CFLAGS) $(DEBUGFLAGS)

# DEBUG Flags below
DEBUG: DEBUGFLAGS = -g -O0
DEBUG: ALL

# Clean rules below
CLEAN:
	rm -f $(OBJFILES) $(EXECUTABLE) *~