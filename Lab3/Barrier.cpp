/**
 * @file Barrier.cpp
 * @brief Barrier implementation
 * @author Mantas Macionis
 * @date october-2023
 * @see https://github.com/mantasmacionis/ccDevLabs/
 * @license Creative Commons Attribution-NonCommercial-ShareAlike 4.0
 */
#include "Barrier.h"

/**
 * @brief Constructor for the Barrier class.
 *
 *
 * @param NumThreads The number of threads for which the barrier will synchronize.
 */
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

/**
 * @brief Get the current count of threads at the barrier.
 *
 *
 * @return The current count of threads at the barrier.
 */
int Barrier::getCount() {
    return this->count;
}

/**
 * @brief Wait for all threads to reach a synchronization barrier.
 *
 */
void Barrier::waitForAll() {
    theMutex->Wait();  
    threadNum++;  // Increment the threadNum to count the number of threads that have reached the barrier

    if (threadNum == count) {  // If all threads have reached the barrier
        outerLock->Wait();  
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