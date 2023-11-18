/**
 * @file main.cpp
 * @brief main method.
 * @author Mantas Macionis
 * @date november-2023
 * @see https://github.com/mantasmacionis/ccDevLabs/
 * @license Creative Commons Attribution-NonCommercial-ShareAlike 4.0
 */
#include "Semaphore.h"
#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
#include <condition_variable>
#include <random>
#include <chrono>


const int COUNT = 5;
const int THINKTIME = 3;
const int EATTIME = 5;
std::vector<Semaphore> forks(COUNT);

/**
 * @brief thinking process for a philosopher with given ID.
 *
 * @param myID The identifier of the philosopher.
 */
void think(int myID) {
    // Generate a random thinking time between 1 and THINKTIME seconds
    int seconds = rand() % THINKTIME + 1;
    std::cout << myID << " is thinking! " << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(seconds));
}

/**
 * @brief Attempts to acquire forks for a philosopher with given ID.
 *
 * @param philID The identifier of the philosopher.
 */
void get_forks(int philID) {
    // Wait until the left fork is available
    forks[philID].Wait();
    // Wait until the right fork is available (circular allocation)
    forks[(philID + 1) % COUNT].Wait();
}

/**
 * @brief Releases forks after a philosopher with the given ID has finished eating.
 *
 * @param philID The identifier of the philosopher.
 */
void put_forks(int philID) {
    // Signal that the left fork is available
    forks[philID].Signal();
    // Signal that the right fork is available
    forks[(philID + 1) % COUNT].Signal();
}

/**
 * @brief eating process for a philosopher with given ID.
 *
 * @param myID The identifier of the philosopher.
 */
void eat(int myID) {
     // Generate a random eating time between 1 and EATTIME seconds
    int seconds = rand() % EATTIME + 1;
    std::cout << myID << " is chomping! " << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(seconds));
}

/**
 * @brief Represents the philosopher's life cycle.
 *
 * @param id The identifier of the philosopher.
 */
void philosopher(int id) {
    while (true) {
          // thinking process
        think(id);
        // Attempt to acquire forks for eating
        get_forks(id);
        eat(id);
         // Release acquired forks after eating
        put_forks(id);
    }
}

/**
 * @brief The main function for the dining philosophers.
 *
 * @return 0 for exit of the program.
 */
int main(void) {
    srand(time(NULL)); // initialize random seed:
     // Create a vector of philosopher threads
    std::vector<std::thread> vt(COUNT);
    int id = 0;
     // Create philosopher threads and assign them to the vector
    for (std::thread& t : vt) {
        t = std::thread(philosopher, id++);
    }
    /**< Join the philosopher threads with the main thread */
    for (auto& v : vt) {
        v.join();
    }
    return 0;
}