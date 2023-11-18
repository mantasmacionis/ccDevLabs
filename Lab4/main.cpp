/**
 * @file main.cpp
 * @brief main method.
 * @author Mantas Macionis
 * @date november-2023
 * @see https://github.com/mantasmacionis/ccDevLabs/
 * @license Creative Commons Attribution-NonCommercial-ShareAlike 4.0
 */
#include "SafeBuffer.h"
#include "Event.h"
#include "Semaphore.h"
#include <iostream>
#include <thread>
#include <vector>
#include <memory>

static const int num_threads = 100;
const int size = 20;

Semaphore bufferFull(0); // Semaphore to track buffer full
Semaphore bufferEmpty(size); // Semaphore to track empty slots

/**
 * @brief The producer function adds events to a shared buffer.
 *
 * @param theBuffer A shared pointer to a SafeBuffer that holds shared pointers to events.
 * @param numLoops The number of times the producer should add events to the buffer.
 */
void producer(std::shared_ptr<SafeBuffer<std::shared_ptr<Event>>> theBuffer, int numLoops) {
    for (int i = 0; i < numLoops; ++i) {
        std::shared_ptr<Event> e = std::make_shared<Event>(i);

        // Wait for an empty slot in the buffer
        bufferEmpty.Wait();

        theBuffer->put(e);

        // Signal that the buffer is no longer empty
        bufferFull.Signal();
    }
}

/**
 * @brief The consumer function retrieves events from a shared buffer and consumes them.
 *
 * @param theBuffer A shared pointer to a SafeBuffer that holds shared pointers to events.
 * @param numLoops The number of times the consumer should retrieve and consume events from the buffer.
 */
void consumer(std::shared_ptr<SafeBuffer<std::shared_ptr<Event>>>theBuffer, int numLoops) {
    for (int i = 0; i < numLoops; ++i) {
        // Wait for a filled slot in the buffer
        bufferFull.Wait();

        std::shared_ptr<Event> e = theBuffer->get();
        e->consume();

        // Signal that the buffer is no longer full
        bufferEmpty.Signal();
    }
}

/**
 * @brief The main function.
 *
 * @return integer to represent the program has finished 
 */
int main(void) {
     // Create a vector of threads
    std::vector<std::thread> vt(num_threads);
     // Create a shared pointer to a SafeBuffer to hold shared pointers to events
    std::shared_ptr<SafeBuffer<std::shared_ptr<Event>>>aBuffer(new SafeBuffer<std::shared_ptr<Event>>(size));

    // Create producer threads and assign them to the vector
    for (std::thread& t : vt) {
        t = std::thread(producer, aBuffer, 10);
        std::cout << "Producer thread created." << std::endl;
    }
     // Wait for each thread to finish and print a message
    for (auto& v : vt) {
        v.join();
        std::cout << "A thread has finished." << std::endl;
    }
    std::cout << "All threads have finished." << std::endl;
    
    return 0;
}