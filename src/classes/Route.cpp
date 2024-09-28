/*
Route.cpp
authors: M00774667, M00916537, M00829986, M00843428, M00951627
created: 02/03/2024
updated: 21/04/2024
*/
#include "Route.hpp"
// Constructor with all the parameters.
Route::Route(std::string routeId, std::string direction, std::string startPoint, std::string endPoint, std::vector<std::string> routeStopsOrder, double totalRouteDistance, int totalRouteTime, bool diversion, std::vector<std::string> busesAssigned)
{
  this->idHeader = 'R';
  this->id = routeId;
  this->direction = direction;
  this->startPoint = startPoint;
  this->endPoint = endPoint;
  this->routeStopsOrder = routeStopsOrder;
  this->totalRouteDistance = totalRouteDistance;
  this->totalRouteTime = totalRouteTime;
  this->diversion = diversion;
  this->busesAssigned = busesAssigned;
}

// Getter methods.
std::string Route::getRouteId(){
  return id;
}

std::string Route::getDirection(){
  return direction;
}

std::string Route::getStartingPoint(){
  return startPoint;
}

std::string Route::getEndingPoint(){
  return endPoint;
}

std::vector<std::string> Route::getRouteStopsOrder(){
  return routeStopsOrder;
}

double Route::getTotalRouteDistance(){
  return totalRouteDistance;
}

int Route::getTotalRouteTime(){
  return totalRouteTime;
}

bool Route::getDiversion(){
  return diversion;
}

std::vector<std::string> Route::getBusesAssigned(){
  return busesAssigned;
}

// Setter methods.
void Route::setDirection(std::string newDirection){
  direction = newDirection;
}

void Route::setStartingPoint(std::string newStartPoint){
  startPoint = newStartPoint;
}

void Route::setEndingPoint(std::string newEndPoint){
  endPoint = newEndPoint;
}
