#ifndef SAFE_BUFFER_H
#define SAFE_BUFFER_H

#include <queue>
#include <mutex>
#include <condition_variable>

template <typename T>
class SafeBuffer {
public:
    SafeBuffer(int size) : bufferSize(size) {}

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
    int bufferSize;
    std::queue<T> buffer;
    std::mutex mutex;
    std::condition_variable bufferFull;
    std::condition_variable bufferEmpty;
};

#endif