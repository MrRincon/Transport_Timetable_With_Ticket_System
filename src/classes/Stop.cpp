/*
Stop.cpp
authors: M00774667, M00916537, M00829986, M00843428, M00951627
created: 02/03/2024
updated: 21/04/2024
*/
#include "Stop.hpp"

Stop::Stop(std::string stopId, std::string stopName, double xLocation, double yLocation, std::vector<std::string> routeAssigned, std::unordered_map<std::string, std::vector<std::string>> bussesAssigned){
  this->idHeader = 'S';
  this->id = stopId;
  this->stopName = stopName;
  this->xLocation = xLocation;
  this->yLocation = yLocation;
  this->routeAssigned = routeAssigned;
  this->bussesAssigned = bussesAssigned;
};

//getter methods.
std::string Stop::getStopID() {
    return id;
}

std::string Stop::getStopName() {
    return stopName;
}

double Stop::getXLocation() {
    return xLocation;
}

double Stop::getYLocation() {
    return yLocation;
}

std::vector<std::string> Stop::getRoutesAssigned() {
    return routeAssigned;
}

std::unordered_map<std::string, std::vector<std::string>> Stop::getBussesAssigned() {
    return bussesAssigned;
}

//setter methods.
void Stop::setStopName(std::string name) {
    stopName = name;
}

void Stop::setCoordinates(double x, double y) {
    xLocation = x;
    yLocation = y;
}
