/*
Menu.hpp
authors: M00774667, M00916537, M00829986, M00843428, M00951627
created: 01/03/2024
updated: 21/04/2024
*/
#ifndef MENU_HPP
#define MENU_HPP
#include <iostream>
#include <string>
#include <unordered_set>
#include <sstream>
#include <regex>
#include <cstdlib>
#include <algorithm>
//Forward declaration to avoid compiling errors
class User;
class Ticket;
class Stop;
class Route;
class Menu{
    private:
    User* userLoggedIn;
    std::vector<std::string> datasets;
    public:
        static int lastUserID;
        std::vector<std::string> getDatasets();
        void setDatasets(std::vector<std::string> dataVec);
        std::string printMenu();
        void registration();
        void login();
        bool verifyUserName(std::string);
        bool verifyUserPsw(std::string);
        bool verifyUserSurname(std::string);
        bool verifyUserEmail(std::string);
        bool verifyUserID(std::string);
        std::string secondMenu();
        int ticketPrice(Route* selectedRoute);
        void findRoute();
        void showRouteStops(Route* route);
        void displayTicketInformation(Ticket *ticketObj);
        void showObtainedTickets();
        void showTimeTable();
        std::string accountSettings();
        void increaseBalance();
        void initialDatasetMenu();
        void logout();

        };
#endif
