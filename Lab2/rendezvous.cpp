#include "Semaphore.h" // Semaphore header.

#include <thread>
#include <vector>
#include <iostream>
#include <memory> //memory for std::shared_ptr.

/*! displays the first function in the barrier being executed */
void task(std::shared_ptr<Semaphore> mutexSem, std::shared_ptr<Semaphore> barrierSem, std::shared_ptr<int> threadCount) {

  std::cout << "first " << std::endl;
  
  // Enter the rendezvous barrier
  mutexSem->wait(); // Acquire the mutex for mutual exclusion.
  (*threadCount)--;
  if (*threadCount == 0) {
    barrierSem->signal(); // Release the barrier semaphore if all threads have arrived.
  }
  mutexSem->signal(); // Release the mutex.
  
  barrierSem->wait(); // Wait for all threads to arrive at the barrier.
  barrierSem->signal(); // Signal the next thread to proceed.
  
  std::cout << "second" << std::endl;
}

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
