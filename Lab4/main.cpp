#include "SafeBuffer.h"
#include "Event.h"
#include "Semaphore.h"
#include <iostream>
#include <thread>
#include <vector>
#include <memory>

static const int num_threads = 100;
const int size = 20;

Semaphore bufferFull(0); // Semaphore to track buffer full
Semaphore bufferEmpty(size); // Semaphore to track empty slots

void producer(std::shared_ptr<SafeBuffer<std::shared_ptr<Event>> theBuffer, int numLoops) {
    for (int i = 0; i < numLoops; ++i) {
        std::shared_ptr<Event> e = std::make_shared<Event>(i);

        // Wait for an empty slot in the buffer
        bufferEmpty.Wait();

        theBuffer->put(e);

        // Signal that the buffer is no longer empty
        bufferFull.Signal();
    }
}

void consumer(std::shared_ptr<SafeBuffer<std::shared_ptr<Event>> theBuffer, int numLoops) {
    for (int i = 0; i < numLoops; ++i) {
        // Wait for a filled slot in the buffer
        bufferFull.Wait();

        std::shared_ptr<Event> e = theBuffer->get();
        e->consume();

        // Signal that the buffer is no longer full
        bufferEmpty.Signal();
    }
}

int main(void) {
    std::vector<std::thread> vt(num_threads);
    std::shared_ptr<SafeBuffer<std::shared_ptr<Event>> aBuffer(new SafeBuffer<std::shared_ptr<Event>>(size));

    for (std::thread& t : vt) {
        t = std::thread(producer, aBuffer, 10);
    }

    for (auto& v : vt) {
        v.join();
    }

    return 0;
}