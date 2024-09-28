/*
test.cpp
authors: M00774667, M00916537, M00829986, M00843428, M00951627
created: 19/03/2024
updated: 21/04/2024
*/
#define CATCH_CONFIG_MAIN
#include <iostream>
#include "./classes/Helper.hpp"
#include "./classes/ReadWrite.hpp"
#include "catch.hpp"

TEST_CASE("Construction of class objects", "[class construction]"){
  SECTION("constructing user class"){
    User u("Joe", "Schmoe", "123123", "jschmoe@gmail.com", "U10", 0);
    std::string fname, lname, pwd, email, userId;
    int userBalance;
    fname = u.getFname();
    lname = u.getLname();
    pwd = u.getPassword();
    email = u.getEmail();
    userId = u.getUserID();
    userBalance = u.getUserBalance();

    bool userCorrect;
    userCorrect = (fname == "Joe") && (lname == "Schmoe") && (pwd == "123123") && (email == "jschmoe@gmail.com") &&  (userId == "U10") && (userBalance == 0);
    REQUIRE(userCorrect);
  }
  SECTION("constructing bus class"){
    Bus b("B001", "John Arbuckle", "A", "R001", 50, false);
    std::string busId, name, currentStop, routeId;
    int capacity;
    bool delayed;
    busId = b.getBusID();
    name = b.getBusDriver();
    currentStop = b.getCurrentLocation();
    routeId = b.getRouteAssigned();
    capacity = b.getCapacity();
    delayed = b.getDelayedStatus();

    bool busCorrect;
    busCorrect = (busId == "B001") && (name == "John Arbuckle") && (currentStop == "A") && (routeId == "R001") && (capacity == 50) && (delayed == false);
    REQUIRE(busCorrect);
  }
  SECTION("constructing ticket class"){
    time_t cTime = 0;
    Ticket t("T001", "B001", "A", "B", "R001", cTime, false);
    std::string ticketId, busId, start, stop, routeId;
    time_t busTime;
    bool isValid;
    ticketId = t.getTicketID();
    busId = t.getBusAssignedTo();
    start = t.getStartLocation();
    stop = t.getEndLocation();
    routeId = t.getRouteReference();
    busTime = t.getBusTime();
    isValid = t.isTicketValid();

    bool ticketCorrect;
    ticketCorrect = (ticketId == "T001") && (busId == "B001") && (start == "A") && (stop == "B") && (routeId == "R001") && (cTime == busTime) && (isValid == false);
    REQUIRE(ticketCorrect);
  }
  SECTION("constructing stop class"){
    std::vector<std::string> routeAssigned;
    routeAssigned.push_back("R001");
    std::unordered_map<std::string, std::vector<std::string>> bussesAssigned;
    std::vector<std::string> times;
    times.push_back("10:00");
    bussesAssigned["B001"] = times;
    Stop s("A", "Alice Way", 10, 15, routeAssigned, bussesAssigned);

    std::string stopId, stopName;
    double x, y;
    std::vector<std::string> routes;
    std::unordered_map<std::string, std::vector<std::string>> busAndTime;
    stopId = s.getStopID();
    stopName = s.getStopName();
    x = s.getXLocation();
    y = s.getYLocation();
    routes = s.getRoutesAssigned();
    busAndTime = s.getBussesAssigned();

    bool stopCorrect;
    stopCorrect = (stopId == "A") && (stopName == "Alice Way") && (x == 10) && (y == 15) && (routes[0] == "R001") && (busAndTime["B001"][0] == "10:00");
    REQUIRE(stopCorrect);
  }
  SECTION("constructing route class"){
    std::vector<std::string> routeStops;
    routeStops.push_back("A");
    routeStops.push_back("B");
    std::vector<std::string> busAssigned;
    busAssigned.push_back("B001");
    Route r("R001", "NE", "A", "B", routeStops, 20, 2, false, busAssigned);

    std::string routeId, direction, start, end;
    std::vector<std::string> routeStopsOrder;
    double dist;
    int routeTime;
    bool diversion;
    std::vector<std::string> buses;
    routeId = r.getRouteId();
    direction = r.getDirection();
    start = r.getStartingPoint();
    end = r.getEndingPoint();
    routeStopsOrder = r.getRouteStopsOrder();
    dist = r.getTotalRouteDistance();
    routeTime = r.getTotalRouteTime();
    diversion = r.getDiversion();
    buses = r.getBusesAssigned();

    bool routeCorrect;
    routeCorrect = (routeId == "R001") && (direction == "NE") && (start == "A") && (end == "B") && (routeStopsOrder[0] == "A") && (routeStopsOrder[1] == "B") && (dist == 20) && (routeTime == 2) && (diversion == false) && (buses[0] == "B001");
    REQUIRE(routeCorrect);
  }
}

TEST_CASE("Loading data from datasets", "[loading from dataset]"){
  ReadWrite &rw = ReadWrite::instance();
  SECTION("successful loading of data"){
    // As long as the provided test datasets have not been removed or otherwise modified then the test should work
    bool success = rw.init("Test_Datasets/users.csv", "Test_Datasets/buses.csv", "Test_Datasets/tickets.csv", "Test_Datasets/stops.csv", "Test_Datasets/routes.csv");
    REQUIRE(success);
    rw.clearAllData();
  }
  SECTION("failed loading of data"){
    bool success = rw.init("", "", "", "", "");
    rw.clearAllData();
    // There are many conditions in which data will not be loaded correctly and as such trigger an error
    // Providing invalid filenames or providing incorrectly formatted filenames will both trigger an error response from the system and data will stop being loaded
    REQUIRE(success == false);
  }
}

// tests the process of creating and registering a new user onto the system
TEST_CASE("Registering a user", "[registering a new user]"){
  ReadWrite &rw = ReadWrite::instance();
  rw.init("Test_Datasets/users.csv", "Test_Datasets/buses.csv", "Test_Datasets/tickets.csv", "Test_Datasets/stops.csv", "Test_Datasets/routes.csv");
  User u("Joe", "Schmoe", "JHeartHeart1", "joeSchmoe@gmail.com", "U100",0);
  rw.addUser(u);
  rw.saveUsers("Test_Datasets/users.csv");
  rw.clearAllData();
  rw.init("Test_Datasets/users.csv", "Test_Datasets/buses.csv", "Test_Datasets/tickets.csv", "Test_Datasets/stops.csv", "Test_Datasets/routes.csv");
  std::vector<User> userList = rw.getUserList();
  User newU = userList[userList.size() - 1];
  REQUIRE(u.getUserID() == newU.getUserID());
  rw.clearAllData();
}

// tests theh process of logging into an existing user account
TEST_CASE("Logging into an existing user account", "[logging in]"){
  ReadWrite &rw = ReadWrite::instance();
  rw.init("Test_Datasets/users.csv", "Test_Datasets/buses.csv", "Test_Datasets/tickets.csv", "Test_Datasets/stops.csv", "Test_Datasets/routes.csv");
  std::string accountId, pwd;
  accountId = "U100";
  pwd = "JHeartHeart1";
  User* user = rw.getUser("U100");
  if(!user){
    REQUIRE(false);
  }else{
    REQUIRE(user->getPassword() == pwd);
  }
  rw.clearAllData();
}

TEST_CASE("Purchasing a ticket", "[purchasing ticket]"){
  ReadWrite &rw = ReadWrite::instance();
  rw.init("Test_Datasets/users.csv", "Test_Datasets/buses.csv", "Test_Datasets/tickets.csv", "Test_Datasets/stops.csv", "Test_Datasets/routes.csv");
  User* user = rw.getUser("U100");
  Ticket t("T100", "B1", "S1", "S10", "R1", std::time(0), false);
  user->addPurchasedTicket("T100");
  rw.addTicket(t);
  rw.saveUsers("Test_Datasets/users.csv");
  rw.saveTickets("Test_Datasets/tickets.csv");
  rw.clearAllData();
  rw.init("Test_Datasets/users.csv", "Test_Datasets/buses.csv", "Test_Datasets/tickets.csv", "Test_Datasets/stops.csv", "Test_Datasets/routes.csv");
  Ticket* tPtr = rw.getTicket("T100");
  if(!tPtr){
    REQUIRE(false);
  }else{
    REQUIRE(tPtr->getTicketID() == t.getTicketID());
  }
  rw.clearAllData();
}
