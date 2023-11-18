/**
 * @file Semaphore.h
 * @brief Semaphore implementation.
 * @author Mantas Macionis
 * @date november-2023
 * @see https://github.com/mantasmacionis/ccDevLabs/
 * @license Creative Commons Attribution-NonCommercial-ShareAlike 4.0
 */
#ifndef SEMAPHORE_H
#define SEMAPHORE_H 
#include <mutex>
#include <condition_variable>
#include <chrono>
/*! \class Semaphore
    \brief A Semaphore Implementation

   Uses C++11 features such as mutex and condition variables to implement Semaphore

*/

/**
 * @brief Semaphore class, to implement synchronization mechanism using a count.
 */
class Semaphore
{
private:
    unsigned int m_uiCount; /*!< Holds the Semaphore count */
    std::mutex m_mutex; /*!< Mutex for thread synchronization */
    std::condition_variable m_condition; /*!< Condition variable for thread waiting */
 
/**
     * @brief Constructor for Semaphore class.
     *
     * @param uiCount Initial count for the Semaphore (default is 0).
     */    
public:
    Semaphore(unsigned int uiCount=0)
          : m_uiCount(uiCount) { };
          
    /**
     * @brief Waits on the semaphore until the count becomes greater than 0,
    *        or until the time duration elapses.
     *
     * @tparam R represents the number of ticks in the clock's duration.
    * @tparam P represents the period of the clock's duration.
    * @param crRelTime The time duration for which to wait.
    * @return True if the semaphore was successfully reached within time;
    *         false if the timeout reached.
     */
    void Wait();
    template< typename R,typename P >
    bool Wait(const std::chrono::duration<R,P>& crRelTime);
    void Signal();

};

#endif
