/**
 * @file main.cpp
 * @brief main method.
 * @author Mantas Macionis
 * @date october-2023
 * @see https://github.com/mantasmacionis/ccDevLabs/
 * @license Creative Commons Attribution-NonCommercial-ShareAlike 4.0
 */
#include "Barrier.h"
#include <thread>
#include <vector>
#include <iostream>

const int TotalThreads = 5;

/**
 * @brief hread synchronization process using a barrier.
 *
 * Repeatedly prints "first," waits for all threads to reach the barrier,
 * prints "second," and waits again. Continue for iterations
 *
 * @param barrierObj A shared pointer to the barrier object for synchronization.
 */
void task(std::shared_ptr<Barrier> barrierObj) {
    for (int i = 0; i < 5; ++i) {
        std::cout << "first " << std::endl;
        barrierObj->waitForAll();
        std::cout << "second" << std::endl;
        barrierObj->waitForAll();
    }
}

/**
 * @brief Main method
 *
 * Creates and manages a vector of
 * threads, each of which executes the `task` function with the provided barrier
 * object. After all threads have completed their tasks, the program returns 0
 *
 * @return 0 on successful program execution.
 */
int main(void) {
    std::vector<std::thread> threadArray(TotalThreads);
    std::shared_ptr<Barrier> barrierObj(new Barrier(5));

    for (int i = 0; i < threadArray.size(); ++i) {
        threadArray[i] = std::thread(task, barrierObj);
    }

    for (int i = 0; i < threadArray.size(); i++) {
        threadArray[i].join();
    }

    return 0;
}