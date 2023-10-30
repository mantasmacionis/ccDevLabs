/**
 * @file Semaphore.h
 * @brief Semaphore header file
 * @author Mantas Macionis
 * @date october-2023
 * @see https://github.com/mantasmacionis/ccDevLabs/
 * @license Creative Commons Attribution-NonCommercial-ShareAlike 4.0
 */
#include <mutex>
#include <condition_variable>

/**
 * @class Semaphore
 * @brief A class representing a counting semaphore for synchronization.
 *
 * This class provides a counting semaphore for synchronization between multiple threads.
 * It allows threads to wait for a resource to become available and signal when it's available.
 */
class Semaphore
{
private:
    unsigned int m_uiCount; /*!< Holds the Semaphore count */
    std::mutex m_mutex;
    std::condition_variable m_condition;


public:
    Semaphore(unsigned int uiCount=0)
      : m_uiCount(uiCount) { };
    void Wait();
    void Signal();
};
