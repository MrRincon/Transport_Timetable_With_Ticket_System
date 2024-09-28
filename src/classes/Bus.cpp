/*
Bus.cpp
authors: M00774667, M00916537, M00829986, M00843428, M00951627
created: 01/03/2024
updated: 20/04/2024
*/
#include "Bus.hpp"

//Constructor with all the parameters
Bus::Bus(std::string busID, std::string busDriver, std::string currentLocation, std::string routeAssigned, int capacity, bool delayedStatus)
{
  this->idHeader = 'B';
  this->id = busID;
  this->busDriver = busDriver;
  this->currentLocation = currentLocation;
  this->routeAssigned = routeAssigned;
  this->capacity = capacity;
  this->delayedStatus = delayedStatus;
}

//Getter methods
std::string Bus::getBusID()
{
  return id;
}

std::string Bus::getBusDriver()
{
  return Bus::busDriver;
}

std::string Bus::getCurrentLocation()
{
  return Bus::currentLocation;
}

std::string Bus::getRouteAssigned()
{
  return routeAssigned;
}

int Bus::getCapacity()
{
  return capacity;
}

bool Bus::getDelayedStatus()
{
  return delayedStatus;
}
