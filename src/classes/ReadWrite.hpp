/*
ReadWrite.hpp
authors: M00774667, M00916537, M00829986, M00843428, M00951627
created: 01/03/2024
updated: 21/04/2024
*/
#ifndef PARSE_HPP
#define PARSE_HPP
#include <iostream>
#include <vector>
#include "Bus.hpp"
#include "User.hpp"
#include "Ticket.hpp"
#include "Stop.hpp"
#include "Route.hpp"
#include "Sort.hpp"

class ReadWrite{
  private:
    ReadWrite();
    std::string nullVal;
    std::vector<Bus> busList;
    std::vector<Ticket> ticketList;
    std::vector<User> userList;
    std::vector<Stop> stopList;
    std::vector<Route> routeList;
    int currentUserId, currentTicketId;
    bool fileExists(std::string filepath);
    bool checkProperty(std::vector<std::string> dataVec, int capacity);
    std::string createUserStr(User user);
    std::string createTicketStr(Ticket ticket);
    void sortUsers();
    void sortTickets();
    void sortBuses();
    void sortRoutes();
    void sortStops();
    void sortAll();
    int binarySearch(int id, int start, int end, int classType);

  public:
    static ReadWrite& instance();
    ~ReadWrite();
    void clearAllData();
    void updateCurrentUserId();
    void updateCurrentTicketId();
    std::vector<std::vector<std::string>> loadFromFile(std::string filepath);
    int getCurrentUserId();
    int getCurrentTicketId();
    User* getUser(std::string id);
    Ticket* getTicket(std::string id);
    Stop* getStop(std::string id);
    Bus* getBus(std::string id);
    Route* getRoute(std::string id);
    std::vector<Bus> getBusList();
    std::vector<Ticket> getTicketList();
    std::vector<User> getUserList();
    std::vector<Stop> getStopList();
    std::vector<Route> getRouteList();
    int findUser(std::string userId);
    int findTicket(std::string ticketId);
    int findStop(std::string stopId);
    int findRoute(std::string routeId);
    int findBus(std::string busId);
    void removeUser(int idx);
    void removeTicket(int idx);
    bool init(std::string upath, std::string bPath, std::string tPath, std::string sPath, std::string rPath);
    void addUser(User u);
    void addTicket(Ticket t);
    void saveUsers(std::string filename);
    void saveTickets(std::string filename);
    void saveData(std::vector<std::string> datasets);
    void parseData(std::vector<std::vector<std::string>> classValues, int datasetType);
    void createUserList(std::vector<std::vector<std::string>> dataVec, int capacity);
    void createTicketList(std::vector<std::vector<std::string>> dataVec, int capacity);
    void createBusList(std::vector<std::vector<std::string>> dataVec, int capacity);
    void createRouteList(std::vector<std::vector<std::string>> dataVec, int capacity);
    void createStopList(std::vector<std::vector<std::string>> dataVec, int capacity);

};
#endif
