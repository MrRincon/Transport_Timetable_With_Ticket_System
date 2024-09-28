/*
User.cpp
authors: M00774667, M00916537, M00829986, M00843428, M00951627
created: 02/03/2024
updated: 20/04/2024
*/
#include "User.hpp"

// Constructor for the class with all the parameters.
User::User(std::string fname, std::string lname, std::string password, std::string email,
std::string userID, int userBalance, std::vector<std::string> ticketsPurchased){
  this->idHeader = 'U';
  this->fname = fname;
  this->lname = lname;
  this->password = password;
  this->email = email;
  this->id = userID;
  this->userBalance = userBalance;
  this->ticketsPurchased = ticketsPurchased;
}

// Overload constructor for new users with the necessary parameters.
User::User(std::string fname, std::string lname, std::string password,
std::string email, std::string userID, int userBalance){
  this->idHeader = 'U';
  this->fname = fname;
  this->lname = lname;
  this->password = password;
  this->email = email;
  this->id = userID;
  this->userBalance = userBalance;
  this->ticketsPurchased = std::vector<std::string>(); // Initializing the empty ticket list vector.
}

// Getter methods
std::string User::getUserID(){
  return id;
}

std::string User::getFname(){
  return fname;
}

std::string User::getLname(){
  return lname;
}

std::string User::getPassword(){
  return password;
}

std::string User::getEmail(){
  return email;
}

int User::getUserBalance(){
  return userBalance;
}

std::vector<std::string> User::getTickets(){
  return ticketsPurchased;
}

// Method to add a ticket purchased by the user, to their account.
void User::addPurchasedTicket(std::string newTicket){
  ticketsPurchased.push_back(newTicket);
}

// Method to add a specified amount to the users account balance.
void User::addToUserBalance(int balanceToAdd){
  userBalance = userBalance + balanceToAdd;
}
// Method to add a specified amount to the users account balance.
void User::deductFromUsersBalance(int balanceTodeduct){
  userBalance = userBalance - balanceTodeduct;
}

// Method to display the users account information in a formatted table.
void User::userInfoToString(){
  std::ostringstream builder; // Create an ostringstream to hold the table.
  builder << "--------------------------------------------------------------\n"
          // Set each lines width of each line, its position, and contents.
          << "| UserID          | " << std::setw(40) << std::left << getUserID() << " |\n"
          << "| Forename        | " << std::setw(40) << std::left << getFname() << " |\n"
          << "| Surname         | " << std::setw(40) << std::left << getLname() << " |\n"
          << "| Email           | " << std::setw(40) << std::left << getEmail() << " |\n"
          << "| Password        | " << std::setw(40) << std::left << getPassword() << " |\n"
          << "| Account balance | £" << std::setw(39) << std::left << getUserBalance() << " |\n"
          << "--------------------------------------------------------------";
  std::cout << "\nUser Details: \n" << builder.str() << std::endl; // display the user details within the builder.
}
