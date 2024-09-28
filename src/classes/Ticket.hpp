/*
Ticket.hpp
authors: M00774667, M00916537, M00829986, M00843428, M00951627
created: 01/03/2024
updated: 20/04/2024
*/
#ifndef TICKET_HPP
#define TICKET_HPP

// Include the necessary packages.
#include <iostream>
#include <string>
#include <ctime>
#include <chrono>
#include <sstream>
#include <iomanip>
#include "IDObject.hpp"

class Ticket : public IDObject{
// Ticket class private member variables.
private:
    std::string busAssignedTo, startLocation, endLocation, routeReference;
    time_t busTime;
    bool isValid;
// Ticket class public methods.
public:
    // Constructor for the user class with all parameters.
    Ticket(
        std::string ticketID,
        std::string busAssignedTo,
        std::string startLocation,
        std::string endLocation,
        std::string routeReference,
        time_t busTime,
        bool isValid);

    // Getter methods.
    std::string getTicketID() const;
    std::string getBusAssignedTo() const;
    std::string getStartLocation() const;
    std::string getEndLocation() const;
    std::string getRouteReference() const;
    time_t getBusTime() const;

    // Specific member methods.
    bool isTicketValid();

    // Setter methods to set the ticket validity
    void setValidation(bool status);
};
#endif
