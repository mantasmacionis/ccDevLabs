#ifndef EVENT_H
#define EVENT_H

#include <iostream>

class Event {
public:
    Event(int id) : eventId(id) {}

    void consume() {
        std::cout << "Consumed Event " << eventId << std::endl;
    }

private:
    int eventId;
};

#endif