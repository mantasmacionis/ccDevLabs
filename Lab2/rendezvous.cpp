/**
 * @file rendezvous.cpp
 * @brief rendezvous implementation main method.
 * @author Mantas Macionis
 * @date october-2023
 * @see https://github.com/mantasmacionis/ccDevLabs/
 * @license Creative Commons Attribution-NonCommercial-ShareAlike 4.0
 */
#include "Semaphore.h" // Semaphore header.
#include <thread>
#include <vector>
#include <iostream>
#include <memory> //memory for std::shared_ptr.

/**
 * @brief rendezvous barrier for synchronization among multiple threads.
 * 
 * Each thread executes "first ", then they enter the barrier and wait for
 * all other threads to arrive. Once all threads have arrived, they continue execution
 * with second.
 *
 * @param mutexSem A shared semaphore for mutual exclusion.
 * @param barrierSem A shared semaphore for the rendezvous barrier.
 * @param threadCount A shared integer count of the remaining threads.
 */
void task(std::shared_ptr<Semaphore> mutexSem, std::shared_ptr<Semaphore> barrierSem, std::shared_ptr<int> threadCount) {

  std::cout << "first " << std::endl;
  
  // Enter the rendezvous barrier
  mutexSem->wait(); 
  (*threadCount)--;
  if (*threadCount == 0) {
    barrierSem->signal(); // Release the barrier semaphore if all threads have arrived.
  }
  mutexSem->signal(); 
  
  barrierSem->wait(); // Wait for all threads to arrive at the barrier.
  barrierSem->signal(); // Signal the next thread to proceed.
  
  std::cout << "second" << std::endl;
}

/**
 * @brief main method for rendezvous
 *
 * It creates and manages
 * semaphores and an array of threads, each of which runs the `task` function.
 * After all threads have completed.
 *
 * @return 0 on successful program execution.
 */
int main(void) {
  std::shared_ptr<Semaphore> mutexSem = std::make_shared<Semaphore>(1);
  std::shared_ptr<Semaphore> barrierSem = std::make_shared<Semaphore>(0);
  std::shared_ptr<int> threadCount = std::make_shared<int>(10);
  
  /*!< An array of threads */
  std::vector<std::thread> threadArray(*threadCount);

  for (unsigned long int i = 0; i < threadArray.size(); i++) {
    threadArray[i] = std::thread(task, mutexSem, barrierSem, threadCount);
  }

  for (unsigned long int i = 0; i < threadArray.size(); i++) {
    threadArray[i].join();
  }

  return 0;
}
