/*
Menu.cpp
authors: M00774667, M00916537, M00829986, M00843428, M00951627
created: 01/03/2024
updated: 21/04/2024
*/
#include "Menu.hpp"
#include "User.hpp"
#include "Stop.hpp"
#include "ReadWrite.hpp"
#include "Bus.hpp"
#include "Route.hpp"
#include "Ticket.hpp"
#include "Helper.hpp"

// Global variables
int Menu::lastUserID = 0; // Initilise the static variable which keeps the increment of the userID
ReadWrite &rw = ReadWrite::instance();

// getter method for vector of dataset;
std::vector<std::string> Menu::getDatasets()
{
    return datasets;
}

// setter method for vector of datasets
void Menu::setDatasets(std::vector<std::string> dataVec)
{
    datasets = dataVec;
}

// Method to create and display the menu for user access
std::string Menu::printMenu()
{
    std::string input = "";
    while (true)
    {
        std::cout << "\n--------------------------------------------\n"
                  << "| Enter the option that you want to access |\n"
                  << "|------------------------------------------|\n"
                  << "| 1. User Login.                           |\n"
                  << "| 2. User Registration.                    |\n"
                  << "| 0. Exit.                                 |\n"
                  << "--------------------------------------------\n"
                  << std::endl;
        std::cout << "Choice: ";
        std::getline(std::cin, input);
        if (input == "1" || input == "2" || input == "0")
        {
            try // Try catch for input errors
            {
                switch (std::stoi(input)) // Switch to select whether to log in, register or end the program
                {
                case 1:
                    login();
                    break;
                case 2:
                    registration();
                    break;
                case 0:
                    std::cout << "You have chosen to exit the system. Goodbye!" << std::endl;
                    std::exit(0);
                default:
                    break;
                }
                return input;
            }
            catch (const std::invalid_argument &err)
            {
                std::cout << "Invalid input, please enter a number!" << std::endl;
                continue;
            }
        }
        else
        {
            std::cout << "Invalid option, please enter a number e.g. 0, 1, or 2! " << std::endl;
        }
    }
}

// Method to register a new user and added it to the CSV
void Menu::registration()
{
    std::string name, surname, password, email = "";
    rw.updateCurrentUserId();
    std::string userID = "U" + std::to_string(rw.getCurrentUserId());
    bool fnameSelected = false, snameSelected = false, emailSelected = false, passwordSelected = false;
    std::cout << "\nYou have selected user registration.\n";
    while (!fnameSelected)
    {
        std::cout << "\nPlease enter your name: ";
        std::getline(std::cin, name);
        if (verifyUserName(name)) // If statement to check if the user name is acceptable
        {
            std::cout << "Name accepted." << std::endl;
            fnameSelected = true;
        }
        else
        {
            std::cout << "\nThe choosen name is not valid. Try again!" << std::endl;
        }
    }

    while (!snameSelected)
    {
        std::cout << "\nPlease enter your surname: ";
        std::getline(std::cin, surname);
        if (verifyUserSurname(surname)) // If statement to check if the user surname is acceptable
        {
            std::cout << "Surname accepted." << std::endl;
            snameSelected = true;
        }
        else
        {
            std::cout << "\nThe choosen surname is not valid. Try again!" << std::endl;
        }
    }

    while (!emailSelected)
    {
        std::cout << "\nPlease enter your email address:";
        std::getline(std::cin, email);
        if (verifyUserEmail(email)) // If statement to check if the user email is acceptable and unique
        {
            std::cout << "Email accepted." << std::endl;
            emailSelected = true;
        }
    }

    while (!passwordSelected)
    {
        std::cout << "\nPlease enter your password below, the password must contain at least one letter, one number, and at least 6 charecters long. No special characters" << std::endl;
        std::cout << "Please choose a password: ";
        std::getline(std::cin, password);
        if (verifyUserPsw(password)) // If statement to check if the user password is acceptable
        {
            std::cout << "Password accepted.\n"
                      << std::endl;
            passwordSelected = true;
        }
        else
        {
            std::cout << "\nThe choosen password in not valid. Try again!" << std::endl;
        }
    }
    User newUser(name, surname, password, email, userID, 0); // Create new user object
    rw.addUser(newUser);                                     // Register the user and after let the user know the ID they will have
    userLoggedIn = rw.getUser(userID);
    std::cout << "Registration successfull!\n"
              << "You have been assigned this ID: " << userLoggedIn->getUserID() << "\nPlease store this ID as it will not be displayed again." << std::endl;
    secondMenu(); // Print the second menu
}

// Method containing the login functionality.
void Menu::login()
{
    if(rw.getUserList().size() <= 0){
      std::cout << "There are no existing users." << std::endl;
      printMenu();
      return;
    }
    std::string userID, password = "";
    std::cout << "\nYou have selected user login." << std::endl;
    bool userIdSelected, passwordSelected;
    while (!userIdSelected)
    {
        std::cout << "Please enter your user ID: ";
        std::getline(std::cin, userID);
        if (verifyUserID(userID)) // Check if the userID regex is correct and if the user exists
        {
            std::cout << "User ID matched." << std::endl;
            userIdSelected = true;
        }
    }
    while (!passwordSelected)
    {
        std::cout << "\nPlease enter your password: ";
        std::getline(std::cin, password);
        if (verifyUserPsw(password)) // Check for the pattern of the password
        {

            if (rw.getUser(userID)->getPassword() == password) // Check that the password matches the user's password
            {
                userLoggedIn = rw.getUser(userID); // Assign this object to the global variable pointer
                std::cout << "Password matched!" << std::endl;
                passwordSelected = true;
            }
            else
            {
                std::cout << "Wrong password, try again!" << std::endl;
            }
        }
        else
        {
            std::cout << "Your password must have 6 characters with \na capital letter and a number. No special characters, try again!" << std::endl;
        }
    }
    secondMenu(); // Print the second menu options if everything is correct
}

// Method for name regex check
bool Menu::verifyUserName(std::string name)
{
    std::regex rgxUserName("[a-zA-Z -]+"); // Name regex
    return regex_match(name, rgxUserName);
}

// Method for password regex check
bool Menu::verifyUserPsw(std::string psw)
{
    std::regex rgxUserPsw("(?=.*[A-Za-z])(?=.*\\d)[A-Za-z\\d]{6,}"); // Password regex
    return regex_match(psw, rgxUserPsw);
}

// Method for surname regex check
bool Menu::verifyUserSurname(std::string surname)
{
    std::regex rgxUserSurname("[a-zA-Z -]+"); // Surname regex
    return regex_match(surname, rgxUserSurname);
}

// Method for email address regex check and if the email is unique
bool Menu::verifyUserEmail(std::string email)
{
    std::regex rgxUserEmail("(\\w+)(\\.|_)?(\\w*)@(\\w+)(\\.(\\w+))+");
    if (regex_match(email, rgxUserEmail)) // If statement to check if the Email address matches with the regex
    {
        bool uniqueUser = true;
        for (User user : rw.getUserList()) // Loop through all the users
        {
            if (email == user.getEmail()) // If a user has the same email, set the boolean uniqueUser to false
            {
                uniqueUser = false;
            }
        }
        if (uniqueUser) // If user is unique, return true.
        {
            return true;
        }
        else
        {
            std::cout << "\nThis email has already been registered with an account. Try again." << std::endl;
            return false;
        }
    }
    else
    {
        std::cout << "\nThe chosen email address pattern is not valid. Try again." << std::endl;
        return false;
    }
}

// Method for userID regex check and if the user ID exists
bool Menu::verifyUserID(std::string userID)
{
    std::regex rgxUserID("^[A-Z0-9]+$"); // UserID regex
    if (regex_match(userID, rgxUserID))  // If statement to check if the userID matches with the regex
    {
        User *user = rw.getUser(userID); // User pointer variable to be filled with the user address
        if (user)                        // If user is not a nullptr(0), the user has been found
        {
            return true;
        }
        else
        {
            std::cout << "User ID does not match. Try again!" << std::endl;
            return false;
        }
    }
    else
    {
        std::cout << "The pattern for the userID is not allowed,\nplease start the pattern with a capital 'U' and then add the numbers of your ID" << std::endl;
        return false;
    }
}

// Method to display the second menu for the program functionality after the registration or logging in
std::string Menu::secondMenu()
{
    std::string input = "";
    std::cout << "\nWelcome to the main menu." << std::endl;
    while (true)
    {
        std::cout << "\n--------------------------------------------\n"
                  << "| Enter the option that you want to access |\n"
                  << "|------------------------------------------|\n"
                  << "| 1. Find a route.                         |\n"
                  << "| 2. Show obtained tickets.                |\n"
                  << "| 3. Show timetable at the bus stop.       |\n"
                  << "| 9. Account settings.                     |\n"
                  << "| 0. Log-out.                              |\n"
                  << "--------------------------------------------\n"
                  << std::endl;
        std::cout << "Choice: ";
        std::getline(std::cin, input);
        if (input == "1" || input == "2" || input == "3" || input == "9" || input == "0")
        {
            try
            {
                switch (std::stoi(input))
                {
                case 1:
                    findRoute(); // Case to find route
                    break;
                case 2:
                    showObtainedTickets(); // Case to show obtained tickets
                    break;
                case 3:
                    showTimeTable(); // Case to show the time table
                    break;
                case 9:
                    accountSettings(); // Case for the account settings
                    break;
                case 0:
                    std::cout << "You have chosen to logout.\n"
                              << std::endl;
                    logout();
                    break;
                default:
                    break;
                }
                return input;
            }
            catch (const std::invalid_argument &err)
            {
                std::cout << "Invalid input, please enter a number!" << std::endl;
                continue;
            }
        }
        else
        {
            std::cout << "Invalid option, please enter a number e.g. 0, 1, 2, or 3! " << std::endl;
        }
    }
}

// Method to calculate price, according to the distance
int Menu::ticketPrice(Route *selectedRoute)
{
    int stopsSize = selectedRoute->getRouteStopsOrder().size();
    return stopsSize;
}

// Method to find a route
void Menu::findRoute()
{
    std::cout << "\nAll bus stops:" << std::endl;
    std::ostringstream builder; // Create an ostringstream to hold the table.
    builder << "-----------------------------\n";
    for (Stop s : rw.getStopList())
    {
        builder << "| " << std::setw(4) << std::left << s.getStopID() << "| " << std::setw(20) << std::left << s.getStopName() << "|" << std::endl;
    }
    builder << "-----------------------------\n";
    std::cout << builder.str() << std::endl; // display the details within the builder.
    std::string startPointID, endPointID = "";
    std::cout << "Enter the stop you want to start your route at (S1, S5, S10). " << std::endl;
    Stop *endPoint, *startPoint;
    bool correctInput = false;
    while (!(correctInput)) // do the ckeck if the stop exists
    {
        std::cout << "Starting bus stop or END to return to main menu: ";
        std::getline(std::cin, startPointID);
        if(startPointID == "END"){
          secondMenu();
          return;
        }
        startPoint = rw.getStop(startPointID); // get the start point
        if (startPoint == nullptr)
        {
            std::cout << "Start point " << startPointID << " is not found.\n"
                      << "Please re-submit the start location.\n";
            std::getline(std::cin, startPointID);
        }
        else
        {
            correctInput = true;
        }
    }
    correctInput = false; // reset the boolean
    while (!(correctInput)) // do the ckeck if the stop exists
    {
        std::cout << "Enter the stop you want to end your journey at (S2, S4, S5). " << std::endl;
        std::cout << "Ending bus stop or END to return to main menu: ";
        std::getline(std::cin, endPointID);
        if(endPointID == "END"){
          secondMenu();
          return;
        }
        endPoint = rw.getStop(endPointID); // get the end point
        if (endPoint == nullptr)
        {
            std::cout << "End point " << endPointID << " is not found.\n"
                      << "Please re-submit the end location.\n";
        }
        else
        {
            correctInput = true;
        }
    }
    // if the same start and end points are given then an error message is displayed and the user is returned to the main menu
    if (startPoint->getStopID() == endPoint->getStopID())
    {
        std::cout << "The starting stop and destination stop cannot be the same." << std::endl;
        secondMenu();
        return;
    }
    std::vector<std::string> routeAssigned = startPoint->getRoutesAssigned();
    std::vector<Route *> foundRoutes;
    // finds all routes in which the starting stop is earlier in the route list than the ending stop
    // if the route does not have both stops then it is not included
    for (std::string routeId : routeAssigned)
    {
        Route *route = rw.getRoute(routeId);
        bool startFound = false;
        if (route)
        {
            std::vector<std::string> stops = route->getRouteStopsOrder();
            for (std::string stopId : stops)
            {
                if (!startFound)
                {
                    if (stopId == startPoint->getStopID())
                    {
                        startFound = true;
                    }
                }
                else
                {
                    if (stopId == endPoint->getStopID())
                    {
                        foundRoutes.push_back(route);
                        break;
                    }
                }
            }
        }
    }
    // if no routes meeting above criteria were found then the user is given the option to return to the main menu or to re enter their information
    if (foundRoutes.size() <= 0)
    {
        std::cout << "\nNo route found between these two stops." << std::endl;
        std::string mainMenuSelect;
        bool optionSelected = false;
        while(!optionSelected){
          std::cout << "Would  you like to return to the main menu? (Y/N): " << std::endl;
          std::getline(std::cin, mainMenuSelect);
          if(mainMenuSelect == "Y" || mainMenuSelect == "N"){
            optionSelected = true;
            if(mainMenuSelect == "Y"){
              secondMenu();
              return;
            }else{
              findRoute();
              return;
            }
          }
        }
    }
    else
    {
        // gets the timetable of the starting stop and displays all applicable routes
        std::unordered_map<std::string, std::vector<std::string>> stopTimetable = startPoint->getBussesAssigned();
        for(int i = 0; i < foundRoutes.size(); i++){
            std::ostringstream builder;
            builder << "\n-----------------------------------------------\n"
                    <<  "| ID: " << std::setw(3) << std::left << (i+1) << "|" << std::setw(35) << std::left << " Route Number: " + foundRoutes[i]->getRouteId() << " |";

            std::cout << builder.str() << std::endl; // print the table to the console.
            // displays all the stops of the route in order
            showRouteStops(foundRoutes[i]);
        }
        int frSize = foundRoutes.size();
        int routeSelectInt = -1;
        // asks the user to select a route from a provided list
        while(routeSelectInt < 1 || routeSelectInt > frSize){
            std::string routeSelect;
            std::cout << "Please select a route by its ID or enter 'END' to return to main menu: " << std::endl;
            std::getline(std::cin, routeSelect);
            if(routeSelect == "END"){
              secondMenu();
              return;
            }
            routeSelectInt = strToInt(routeSelect);
            if(routeSelectInt < 1 || routeSelectInt > frSize){
              std::cout << "Please make a valid selection." << std::endl;
            }
        }
        std::vector<std::string> bAssigned = foundRoutes[routeSelectInt - 1]->getBusesAssigned();
        int bSize = bAssigned.size();
        int busSelectInt = -1;
        // displays all buses which utilize the selected route
        std::ostringstream busBuilder; // Create an ostringstream to hold the table.

        for(int j = 0; j < bSize; j++){
            busBuilder << "\n---------------------------\n"
                    << "| ID: " << std::setw(3) << std::left << (j+1) << "| Bus Number: " << std::setw(3) << std::left << bAssigned[j] << "|";
        }
        busBuilder << "\n---------------------------";
        std::cout << busBuilder.str() << std::endl; // print the table to the console.

        // asks the user to select a bus for their ticket
        while(busSelectInt < 1 || busSelectInt > bSize){
            std::string busSelect;
            std::cout << "Please select a bus or enter 'END' to return to main menu: " << std::endl;
            std::getline(std::cin, busSelect);
            if(busSelect == "END"){
              secondMenu();
            return;
            }
            busSelectInt = strToInt(busSelect);
            if(busSelectInt < 1 || busSelectInt > bSize){
              std::cout << "Please make a valid selection." << std::endl;
            }
        }
        int tSize = stopTimetable[bAssigned[busSelectInt - 1]].size();
        int ticketSelectInt = -1;
        // displays all the bus times of the user's selected bus
        std::ostringstream timeBuilder; // Create an ostringstream to hold the table.

        for(int k = 0; k < tSize; k++){
            timeBuilder << "\n------------------\n"
                       << "| ID: " << std::setw(3) << std::left << (k+1) << "| " << stopTimetable[bAssigned[busSelectInt - 1]][k] + " |";
        }
        timeBuilder << "\n------------------";
        std::cout << timeBuilder.str() << std::endl; // print the table to the console.

        // asks the user to select a time for their ticket
        while(ticketSelectInt < 1 || ticketSelectInt > tSize){
            std::string ticketSelect;
            std::cout << "Please select a time or enter 'END' to return to main menu: " << std::endl;
            std::getline(std::cin, ticketSelect);
            if(ticketSelect == "END"){
              secondMenu();
            return;
            }
              ticketSelectInt = strToInt(ticketSelect);
            if(ticketSelectInt < 1 || ticketSelectInt > tSize){
              std::cout << "Please make a valid selection." << std::endl;
            }
        }
        const time_t ONE_DAY = 24 * 60 * 60;
        const int DAYS_OF_WEEK = 7;
        struct tm* ti;
        time_t availableTimes[DAYS_OF_WEEK];
        time_t hoursAndMins = extractHoursAndMins(stopTimetable[bAssigned[busSelectInt - 1]][ticketSelectInt - 1]);
        // displays the available dates the user can purchase a ticket for
        std::ostringstream dateBuilder;
        for(int i = 0; i < DAYS_OF_WEEK; i++){
            std::stringstream buffer;
            time_t currentTime;
            time(&currentTime);
            currentTime += i * ONE_DAY;
            ti = localtime(&currentTime);
            ti->tm_hour = 0;
            ti->tm_min = 0;
            ti->tm_sec = 0;
            currentTime = mktime(ti);
            currentTime += hoursAndMins;
            ti = localtime(&currentTime);
            buffer << std::put_time(ti, "%m/%d/%Y:%H:%M");
            if(buffer.fail()){
              std::cout << "Time failed to parse" << std::endl;
            return;
            }
            availableTimes[i] = currentTime;

            dateBuilder << "\n------------------------------------\n"
                        <<"| ID: " << std::setw(3) << std::left << (i+1) << "| Date: " << std::setw(16) << std::left << buffer.str() << "  |";
        }
        dateBuilder << "\n------------------------------------";
        std::cout << dateBuilder.str() << std::endl; // print the table to the console.

        int timeSelectInt = -1;
        // asks the user to select a date for their ticket
        while(timeSelectInt < 1 || timeSelectInt > DAYS_OF_WEEK){
            std::string timeSelect;
            std::cout << "Please select the ID for the date of the ticket or enter 'END' to return to main menu: " << std::endl;
            std::getline(std::cin, timeSelect);
            if(timeSelect == "END"){
              secondMenu();
              return;
            }
            timeSelectInt = strToInt(timeSelect);
            if(timeSelectInt < 1 || timeSelectInt > DAYS_OF_WEEK);
        }
        int ticketVal = ticketPrice(foundRoutes[routeSelectInt - 1]);
        bool purchaseSelectionMade;
        while(!purchaseSelectionMade){
            std::string purchaseSelect;
            std::cout << "The price of your ticket is: £" << ticketVal << std::endl;
            std::cout << "Would you like to purchase the ticket? (Y/N): ";
            std::getline(std::cin, purchaseSelect);
            if(purchaseSelect == "Y" || purchaseSelect == "N"){
                purchaseSelectionMade = true;
                if(purchaseSelect == "N"){
                    std::cout << "Transaction cancelled, returning to the main menu..." << std::endl;
                    secondMenu();
                    return;
                }
            }
        }
        if(userLoggedIn->getUserBalance() >= ticketVal){
            userLoggedIn->deductFromUsersBalance(ticketVal);
            rw.updateCurrentTicketId();
            // ticket id assigned to new ticket
            std::string tid = "T" + std::to_string(rw.getCurrentTicketId());
            // ticket object is created
            Ticket t(tid, bAssigned[busSelectInt - 1], startPoint->getStopID(), endPoint->getStopID(), foundRoutes[routeSelectInt - 1]->getRouteId(), availableTimes[timeSelectInt - 1], true);
            // add ticket to ticketlist
            rw.addTicket(t);
            // add ticket to the user that is logged in
            userLoggedIn->addPurchasedTicket(tid);
            std::cout << "Ticket purchased successfully" << std::endl;
            secondMenu();
        }else{
            std::cout << "Insufficient funds, Please navigate to 'Account settings' to upate your acccount balance." << std::endl;
            secondMenu();
        }
    }
}

// Method to show the routes stops.
void Menu::showRouteStops(Route *route)
{
    std::vector<std::string> stops = route->getRouteStopsOrder();
    std::string formattedStops;
    for (int i = 0; i < stops.size(); i++)
    {
        if (i != stops.size() - 1)
        {
            formattedStops +=  stops[i] + "-->";
        }
        else
        {
            formattedStops += stops[i];
        }
    }
    std::ostringstream builder;
    builder << "-----------------------------------------------\n"
            <<  "| Route order: " << std::setw(30) << std::left << formattedStops << " |"
            << "\n-----------------------------------------------";
            std::cout << builder.str() << std::endl; // print the table to the console.
}

// A 'toString' method to display the ticket information.
void Menu::displayTicketInformation(Ticket *ticketObj)
{
    // Get the bus time and convert it to a human readable string.
    time_t busTime = ticketObj->getBusTime();
    std::tm *timeInfo = std::localtime(&busTime);
    std::ostringstream formattedTime;
    formattedTime << std::put_time(timeInfo, "%m/%d/%Y:%H:%M");
    std::string timeString = formattedTime.str();

    std::string validity;
    if (ticketObj->isTicketValid() == true)
    {
        validity = "Valid";
    }
    else
    {
        validity = "Not Valid / Expired";
    }

    Stop *startLocationName = rw.getStop(ticketObj->getStartLocation()); // get the start point
    Stop *endLocationName = rw.getStop(ticketObj->getEndLocation());     // get the start point

    // Create an ostringstream to hold the ticket information formatted in a table.
    std::ostringstream builder;
    builder << "\n---------------------------------------------------\n"
            << "| TicketID        |" << std::setw(30) << std::left << ticketObj->getTicketID() << " |\n"
            << "| Bus assigned to |" << std::setw(30) << std::left << ticketObj->getBusAssignedTo() << " |\n"
            << "| Departure time  |" << std::setw(30) << std::left << timeString << " |\n"
            << "| Start location  |" << std::setw(30) << std::left << ticketObj->getStartLocation() + ", " + startLocationName->getStopName() << " |\n"
            << "| End location    |" << std::setw(30) << std::left << ticketObj->getEndLocation() + ", " + endLocationName->getStopName() << " |\n"
            << "| Route           |" << std::setw(30) << std::left << ticketObj->getRouteReference() << " |\n"
            << "| Valid           |" << std::setw(30) << std::left << validity << " |\n"
            << "---------------------------------------------------";
    std::cout << builder.str() << std::endl; // print the table to the console.
}

// Method to display obtained tickets
void Menu::showObtainedTickets()
{
    if(rw.getTicketList().size() <= 0){
      std::cout << "There are no tickets currently available to be displayed" << std::endl;
      secondMenu();
      return;
    }
    std::vector<std::string> tickets = userLoggedIn->getTickets();
    if (tickets.empty())
    {
        std::cout << "\nThis account currently has no tickets, please purchase tickets for them to show here." << std::endl;
    }
    else
    {
        for (std::string ticket : tickets)
        {
            Ticket *ticketObj = rw.getTicket(ticket);
            if (ticketObj != nullptr)
            {
                displayTicketInformation(ticketObj);
            }
            else
            {
                std::cout << "\nFailed to find ticket information for ticket ID: " << ticket << std::endl;
            }
        }
    }
    std::string input;
    while (input != "0")
    {
        std::cout << "\nEnter '0' when ready to return back to the menu."
                  << std::endl;
        std::getline(std::cin, input);
        if (input == "0")
        {
            secondMenu(); // return after back to the menu
        }
    }
}

// Method to display a timetable with possible buses and time frequencies
void Menu::showTimeTable()
{
    std::string stopID;
    while (true)
    {
        std::cout << "\nAll bus stops:" << std::endl;
        std::ostringstream builder; // Create an ostringstream to hold the table.
        builder << "-----------------------------\n";
        for (Stop s : rw.getStopList())
        {
            builder << "| " << std::setw(4) << std::left << s.getStopID() << "| " << std::setw(20) << std::left << s.getStopName() << "|" << std::endl;
        }
        builder << "-----------------------------\n";
        std::cout << builder.str() << std::endl; // display the details within the builder.
        bool stopIDValid;
        while(!stopIDValid){
          std::cout << "Enter the stop ID to view the timetable or enter '0' to return to the menu: ";
          std::getline(std::cin, stopID);
          if (stopID == "0")
          {
              secondMenu();
              return;
          }
          // Check stopID corrolates to an existing stop.
          if(stopID == ""){
            std::cout << "Provide a valid input." << std::endl;
          }else{
            stopIDValid = true;
          }
        }
        int stopIndex = rw.findStop(stopID);
        if (stopIndex != -1)
        {
            break;
        }
        else
        {
            std::cout << "Stop with ID " << stopID << " not found." << std::endl;
        }
    }

    // Retrieve the stop object.
    Stop *stop = rw.getStop(stopID);

    // Retrieve the timetable for the stop.
    std::unordered_map<std::string, std::vector<std::string>> timetable = stop->getBussesAssigned();

    // Display the timetable.
    std::ostringstream builder; // Create an ostringstream to hold the table.
    std::string timesString;
    for (const auto &stopEntry : timetable)
    {
        builder << "----------------------------------------\n"
                // Set each lines width of each line, its position, and contents.
                << "|  Bus  |" << std::setw(30) << " Bus Arrival & Departure time |\n";
        for (const auto &times : stopEntry.second)
        {
            timesString += times + " ";
        }
        builder << "| " << std::setw(5) << std::left << stopEntry.first << " |" << std::setw(30) << std::left << "     " + timesString << "|\n"
                << "----------------------------------------\n";
        timesString = "";
    }

    std::cout << "\nTimetable for stop " << stopID << ": \n"
              << builder.str() << std::endl; // display the user details within the builder.
    showTimeTable();
}

// Method which displays the account settings options to the user and calls the necessary method from their choice.
std::string Menu::accountSettings()
{
    std::string option;
    std::cout << "\nAccount Settings" << std::endl;
    while (true)
    {
        std::cout << "\n--------------------------------------------\n"
                  << "| Enter the option that you want to access |\n"
                  << "|------------------------------------------|\n"
                  << "| 1. View user details.                    |\n"
                  << "| 2. Add balance.                          |\n"
                  << "| 0. Return back to the menu.              |\n"
                  << "--------------------------------------------\n"
                  << std::endl;
        std::cout << "Choice: ";
        std::getline(std::cin, option);
        if (option == "1" || option == "2" || option == "0")
        {
            try
            {
                switch (std::stoi(option))
                {
                case 1:
                    userLoggedIn->userInfoToString();
                    accountSettings();
                    break;
                case 2:
                    increaseBalance();
                    break;
                case 0:
                    secondMenu(); // return after back to the menu
                    break;
                default:
                    break;
                }
                return option;
            }
            catch (const std::invalid_argument &err)
            {
                std::cout << "Invalid input, please enter a number!" << std::endl;
                continue;
            }
        }
        else
        {
            std::cout << "Invalid input, please enter one of the numbers pointed above." << std::endl;
        }
    }
}

// Method to add to the user balance
void Menu::increaseBalance()
{
    bool correctInput = false;
    while (!correctInput)
    {
        std::string newBalanceAmount = "";
        std::cout << "To increase the balance\nPlease enter the ammount in pounds(£): £";
        std::getline(std::cin, newBalanceAmount);
        std::regex rgxBalance("^\\d+$");                    // Money regex
        if (std::regex_match(newBalanceAmount, rgxBalance)) // Check if input matches the pattern
        {
            userLoggedIn->addToUserBalance(std::stoi(newBalanceAmount)); // Add income to the logged in user
            correctInput = true;
        }
        else
        {
            std::cout << "Wrong input, please enter a whole number, no decimal values.";
        }
    }
    accountSettings();
}

// Method to input the name of the .csv files that will be used as a database
void Menu::initialDatasetMenu()
{
    ReadWrite &r = ReadWrite::instance();
    std::string usersFile, busesFile, ticketsFile, stopsFile, routesFile;

    std::cout << "Required files for the program to run: buses.csv, routes.csv, stops.csv."
              << "\nAdditional available files: users.csv, tickets.csv"
              << "\nPlease enter the file names for the initial data sets, individually, and in the order specified." << std::endl;

    bool allRequiredPresent = false;
    while (!allRequiredPresent)
    {
        // Attain the file name for the optional users dataset.
        std::cout << "\nEnter the file name for the initial users dataset or press Enter to skip: ";
        std::getline(std::cin, usersFile);
        if (!usersFile.empty() && usersFile.substr(usersFile.size() - 4) != ".csv")
        {
            std::cout << "Invalid dataset file format, please enter a valid .csv file or skip.\n";
            continue; // Restart the while loop.
        }

        // Attain the file name for the required buses dataset.
        std::cout << "Enter the file name for the initial buses dataset: ";
        std::getline(std::cin, busesFile);
        if (busesFile.empty() || busesFile.substr(busesFile.size() - 4) != ".csv")
        {
            std::cout << "Invalid dataset file format, please enter a valid .csv file.\n";
            continue;
        }

        // Attain the file name for the optional tickets dataset.
        std::cout << "Enter the file name for the initial tickets dataset or press Enter to skip: ";
        std::getline(std::cin, ticketsFile);
        if (!ticketsFile.empty() && ticketsFile.substr(ticketsFile.size() - 4) != ".csv")
        {
            std::cout << "Invalid dataset file format, please enter a valid .csv file or skip.\n";
            continue;
        }

        // Attain the file name for the required stops dataset.
        std::cout << "Enter the file name for the initial stops dataset: ";
        std::getline(std::cin, stopsFile);
        if (stopsFile.empty() || stopsFile.substr(stopsFile.size() - 4) != ".csv")
        {
            std::cout << "Invalid dataset file format, please enter a valid .csv file.\n";
            continue;
        }

        // Attain the file name for the required routes dataset.
        std::cout << "Enter the file name for the initial routes dataset: ";
        std::getline(std::cin, routesFile);
        if (routesFile.empty() || routesFile.substr(routesFile.size() - 4) != ".csv")
        {
            std::cout << "Invalid dataset file format, please enter a valid .csv file.\n";
            continue;
        }

        // Check if all required files are entered.
        if (!busesFile.empty() && !stopsFile.empty() && !routesFile.empty())
        {
            allRequiredPresent = true;
        }
        else
        {
            std::cout << "Please ensure all required dataset files are entered correctly.\n";
        }
    }

    // Initializing with the collected, correct filenames.
    if (allRequiredPresent)
    {
        std::cout << "All required dataset files are present, proceeding to initialize.\n";
        bool initSuccess = r.init(usersFile, busesFile, ticketsFile, stopsFile, routesFile); // Pass the files in their order to init().
        if (initSuccess)
        {
            std::vector<std::string> dataFiles;
            dataFiles.push_back(usersFile);
            dataFiles.push_back(busesFile);
            dataFiles.push_back(ticketsFile);
            dataFiles.push_back(stopsFile);
            dataFiles.push_back(stopsFile);
            setDatasets(dataFiles);
            std::cout << "Initialization successful. Datasets loaded.\n";
            system("cls");   // Clean the scren for windows OS
            system("clear");
        }
        else
        {
            std::cout << "Initialization failed. Please check the dataset files.\n";
            exit(0);
        }
    }
    else
    {
        exit(0);
    }
}

// Method to log out and clear the screen from the previous user information
void Menu::logout()
{
    std::string userID, password = "";
    system("cls");   // Clean the scren for windows OS
    system("clear"); // Clean the screen for Unix-Linux OS
    if(datasets[0] == ""){
        std::string userDataFile;
        while(userDataFile.empty() || userDataFile.substr(userDataFile.size() - 4) != ".csv"){
          std::cout << "No valid user data set was provided. Please provide a name to save changes to now. Filename must end with '.csv': " << std::endl;
          std::getline(std::cin, userDataFile);
          if(userDataFile.empty() || userDataFile.substr(userDataFile.size() - 4) != ".csv"){
            std::cout << "An invalid input was not provided" << std::endl;
          }
        }
        datasets[0] = userDataFile;
    }
    if(datasets[2] == ""){
      std::string ticketDataFile = "";
      while(ticketDataFile.empty() || ticketDataFile.substr(ticketDataFile.size() - 4) != ".csv"){
        std::cout << "No valid ticket data set was provided. Please provide a name to save changes to now. Filename must end with '.csv': " << std::endl;
        std::getline(std::cin, ticketDataFile);
        if(ticketDataFile.empty() || ticketDataFile.substr(ticketDataFile.size() - 4) != ".csv"){
          std::cout << "An invalid input was not provided" << std::endl;
        }
      }
      datasets[2] = ticketDataFile;
    }
    rw.saveData(datasets);   // Save the new or updated data of the user back to the csv file
    userLoggedIn = nullptr;
    userID.clear();
    password.clear();

    std::cout << "Logout successful\nReturning to main menu..." << std::endl;
    printMenu(); // Return to the main menu after logout
}
