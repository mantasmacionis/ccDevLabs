#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

std::mutex mtx;
std::condition_variable cv;
bool taskOneExecuted = false;

/*! displays a message first */
void taskOne(int delay) {
    std::this_thread::sleep_for(std::chrono::seconds(delay));
    std::unique_lock<std::mutex> lock(mtx);
    std::cout << "I ";
    std::cout << "must ";
    std::cout << "print ";
    std::cout << "first" << std::endl;
    taskOneExecuted = true;
    cv.notify_one();  // Signal that taskOne has completed
}

/*! displays a message second */
void taskTwo() {
    std::unique_lock<std::mutex> lock(mtx);
    cv.wait(lock, [] { return taskOneExecuted; });  // Wait for taskOne to complete
    std::cout << "This ";
    std::cout << "will ";
    std::this_thread::sleep_for(std::chrono::seconds(5));
    std::cout << "appear ";
    std::cout << "second" << std::endl;
}

int main() {
    std::thread threadOne, threadTwo;

    int taskOneDelay = 5;
    threadOne = std::thread(taskOne, taskOneDelay);
    threadTwo = std::thread(taskTwo);

    std::cout << "Launched from the main\n";

    threadOne.join();
    threadTwo.join();

    return 0;
}
