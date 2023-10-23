#include "Barrier.h"
#include <thread>
#include <vector>
#include <iostream>

const int TotalThreads = 5;

void task(std::shared_ptr<Barrier> barrierObj) {
    for (int i = 0; i < 5; ++i) {
        std::cout << "first " << std::endl;
        barrierObj->waitForAll();
        std::cout << "second" << std::endl;
        barrierObj->waitForAll();
    }
}

int main(void) {
    std::vector<std::thread> threadArray(TotalThreads);
    std::shared_ptr<Barrier> barrierObj(new Barrier(5));

    for (int i = 0; i < threadArray.size(); ++i) {
        threadArray[i] = std::thread(task, barrierObj);
    }

    for (int i = 0; i < threadArray.size(); i++) {
        threadArray[i].join();
    }

    return 0;
}