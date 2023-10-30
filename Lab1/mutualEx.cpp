/**
 * @file mutualEx.cpp
 * @brief mutual exclusion example file
 * @author Mantas Macionis
 * @date october-2023
 * @see https://github.com/mantasmacionis/ccDevLabs/
 * @license Creative Commons Attribution-NonCommercial-ShareAlike 4.0
 */

#include "Semaphore.h"
#include <iostream>
#include <thread>
#include <vector>

static const int num_threads = 100;
int sharedVariable = 0;

/*! \fn updateTask
    \brief An Implementation of Mutual Exclusion using Semaphores

    Uses C++11 features such as mutex and condition variables to implement an example of a rendezvous for threads
*/

/**
 * @brief Update a shared variable
 *
 * This function updates a shared variable by incrementing it a specified
 * number of times.
 *
 * @param numUpdates The number of times to increment the shared variable.
 */
void updateTask(std::shared_ptr<Semaphore> /* firstSem */, int numUpdates) {
    for (int i = 0; i < numUpdates; i++) {
        // UPDATE SHARED VARIABLE HERE!
        sharedVariable++;
    }
}

/**
 * @brief The main method
 *
 * Vector of threads is created. launching multiple threads to execute
 * the updateTask function concurrently using a semaphore. After the threads complete their tasks, the main thread waits for
 * their completion 
 *
 * @return 0 on successful program execution.
 */
int main() {
    std::vector<std::thread> vt(num_threads);
    std::shared_ptr<Semaphore> aSemaphore(new Semaphore);

    /**< Launch the threads  */
    for (std::thread& t : vt) {
        t = std::thread(updateTask, aSemaphore, 1000);
    }
    std::cout << "Launched from the main\n";

    /**< Join the threads with the main thread */
    for (auto& v : vt) {
        v.join();
    }

    std::cout << sharedVariable << std::endl;
    return 0;
}