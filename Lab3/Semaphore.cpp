/**
 * @file Semaphore.cpp
 * @brief Semaphore Implementation
 * @author Mantas Macionis
 * @date october-2023
 * @see https://github.com/mantasmacionis/ccDevLabs/
 * @license Creative Commons Attribution-NonCommercial-ShareAlike 4.0
 */
#include "Semaphore.h"

/**
 * @brief Wait for a semaphore to become available.
 *
 * function acquires a lock and checks the semaphore count. If the count is greater
 * than 0, it decrements the count and proceeds. Otherwise, it waits until the
 * semaphore becomes available.
 */
void Semaphore::Wait() {
    std::unique_lock<std::mutex> lock(m_mutex);
    m_condition.wait(lock, [&]() -> bool { return m_uiCount > 0; });
    --m_uiCount;
}

/**
 * @brief Signal the availability of the semaphore.
 *
 * This function signals the availability of the semaphore, allowing waiting
 * threads to proceed. It increments the semaphore count and notifies one
 * waiting thread to become active.
 */
void Semaphore::Signal() {
    std::unique_lock<std::mutex> lock(m_mutex);
    ++m_uiCount;
    m_condition.notify_one();
}
