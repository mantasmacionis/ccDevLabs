/**
 * @file SafeBuffer.h
 * @brief SafeBuffer header file.
 * @author Mantas Macionis
 * @date november-2023
 * @see https://github.com/mantasmacionis/ccDevLabs/
 * @license Creative Commons Attribution-NonCommercial-ShareAlike 4.0
 */
#ifndef SAFE_BUFFER_H
#define SAFE_BUFFER_H

#include <queue>
#include <mutex>
#include <condition_variable>

/**
 * @brief The SafeBuffer class provides a thread-safe buffer for storing elements of type T.
 * 
 * @tparam T The type of elements stored in the buffer.
 */
template <typename T>
class SafeBuffer {
public:
/**
     * @brief Constructor for SafeBuffer class.
     * 
     * @param size The maximum size of the buffer.
     */
    SafeBuffer(int size) : bufferSize(size) {}
    /**
     * @brief Adds an item to the buffer in a thread-safe manner.
     * 
     * @param item The item to be added to the buffer.
     */

    void put(T item) {
        std::unique_lock<std::mutex> lock(mutex);
        bufferFull.wait(lock, [this] { return buffer.size() < bufferSize; });
        buffer.push(item);
        bufferEmpty.notify_all();
    }

    T get() {
        std::unique_lock<std::mutex> lock(mutex);
        bufferEmpty.wait(lock, [this] { return !buffer.empty(); });
        T item = buffer.front();
        buffer.pop();
        bufferFull.notify_all();
        return item;
    }

private:
    int bufferSize;  /*!< The maximum size of the buffer. */
    std::queue<T> buffer;  /*!< buffer storing elements of type T. */
    std::mutex mutex; /*!< Mutex for thread synchronization. */
    std::condition_variable bufferFull; /*!< Condition variable for buffer full condition. */
};

#endif