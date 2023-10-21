#Author: Mantas Macionis
#License: Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. 
#Git: https://github.com/mantasmacionis/ccDevLabs/
#First simple Makefile
#Used to contain commands to compile projects
CC = g++
CPPFILES = helloThreads.cpp mutualEx.cpp Semaphore.cpp
HFILES = Semaphore.h
OBJFILES = $(CPPFILES:.cpp=.o)
CFLAGS = -std=c++11 -pthread -I.
DEBUGFLAGS =

%.o: %.cpp $(HFILES)
	$(CC) -c -o $@ $< $(CFLAGS) $(DEBUGFLAGS)

ALL: semaphore

semaphore: $(OBJFILES)
	$(CC) -o $@ $(OBJFILES) $(CFLAGS) $(DEBUGFLAGS)

DEBUG: DEBUGFLAGS = -g -O0
DEBUG: ALL

CLEAN:
	rm -f $(OBJFILES) semaphore *~