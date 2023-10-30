/**
 * @file Barrier.h
 * @brief A barrier implementation
 * @author Mantas Macionis
 * @date october-2023
 * @see https://github.com/mantasmacionis/ccDevLabs/
 * @license Creative Commons Attribution-NonCommercial-ShareAlike 4.0
 */
#include "Semaphore.h"
#include <iostream>
#include <stdio.h>

/*! \class Barrier
    \brief A Barrier Implementation

   Uses C++11 features such as mutex and condition variables to implement a Barrier class using Semaphores

*/
class Barrier
{
private:

  int count;
  int threadNum;
  bool condition;
  std::shared_ptr<Semaphore> theMutex;
  std::shared_ptr<Semaphore> innerLock;
  std::shared_ptr<Semaphore> outerLock;


public:

  virtual ~Barrier();
  Barrier(int count);
  int getCount();
  void waitForAll();
};
