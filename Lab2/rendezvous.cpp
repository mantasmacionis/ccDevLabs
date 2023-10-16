#include "Semaphore.h"
#include <thread>
#include <vector>
#include <iostream>

/*! displays the first function in the barrier being executed */
void task(std::shared_ptr<Semaphore> mutexSem,std::shared_ptr<Semaphore> barrierSem, int threadCount){

  std::cout << "first " << std::endl;
  //put barrier code here
  std::cout << "second" << std::endl;
}




int main(void){
  std::shared_ptr<Semaphore> mutexSem;
  std::shared_ptr<Semaphore> barrierSem;
  std::shared_ptr<int> threadCount;
  mutexSem=std::make_shared<Semaphore>(1);
  barrierSem=std::make_shared<Semaphore>(0);
  threadCount=std::make_shared<int>(10);
  /*!< An array of threads*/
  std::vector<std::thread> threadArray(threadCount);
  /*!< Pointer to barrier object*/

  for(unsigned long int i=0; i < threadArray.size(); i++){
    threadArray[i]=std::thread(task,mutexSem,barrierSem,threadCount);
  }

  for(unsigned long int i = 0; i < threadArray.size(); i++){
    threadArray[i].join();
  }
  
  return 0;
}
