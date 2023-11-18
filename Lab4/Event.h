/**
 * @file Event.h
 * @brief Event implementation.
 * @author Mantas Macionis
 * @date november-2023
 * @see https://github.com/mantasmacionis/ccDevLabs/
 * @license Creative Commons Attribution-NonCommercial-ShareAlike 4.0
 */
#ifndef EVENT_H
#define EVENT_H

#include <iostream>

/**
 * @brief The Event class represents an event with an associated identifier.
 */
class Event {
public:
 /**
     * @brief Constructor for the Event class.
     *
     * @param id The identifier of the event.
     */
    Event(int id) : eventId(id) {}
    /**
     * @brief Consumes the event, printing a message indicating the event ID.
     */

    void consume() {
        std::cout << "Consumed Event " << eventId << std::endl; /*!< The identifier of the event. */
    }

private:
    int eventId;
};

#endif