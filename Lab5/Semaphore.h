/**
 * @file Semaphore.h
 * @brief Semaphore header file
 * @author Mantas Macionis
 * @date november-2023
 * @see https://github.com/mantasmacionis/ccDevLabs/
 * @license Creative Commons Attribution-NonCommercial-ShareAlike 4.0
 */
#ifndef SEMAPHORE_H
#define SEMAPHORE_H 
#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
#include <condition_variable>
#include <random>
#include <chrono>


/**
 * @brief The Semaphore class, providing synchronization mechanism using a count.
 */
class Semaphore {
public:
/**
     * @brief Constructor for the Semaphore class.
     *
     * @param count Initial count for the semaphore (default is 1).
     */
    Semaphore(int count = 1) : count_(count) {}

    /**
     * @brief Waits on the semaphore until the count becomes greater than 0, then decrements the count.
     */
    void Wait() {
        // Acquire a unique lock on the associated mutex
        std::unique_lock<std::mutex> lock(mutex_);
          // Wait until the count becomes greater than 0
        condition_.wait(lock, [this] { return count_ > 0; });
        count_--;
    }

     /**
     * @brief Signals the semaphore, incrementing the count and waking up one waiting thread.
     */
    void Signal() {
        // Acquire a lock guard on the associated mutex
        std::lock_guard<std::mutex> lock(mutex_);
         // Increment the count after acquiring the lock
        count_++;
        condition_.notify_one();
    }

/**
 * @brief Private members of the Semaphore class.
 */
private:
    std::mutex mutex_; /*!< Mutex for thread synchronization. */
    std::condition_variable condition_; /*!< Condition variable for thread waiting. */
    int count_;  /*!< Semaphore count. */
};

#endif
