/**
 * @file Semaphore.pp
 * @brief Semaphore implementation
 * @author Mantas Macionis
 * @date november-2023
 * @see https://github.com/mantasmacionis/ccDevLabs/
 * @license Creative Commons Attribution-NonCommercial-ShareAlike 4.0
 */
#include "Semaphore.h"
/*! \class Semaphore
    \brief A Semaphore Implementation

   Uses C++11 features such as mutex and condition variables to implement Semaphore

*/



/**
 * @brief Waits on the semaphore until the count becomes greater than 0,
 *        then decrements the count.
 */
void Semaphore::Wait()
{
      std::unique_lock< std::mutex > lock(m_mutex);
      m_condition.wait(lock,[&]()->bool{ return m_uiCount>0; });
      --m_uiCount;
}

/**
 * @brief Waits on the semaphore until the count becomes greater than 0
 *        or until the specified relative time duration elapses.
 *
 * @tparam R represents number of ticks in the clock's duration.
 * @tparam P represents the period of the clock's duration.
 * @param crRelTime  duration for which to wait.
 * @return True if the semaphore was successfully acquired within the specified time;
 *         false if the timeout.
 */
template< typename R,typename P >
bool Semaphore::Wait(const std::chrono::duration<R,P>& crRelTime)
{
      std::unique_lock< std::mutex > lock(m_mutex);
      if (!m_condition.wait_for(lock,crRelTime,[&]()->bool{ return m_uiCount>0; })){
	  return false;
      }
      --m_uiCount;
      return true;
}

/**
 * @brief Signals the semaphore, incrementing the count and waking up one waiting thread.
 */
void Semaphore::Signal()
{
      std::unique_lock< std::mutex > lock(m_mutex);
      ++m_uiCount;
      m_condition.notify_one();
}