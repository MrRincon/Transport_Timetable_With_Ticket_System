/*
Stop.cpp
authors: M00774667, M00916537, M00829986, M00843428, M00951627
created: 01/03/2024
updated: 21/04/2024
*/
#ifndef STOP_HPP
#define STOP_HPP
#include <string>
#include <iostream>
#include <vector>
#include <unordered_map>
#include "IDObject.hpp"

//Forward declaration to avoid compiling errors.
class Route;
class Bus;
class Stop : public IDObject{
// Ticket class private member variables.
private:
    std::string stopName;
    double xLocation, yLocation;//Coordinates of the stop on a map.
    std::vector<std::string> routeAssigned;
    std::unordered_map<std::string, std::vector<std::string>> bussesAssigned;
// Ticket class public methods.
public:
    //Constructor for the Stop class with all the parameters.
    Stop(
        std::string stopId,
        std::string stopName,
        double xLocation,
        double yLocation,
        std::vector<std::string> routeAssigned,
        std::unordered_map<std::string, std::vector<std::string>> bussesAssigned
        );

    //Getter methods.
    std::string getStopID();
    std::string getStopName();
    double getXLocation();
    double getYLocation();
    std::vector<std::string> getRoutesAssigned();
    std::unordered_map<std::string, std::vector<std::string>> getBussesAssigned();

    //Setter methods.
    void setStopName(std::string);
    void setCoordinates(double x, double y);
};
#endif
