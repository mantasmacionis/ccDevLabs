#Author: Mantas Macionis
#License: Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. 
#Git: https://github.com/mantasmacionis/ccDevLabs/
#First simple Makefile
#Used to contain commands to compile projects
CC = g++
CPPFILES = helloThreads.cpp mutualEx.cpp Semaphore.cpp #CPP files used in this project
HFILES = Semaphore.h									#.h files used in this project
OBJFILES = $(CPPFILES:.cpp=.o)
CFLAGS = -std=c++11 -pthread -I.
DEBUGFLAGS =
#.o and flag linking below 
%.o: %.cpp $(HFILES)
	$(CC) -c -o $@ $< $(CFLAGS) $(DEBUGFLAGS)			

ALL: semaphore
#Creating the executable file below
semaphore: $(OBJFILES)
	$(CC) -o $@ $(OBJFILES) $(CFLAGS) $(DEBUGFLAGS)
#DEBUG FLags below
DEBUG: DEBUGFLAGS = -g -O0
DEBUG: ALL
#Clean rules below
CLEAN:
	rm -f $(OBJFILES) semaphore *~