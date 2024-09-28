/*
Route.hpp
authors: M00774667, M00916537, M00829986, M00843428, M00951627
created: 01/03/2024
updated: 20/04/2024
*/
#ifndef ROUTE_HPP
#define ROUTE_HPP
#include <iostream>
#include <string>
#include <ctime>
#include <vector>
#include <iomanip>
#include "IDObject.hpp"

class Route : public IDObject{
    private:
    std::string direction, startPoint, endPoint;
    std::vector<std::string> routeStopsOrder, busesAssigned;
    double totalRouteDistance;
    int totalRouteTime;
    bool diversion;

    public:
      //Constructor for the route class with all the parameters
      Route(
        std::string routeId,
        std::string direction,
        std::string startPoint,
        std::string endPoint,
        std::vector<std::string> routeStopsOrder,
        double totalRouteDistance,
        int totalRouteTime,
        bool diversion,
        std::vector<std::string> busesAssigned
        );

      //Getter methods
      std::string getRouteId();
      std::string getDirection();
      std::string getStartingPoint();
      std::string getEndingPoint();
      std::vector<std::string> getRouteStopsOrder();
      double getTotalRouteDistance();
      int getTotalRouteTime();
      bool getDiversion();
      std::vector<std::string> getBusesAssigned();

      //Setter methods
      void setDirection(std::string);
      void setStartingPoint(std::string);
      void setEndingPoint(std::string);
};
#endif
