/*
User.hpp
authors: M00774667, M00916537, M00829986, M00843428, M00951627
created: 23/03/2024
updated: 20/04/2024
*/
#ifndef USER_HPP
#define USER_HPP

// Include the necessary packages.
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>
#include "IDObject.hpp"

// Forward declaration to avoid compiling errors.
class Ticket;

class User : public IDObject{
// User class private member variables.
private:
    std::string fname, lname, password, email;
    int userBalance;
    std::vector<std::string> ticketsPurchased;
// User class public methods.
public:
    // Constructor for the class with all the parameters.
    User(
        std::string fname,
        std::string lname,
        std::string password,
        std::string email,
        std::string userID,
        int userBalance,
        std::vector<std::string> ticketsPurchased);
    // Overload constructor for new users with the necessary parameters.
    User(
        std::string fname,
        std::string lname,
        std::string password,
        std::string email,
        std::string userID,
        int userBalance);

    // Getter methods.
    std::string getUserID();
    std::string getFname();
    std::string getLname();
    std::string getPassword();
    std::string getEmail();
    int getUserBalance();
    std::vector<std::string> getTickets();

    // Setter method.
    void deductFromUsersBalance(int);

    // Methods to add tickets that are purchased, increase user account balance, and display user account information.
    void addPurchasedTicket(std::string);
    void addToUserBalance(int);
    void userInfoToString();
};
#endif
