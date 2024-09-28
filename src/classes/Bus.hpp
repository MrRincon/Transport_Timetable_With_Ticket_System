/*
Bus.hpp
authors: M00774667, M00916537, M00829986, M00843428, M00951627
created: 01/03/2024
updated: 20/04/2024
*/
#ifndef BUS_HPP
#define BUS_HPP
#include "IDObject.hpp"
#include <iostream>
#include <string>

class Bus : public IDObject
{
private:
    std::string busDriver, currentLocation, routeAssigned;
    int capacity;
    bool delayedStatus;

public:
    // Constructor for the bus class with all the parameters.
    Bus(
        std::string busID,
        std::string busDriver,
        std::string currentLocation,
        std::string routeAssigned,
        int capacity,
        bool delayedStatus);

    // Getter methods.
    std::string getBusID();
    std::string getBusDriver();
    std::string getCurrentLocation();
    std::string getRouteAssigned();
    int getCapacity();
    bool getDelayedStatus();
};
#endif
