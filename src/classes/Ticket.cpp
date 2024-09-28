/*
Ticket.cpp
authors: M00774667, M00916537, M00829986, M00843428, M00951627
created: 02/03/2024
updated: 21/04/2024
*/

#include "Ticket.hpp"
// Constructor for the class.
Ticket::Ticket(std::string ticketID, std::string busAssignedTo, std::string startLocation,
std::string endLocation, std::string routeReference, time_t busTime, bool isValid){
  this->idHeader = 'T';
  this->id = ticketID;
  this->busAssignedTo = busAssignedTo;
  this->startLocation = startLocation;
  this->endLocation = endLocation;
  this->routeReference = routeReference;
  this->busTime = busTime;
  this->isValid = isValid;
}

// Getter methods.
std::string Ticket::getTicketID() const{
  return id;
}

std::string Ticket::getBusAssignedTo() const{
  return busAssignedTo;
}

std::string Ticket::getStartLocation() const{
  return startLocation;
}

std::string Ticket::getEndLocation() const{
  return endLocation;
}

std::string Ticket::getRouteReference() const{
  return routeReference;
}

time_t Ticket::getBusTime() const{
  return busTime;
}

// method to return and update the boolean for the ticket validity variable.
bool Ticket::isTicketValid(){
  time_t currentTime;
  time(&currentTime);
  if (busTime > currentTime)
  {
    this->setValidation(true);
    return true;
  }
  else
  {
    this->setValidation(false);
    return false;
  }
}

// Setter methods for the validity of the ticket.
void Ticket::setValidation(bool newStatus){
  isValid = newStatus;
}
