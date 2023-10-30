/**
 * @file helloThreads.cpp
 * @brief This is the main source file for the project.
 * @author Mantas Macionis
 * @date october-2023
 * @see https://github.com/mantasmacionis/ccDevLabs/
 * @license Creative Commons Attribution-NonCommercial-ShareAlike 4.0
 */

#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

std::mutex mtx;
std::condition_variable cv;
bool taskOneExecuted = false; //Created boolean to track whether task has been completed

/**
 * @brief Delay execution for a specified duration and print a message.
 * Once the printing
 * is finished, it sets a flag to true and signals completion using a condition
 * variable.
 *
 * @param delay The number of seconds to delay the execution.
 */
void taskOne(int delay) {
    std::this_thread::sleep_for(std::chrono::seconds(delay));
    std::unique_lock<std::mutex> lock(mtx);
    std::cout << "I ";
    std::cout << "must ";
    std::cout << "print ";
    std::cout << "first" << std::endl;
    taskOneExecuted = true; //flag set to true once printing is finished
    cv.notify_one();  // Signal that taskOne is completed
}

/**
 * @brief Waits for the completion of TaskOne and then performs additional actions.
 *
 * This function waits for TaskOne to complete its execution by monitoring a
 * condition variable and lock. 
 *
 * @note TaskTwo must appear after taskOne
 */
void taskTwo() {
    std::unique_lock<std::mutex> lock(mtx);
    cv.wait(lock, [] { return taskOneExecuted; });  // Waiting for signal from TaskOne
    std::cout << "This ";
    std::cout << "will ";
    std::this_thread::sleep_for(std::chrono::seconds(5));
    std::cout << "appear ";
    std::cout << "second" << std::endl;
}

/**
 * @brief The main method for the program
 *
 * hreadOne and threadTwo creation, execute the taskOne and taskTwo
 * functions concurrently. After launching the threads, output launched from main,
 * then wait for both threads to complete their execution 
 *
 * @return 0 on successful program execution.
 */
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
