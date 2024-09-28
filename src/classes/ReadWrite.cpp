/*
ReadWrite.cpp
authors: M00774667, M00916537, M00829986, M00843428, M00951627
created: 01/03/2024
updated: 21/04/2024
*/

#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include "ReadWrite.hpp"
#include "Helper.hpp"

// class constructor also sets the default values
ReadWrite::ReadWrite(){
  this->nullVal = "NULL";
  this->currentUserId = 0;
  this->currentTicketId = 0;
}

ReadWrite::~ReadWrite(){

}

// used to get the single instance of the ReadWrite object
ReadWrite& ReadWrite::instance(){
    static ReadWrite rw;
    return rw;
}

// reads data from the provided data files and stores the created classes into appropriate vectors
bool ReadWrite::init(std::string uPath, std::string bPath, std::string tPath, std::string sPath, std::string rPath){
  // If a required dataset is not provided then an error message is displayed
  if(!this->fileExists(bPath) || !this->fileExists(sPath) || !this->fileExists(rPath)){
    std::cout << "A bus, stop and route dataset must be provided." << std::endl;
    return false;
  }
  // attempts to load data from user dataset
  std::vector<std::vector<std::string>> userValues = this->loadFromFile(uPath);
  this->parseData(userValues, 0);
  std::vector<std::vector<std::string>> busValues = this->loadFromFile(bPath);
  this->parseData(busValues, 1);
  // attempts to load data from required dataset buses, if something goes wrong then the function terminates early
  if(this->busList.size() <= 0){
    std::cout << "Something went wrong loading bus dataset." << std::endl;
    return false;
  }
  // attempts to load data from ticket dataset
  std::vector<std::vector<std::string>> ticketValues = this->loadFromFile(tPath);
  this->parseData(ticketValues, 2);
  std::vector<std::vector<std::string>> stopValues = this->loadFromFile(sPath);
  this->parseData(stopValues, 3);
  // attempts to load data from required dataset stops, if something goes wrong then the function terminates early
  if(this->stopList.size() <= 0){
    std::cout << "Something went wrong loading stops dataset." << std::endl;
    return false;
  }
  std::vector<std::vector<std::string>> routeValues = this->loadFromFile(rPath);
  this->parseData(routeValues, 4);
  // attempts to load data from required dataset routes, if something goes wrong then the function terminates early
  if(this->routeList.size() <= 0){
    std::cout << "Something went wrong loading route dataset." << std::endl;
    return false;
  }
  this->sortAll();
  return true;
}

void  ReadWrite::clearAllData(){
  this->userList.clear();
  this->ticketList.clear();
  this->busList.clear();
  this->stopList.clear();
}

// saves changes made during runtime to a persistent file
void ReadWrite::saveData(std::vector<std::string> filenames){
  this->sortAll();
  this->saveUsers(filenames[0]);
  this->saveTickets(filenames[2]);
}

// sorts all vectors
void ReadWrite::sortAll(){
  this->sortUsers();
  this->sortTickets();
  this->sortBuses();
  this->sortRoutes();
  this->sortStops();
}

// sorts users
void ReadWrite::sortUsers(){
  Sort<User> userSorter;
  userSorter.sort(this->userList, [](User u){ return u.getIdValue();});
}

// sorts tickets
void ReadWrite::sortTickets(){
  Sort<Ticket> ticketSorter;
  ticketSorter.sort(this->ticketList, [](Ticket t){ return t.getIdValue();});
}

// sorts buses
void ReadWrite::sortBuses(){
  Sort<Bus> busSorter;
  busSorter.sort(this->busList, [](Bus b){ return b.getIdValue();});
}

// sorts routes
void ReadWrite::sortRoutes(){
  Sort<Route> routeSorter;
  routeSorter.sort(this->routeList, [](Route r){ return r.getIdValue();});
}

// sorts stops
void ReadWrite::sortStops(){
  Sort<Stop> stopSorter;
  stopSorter.sort(this->stopList, [](Stop s){ return s.getIdValue();});
}

// saves user list to a file
void ReadWrite::saveUsers(std::string filename){
  std::ofstream file;
  file.open(filename);
  file << "Users\n";
  file << "First Name,Last Name,Password,Email,UID,Balance,Tickets\n";
  for(int i = 0; i < this->userList.size(); i++){
    file << this->createUserStr(this->userList[i]) + "\n";
  }
  file.close();
}

// saves ticket list to a file
void ReadWrite::saveTickets(std::string filename){
  std::ofstream file;
  file.open(filename);
  file << "Ticket\n";
  file << "ID,Assigned Bus,Start Location,End Location,Route,Bus Time,Valid\n";
  for(int i = 0; i < this->ticketList.size(); i++){
    std::string strTicket = this->createTicketStr(this->ticketList[i]);
    file << strTicket + "\n";
  }
  file.close();
}

// Gets and returns a pointer to the user object at the provided index
User* ReadWrite::getUser(std::string id){
  int idx = this->findUser(id);
  if(idx != -1){
    return &(this->userList[idx]);
  }
  return nullptr;
}

// Gets and returns a pointer to the ticket object at the provided index
Ticket* ReadWrite::getTicket(std::string id){
  int idx = this->findTicket(id);
  if(idx != -1){
    return &(this->ticketList[idx]);
  }
  return nullptr;
}

// finds and returns a pointer to the stop with the provided id
Stop* ReadWrite::getStop(std::string id){
  int idx = this->findStop(id);
  if(idx != -1){
    return &(this->stopList[idx]);
  }
  return nullptr;
}

// finds and returns a pointer to the bus with the provided id
Bus* ReadWrite::getBus(std::string id){
  int idx = this->findBus(id);
  if(idx != -1){
    return &(this->busList[idx]);
  }
  return nullptr;
}

// finds and returns a pointer to the route with the provided id
Route* ReadWrite::getRoute(std::string id){
  int idx = this->findRoute(id);
  if(idx != -1){
    return &(this->routeList[idx]);
  }
  return nullptr;
}

// removes user at provided index in the user list
void ReadWrite::removeUser(int idx){
  if(idx >= 0 && idx < this->userList.size()){
    this->userList.erase(this->userList.begin() + idx);
    return;
  }
  std::cout << "No user at provided index" << std::endl;
}

// removes ticket at provided index in the user list
void ReadWrite::removeTicket(int idx){
  if(idx >= 0 && idx < this->ticketList.size()){
    this->ticketList.erase(this->ticketList.begin() + idx);
    return;
  }
  std::cout << "No ticket at provided index" << std::endl;
}

// getters for the respective class lists stored
std::vector<User> ReadWrite::getUserList(){
  return this->userList;
}

std::vector<Ticket> ReadWrite::getTicketList(){
  return this->ticketList;
}

std::vector<Bus> ReadWrite::getBusList(){
  return this->busList;
}

std::vector<Stop> ReadWrite::getStopList(){
  return this->stopList;
}

std::vector<Route> ReadWrite::getRouteList(){
  return this->routeList;
}

// binary search which accepts an id value to search for as well as a start, end and class typename
// the class type integer indicates which list the binary search should search through
int ReadWrite::binarySearch(int searchId, int start, int end, int classType){
  int mid = ((start + end)/2);
  int idValue = -1;
  switch(classType){
    case 0:
      idValue = this->userList[mid].getIdValue();
      if(abs(start - end) == 1){
        if(this->userList[start].getIdValue() == searchId){
          return start;
        }else if(this->userList[end].getIdValue() == searchId){
          return end;
        }else{
          return -1;
        }
      }
      break;
    case 1:
      idValue = this->ticketList[mid].getIdValue();
      if(abs(start - end) == 1){
        if(this->ticketList[start].getIdValue() == searchId){
          return start;
        }else if(this->ticketList[end].getIdValue() == searchId){
          return end;
        }else{
          return -1;
        }
      }
      break;
    case 2:
      idValue = this->busList[mid].getIdValue();
      if(abs(start - end) == 1){
        if(this->busList[start].getIdValue() == searchId){
          return start;
        }else if(this->busList[end].getIdValue() == searchId){
          return end;
        }else{
          return -1;
        }
      }
      break;
    case 3:
      idValue = this->stopList[mid].getIdValue();
      if(abs(start - end) == 1){
        if(this->stopList[start].getIdValue() == searchId){
          return start;
        }else if(this->stopList[end].getIdValue() == searchId){
          return end;
        }else{
          return -1;
        }
      }
      break;
    case 4:
      idValue = this->routeList[mid].getIdValue();
      if(abs(start - end) == 1){
        if(this->routeList[start].getIdValue() == searchId){
          return start;
        }else if(this->routeList[end].getIdValue() == searchId){
          return end;
        }else{
          return -1;
        }
      }
      break;
    default:
      return idValue;
  }
  if(idValue == -1){
    return -1;
  }
  if(searchId > idValue){
    start = mid;
    return this->binarySearch(searchId, start, end, classType);
  }else if(searchId < idValue){
    end = mid;
    return this->binarySearch(searchId, start, end, classType);
  }else{
    return mid;
  }
}

// finds the index of the user class with the matching id, returns a -1 if not found
int ReadWrite::findUser(std::string id){
  int i = extractIdVal(id, 'U');
  if(i == -1){
    return -1;
  }
  return binarySearch(i, 0, this->userList.size() - 1, 0);
}

// finds the index of the ticket class with the matching id, returns a -1 if not found
int ReadWrite::findTicket(std::string id){
  int i = extractIdVal(id, 'T');
  if(i == -1){
    return -1;
  }
  return binarySearch(i, 0, this->ticketList.size() - 1, 1);
}

// finds the index of the stop class with the matching id, returns a -1 if not found
int ReadWrite::findStop(std::string id){
  int i = extractIdVal(id, 'S');
  if(i == -1){
    return -1;
  }
  return binarySearch(i, 0, this->stopList.size() - 1, 3);
}

// finds the index of the bus class with the matching id, returns a -1 if not found
int ReadWrite::findBus(std::string id){
  int i = extractIdVal(id, 'B');
  if(i == -1){
    return -1;
  }
  return binarySearch(i, 0, this->busList.size() - 1, 2);
}

// finds the index of the route class with the matching id, returns a -1 if not found
int ReadWrite::findRoute(std::string id){
  int i = extractIdVal(id, 'R');
  if(i == -1){
    return -1;
  }
  return binarySearch(i, 0, this->routeList.size() - 1, 4);
}

// adds a user to the user list
void ReadWrite::addUser(User u){
  this->userList.push_back(u);
}

// adds a ticket to the vector list
void ReadWrite::addTicket(Ticket t){
  this->ticketList.push_back(t);
}

// returns the current user id
int ReadWrite::getCurrentUserId(){
  return this->currentUserId;
}

// returns the current ticket id
int ReadWrite::getCurrentTicketId(){
  return this->currentTicketId;
}

void ReadWrite::updateCurrentUserId(){
  this->currentUserId++;
}

void ReadWrite::updateCurrentTicketId(){
  this->currentTicketId++;
}

// checks if the file exists
bool ReadWrite::fileExists(std::string filepath){
  std::ifstream file(filepath);
  if(!file){
    return false;
  }else{
    file.close();
    return true;
  }
}

// loads data from provided filepath into a 2 dimensional vector
std::vector<std::vector<std::string>> ReadWrite::loadFromFile(std::string filepath){
  std::string line;
  std::ifstream file(filepath);
  std::vector<std::vector<std::string>> finalClass;
  if(!file){
    std::cout << "The provided file does not exist" << std::endl;
    return finalClass;
  }
  if(file.is_open()){
    getline(file, line);
    getline(file, line);
    while(file){
      std::vector<std::string> classList;
      getline(file, line);
      if(line == ""){
        continue;
      }
      std::string temp;
      std::stringstream ss(line);
      while(getline(ss, temp, ',')){
        if(temp != ""){
          if(temp.back() == '\r' || temp.back() == '\n'){
            temp.pop_back();
          }
          classList.push_back(temp);
        }
      }
      finalClass.push_back(classList);
    }
    file.close();
    return finalClass;
  }
  std::cout << "File is not open" << std::endl;
  return finalClass;
}

// checks if row  of data matches the allowed number of arguments
bool ReadWrite::checkProperty(std::vector<std::string> dataVec, int capacity){
  if((dataVec.size()) % capacity != 0){
    return false;
  }
  return true;
}

// converts 2d vector containing strings into a vector of User objects
void ReadWrite::createUserList(std::vector<std::vector<std::string>> dataVec, int capacity){
  if(dataVec.size() <= 0){
    return;
  }
  int max = 0;
  for(int i = 0; i < dataVec.size(); i++){
    std::vector<std::string> tickets;
    if(!this->checkProperty(dataVec[i], capacity)){
      std::cout << "Provided user dataset is  malformed.";
      return;
    }
    if(dataVec[i][6] == this->nullVal){
    }else{
      tickets = splitString(';',dataVec[i][6]);
    }

    int balance = strToInt(dataVec[i][5]);
    if(balance == -1){
      std::cout << "USER: Balance is incorrectly formatted. Needs to be an integer greater than zero. Please correct your datafile." << std::endl;
      this->userList.clear();
      return;
    }
    std::vector<std::string> idParts = splitString('U',dataVec[i][4]);
    int idNum = strToInt(idParts[0]);
    if(idNum == -1){
      std::cout << "USER: Line " << (i+1) << ": the user id is incorrectly formatted" << std::endl;
      this->userList.clear();
      return;
    }
    if(idNum > max){
      max = idNum;
    }
    if(dataVec[i][6] == this->nullVal){
        User u(dataVec[i][0], dataVec[i][1], dataVec[i][2], dataVec[i][3], dataVec[i][4], balance);
        this->userList.push_back(u);
    }else{
        User u(dataVec[i][0], dataVec[i][1], dataVec[i][2], dataVec[i][3],  dataVec[i][4], balance, tickets);
        this->userList.push_back(u);
    }

  }
  this->currentUserId = max;
}

// converts 2d vector of strings into a vector of Ticket Objs
void ReadWrite::createTicketList(std::vector<std::vector<std::string>> dataVec, int capacity){
  if(dataVec.size() <= 0){
    return;
  }
  int max = 0;
  for(int i = 0; i < dataVec.size(); i++){
    if(!this->checkProperty(dataVec[i], capacity)){
      std::cout << "Tickets dataset is malformed" << std::endl;
      return;
    }
    std::time_t dateTime = extractTime(dataVec[i][5]);
    if(dateTime == -1){
      std::cout << "TICKET: Line " << (i+1) << ": incorrect value for bus time field" << std::endl;
      this->ticketList.clear();
      return;
    }
    int isValid = strToBoolean(dataVec[i][6]);
    if(isValid == -1){
      std::cout << "TICKET: Line " << (i+1) << ": incorrect value for validity field" << std::endl;
      this->ticketList.clear();
      return;
    }
    std::vector<std::string> idParts = splitString('T',dataVec[i][0]);
    int idNum = strToInt(idParts[0]);
    if(idNum == -1){
      std::cout << "TICKET: Line " << (i+1) << ": the user id is incorrectly formatted" << std::endl;
      this->ticketList.clear();
      return;
    }
    if(idNum > max){
      max = idNum;
    }
    Ticket t(dataVec[i][0], dataVec[i][1], dataVec[i][2], dataVec[i][3], dataVec[i][4], dateTime, isValid);
    this->ticketList.push_back(t);
  }
  this->currentTicketId = max;
}

// converts 2d vector of strings into Bus Objects
void ReadWrite::createBusList(std::vector<std::vector<std::string>> dataVec, int capacity){
  if(dataVec.size() <= 0){
    return;
  }
  for(int i = 0; i < dataVec.size(); i++){
    if(!this->checkProperty(dataVec[i], capacity)){
      std::cout << "Provided bus dataset is malformed" << std::endl;
      this->busList.clear();
      return;
    }
    int busCapacity = strToInt(dataVec[i][4]);
    int delayedStatus = strToBoolean(dataVec[i][5]);
    if(delayedStatus == -1){
        std::cout << "BUS: Line " << (i+1) << " of the bus dataset has an invalid value in the delayed status field." << std::endl;
       this->busList.clear();
       return;
    }
    if(busCapacity == -1){
      std::cout << "BUS: Line " << i << " of the bus dataset has an invalid value in place of the bus capacity." << std::endl;
      this->busList.clear();
      return;
    }
    Bus b(dataVec[i][0], dataVec[i][1], dataVec[i][2], dataVec[i][3], busCapacity, intToBoolean(delayedStatus));
    this->busList.push_back(b);
  }
}

// converts 2d vector of strings into a vector of Stop objects
void ReadWrite::createStopList(std::vector<std::vector<std::string>>dataVec, int capacity){
  if(dataVec.size() <= 0){
    return;
  }
  for(int i = 0; i < dataVec.size(); i++){
    if(!this->checkProperty(dataVec[i], capacity)){
      std::cout << "Provided stops dataset is malformed" << std::endl;
      return;
    }
    double xLocation = strToDouble(dataVec[i][2]);
    double yLocation = strToDouble(dataVec[i][3]);
    if(xLocation == -1){
      std::cout << "STOP: Latitude is malformed" << std::endl;
      this->stopList.clear();
      return;
    }
    if(yLocation == -1){
      std::cout << "STOP: Longitude is malformed" << std::endl;
      this->stopList.clear();
      return;
    }
    // check hashTable is correctly structured
    std::unordered_map<std::string, std::vector<std::string>> hashTable = stringToHashTable('>', '|', dataVec[i][5]);
    for(auto key : hashTable){
      if(this->findBus(key.first) == -1){
        std::cout << "STOP: An unknown bus id is used as a key in the stop timetable" << std::endl;
        this->stopList.clear();
        return;
      }
      for(std::string time : key.second){
        if(!isTime(time)){
          std::cout << dataVec[i][0] << std::endl;
          std::cout << "STOP: A time value in the timetable is incorrect" << std::endl;
          this->stopList.clear();
          return;
        }
      }
    }
    Stop s(dataVec[i][0], dataVec[i][1], xLocation, yLocation, splitString(';',   dataVec[i][4]), hashTable);
    this->stopList.push_back(s);
  }
}

// converts 2d vector of strings to a vector of Route objects
void ReadWrite::createRouteList(std::vector<std::vector<std::string>> dataVec, int capacity){
  if(dataVec.size() <= 0){
    return;
  }
  for(int i = 0; i < dataVec.size(); i++){
    if(!this->checkProperty(dataVec[i], capacity)){
      std::cout << "Routes dataset is malformed" << std::endl;
      return;
    }
    std::string direction = parseDir(dataVec[i][1]);
    std::vector<std::string> stops = splitString(';', dataVec[i][4]);
    double dist = strToDouble(dataVec[i][6]);
    int convertedTime = strToInt(dataVec[i][7]);
    int diversion = strToBoolean(dataVec[i][8]);

    if(diversion == -1){
      std::cout << "ROUTE: Line " << (i+1) << ":Diversion is incorrectly formatted" << std::endl;
      this->routeList.clear();
      return;
    }

    if(direction == "A"){
      std::cout << "ROUTE: Direction is incorrectly formatted" << std::endl;
      this->routeList.clear();
      return;
    }
    if(dist == -1){
      std::cout << "ROUTE: Distance is incorrectly formatted" << std::endl;
      this->routeList.clear();
      return;
    }
    if(convertedTime == -1){
      std::cout << "ROUTE: Time is incorrectly formatted" << std::endl;
      this->routeList.clear();
      return;
    }

    Route r(dataVec[i][0], direction, dataVec[i][2], dataVec[i][3], stops, dist, convertedTime, intToBoolean(diversion), splitString(';', dataVec[i][5]));
    this->routeList.push_back(r);
  }
}

// calls the correct function to parse the data of a provided 2d vector of strings
void ReadWrite::parseData(std::vector<std::vector<std::string>> classValues, int datasetType){
  const int userArgCount = 7;
  const int ticketArgCount = 7;
  const int busArgCount = 6;
  const int stopArgCount = 6;
  const int routeArgCount = 9;

  switch(datasetType){
      case 0:
        this->createUserList(classValues, userArgCount);
        break;
      case 1:
        this->createBusList(classValues, busArgCount);
        break;
      case 2:
        this->createTicketList(classValues, ticketArgCount);
        break;
      case 3:
        this->createStopList(classValues, stopArgCount);
        break;
      case 4:
        this->createRouteList(classValues, routeArgCount);
        break;
  }
}

// converts information of a user class into a format to be stored in a data file
std::string ReadWrite::createUserStr(User user){
  std::string finalStr = "";
  std::string fname, lname, pwd, email, id, balance, tickets;
  tickets = "";
  std::vector<std::string> t = user.getTickets();
  fname = user.getFname();
  lname = user.getLname();
  pwd = user.getPassword();
  email = user.getEmail();
  id = user.getUserID();
  balance = std::to_string(user.getUserBalance());
  if(t.size() == 0){
    tickets = "NULL";
  }
  for(int i = 0; i < t.size(); i++){
    if(i != t.size() - 1){
      tickets = tickets + t[i] + ";";
    }else{
      tickets = tickets + t[i];
    }

  }
  finalStr = fname + "," + lname + "," + pwd + "," + email + "," + id + "," + balance + "," + tickets;
  return  finalStr;
}

// converts information of a ticket  class into a format to be stored in a data file
std::string ReadWrite:: createTicketStr(Ticket ticket){
  std::string finalStr = "";
  std::string ticketId, busId, startLoc, endLoc, routeId, isValid;
  std::stringstream buffer;
  ticketId = ticket.getTicketID();
  busId = ticket.getBusAssignedTo();
  startLoc = ticket.getStartLocation();
  endLoc = ticket.getEndLocation();
  routeId = ticket.getRouteReference();
  time_t time = ticket.getBusTime();
  tm* _tm = localtime(&time);
  bool validity = ticket.isTicketValid();
  if(validity){
    isValid = "TRUE";
  }else{
    isValid = "FALSE";
  }
  buffer << std::put_time(_tm, "%m/%d/%Y:%H:%M:%S");
  std::string timeStr;
  if(buffer.fail()){
    timeStr = "NULL";
  }else{
    timeStr = buffer.str();
  }
  finalStr = ticketId + "," + busId + "," + startLoc + "," + endLoc + "," + routeId + "," + timeStr + "," + isValid;
  return finalStr;
}
