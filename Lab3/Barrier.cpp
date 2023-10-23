#include "Barrier.h"

// Constructor for the Barrier class
Barrier::Barrier(int NumThreads) {
    count = NumThreads;
    threadNum = 0;
    theMutex = std::make_shared<Semaphore>(1);  // Create a Semaphore with an initial count of 1
    innerLock = std::make_shared<Semaphore>(0);  //0
    outerLock = std::make_shared<Semaphore>(1); //1
}

// Destructor for the Barrier class
Barrier::~Barrier() {
    // Destructor definition, if necessary
}

// Get the current count value of the Barrier
int Barrier::getCount() {
    return this->count;
}

// Wait for all threads to reach the barrier before proceeding
void Barrier::waitForAll() {
    theMutex->Wait();  // Acquire theMutex to prevent concurrent access to shared variables
    threadNum++;  // Increment the threadNum to count the number of threads that have reached the barrier

    if (threadNum == count) {  // If all threads have reached the barrier
        outerLock->Wait();  // Acquire outerLock to synchronize the release of threads
        innerLock->Signal();  // Signal innerLock to allow all threads to proceed
    }

    theMutex->Signal(); 
    innerLock->Wait();  
    innerLock->Signal(); 

    theMutex->Wait();  
    threadNum--;  

    if (threadNum == 0) {  
        innerLock->Wait();  
        outerLock->Signal();  
    }

    theMutex->Signal();  
    outerLock->Wait(); 
    outerLock->Signal();  
}