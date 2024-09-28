/*
Helper.hpp
authors: M00774667, M00916537, M00829986, M00843428, M00951627
created: 02/03/2024
updated: 21/04/2024
*/
#ifndef HELPER_HPP
#define HELPER_HPP
#include <unordered_map>
#include <vector>
#include <cctype>
#include <cstring>
#include <sstream>
#include <algorithm>
#include <iostream>
#include <iomanip>

// Header file with useful functions
// Author: Teon Morgan
int strToInt(std::string src);
bool intToBoolean(int src);
int strToBoolean(std::string src);
std::vector<std::string> splitString(char delimiter, std::string src);

inline int extractIdVal(std::string id, char header){
  return strToInt(splitString(header, id)[0]);
}

// checks if provided integer is a valid boolean integer
inline bool isBoolInt(int src){
  if(src == 1 || src == 0){
    return true;
  }else{
    return false;
  }
}

// converts a string to an integer, returns -1 if the provided string is not an integer
inline int strToInt(std::string src){
  try{
    return stoi(src);
  }catch(std::invalid_argument){
    return -1;
  }
}

// converts a string to a double, returns -1 if the provided string is not a double
inline double strToDouble(std::string src){
  try{
    return stod(src);
  }catch(std::invalid_argument){
    return -1;
  }
}

// converts a provided string into an integer representing a boolean value, returns -1 if string is not a valid boolean string
inline int strToBoolean(std::string src){
  if(src == "TRUE"){
    return 1;
  }else if(src == "FALSE"){
    return 0;
  }else{
    return -1;
  }
}

// converts an integer into a boolean
inline bool intToBoolean(int src){
  if(src == 1){
    return true;
  }else{
    return false;
  }
}

// splits a provided string using a delimiter and returns the result as a vector of strings
inline std::vector<std::string> splitString(char delimiter, std::string src){
  std::stringstream ss(src);
  std::string temp;
  std::vector<std::string> returnValue;
  while(getline(ss, temp, delimiter)){
    if(temp != ""){
      returnValue.push_back(temp);
    }
  }
  return returnValue;
}

// converts a correctly formatted string into a hashtable
inline std::unordered_map<std::string, std::vector<std::string>> stringToHashTable(char keyDelimiter, char delimiter, std::string src){
  std::unordered_map<std::string,  std::vector<std::string>> hashMap;
  std::vector<std::string> keysVal = splitString(delimiter, src);
  for(int i = 0; i < keysVal.size(); i++){
    std::vector<std::string> keyAndVal = splitString(keyDelimiter, keysVal[i]);
    if(keyAndVal.size() != 2){
      std::cout << "This is an incorrectly constructed hashtable string" << std::endl;
      return hashMap;
    }
    std::vector<std::string> values = splitString(';',keyAndVal[1]);
    hashMap[keyAndVal[0]] = values;
  }
  return hashMap;
}

// displays contents of a hashTable
template <typename T, typename Y> void displayHashTable(std::unordered_map<T, Y> hashTable){
  for(auto i : hashTable){
    std::cout << i.first << std::endl;
    for(auto j : i.second){
      std::cout << j << std::endl;
    }
  }
}

// extracts a time_t value from provided time string
inline time_t extractTime(std::string timeStr){
  struct tm tm = {0};
  std::istringstream ss(timeStr);
  ss >> std::get_time(&tm, "%m/%d/%Y:%H:%M:%S");
  if(ss.fail()){
    time_t time = -1;
    return time;
  }else{
    tm.tm_isdst = -1;
    time_t time = mktime(&tm);
    return time;
  }
}

// extracts the hours and minutes from a time string, converts into a time_t value and returns it
inline time_t extractHoursAndMins(std::string timeStr){
  std::vector<std::string> timeParts = splitString(':', timeStr);
  if(timeParts.size() != 2){
    return 0;
  }
  int hour = strToInt(timeParts[0]);
  int mins = strToInt(timeParts[1]);

  if(hour < 0 || hour > 23){
    return 0;
  }
  if(mins < 0 || mins > 59){
    return 0;
  }
  const int MIN_AS_SECOND = 60;
  const int HOUR_AS_SECOND = 60 * MIN_AS_SECOND;
  time_t hoursAndMins = (hour * HOUR_AS_SECOND) + (mins * MIN_AS_SECOND);
  return hoursAndMins;
}

inline bool isTime(std::string timeStr){
  std::vector<std::string> timeParts = splitString(':', timeStr);
  if(timeParts.size() != 2){
    return 0;
  }
  int hour = strToInt(timeParts[0]);
  int mins = strToInt(timeParts[1]);

  if(hour < 0 || hour > 23){
    return false;
  }
  if(mins < 0 || mins > 59){
    return false;
  }
  return true;
}

// checks whether a provided direction is valid
inline std::string parseDir(std::string direction){
  if(direction == "N"){
    return direction;
  }else if(direction == "S"){
    return direction;
  }else if(direction == "W"){
    return direction;
  }else if(direction == "E"){
    return direction;
  }else if(direction == "NW"){
    return direction;
  }else if(direction == "NE"){
    return direction;
  }else if(direction == "SW"){
    return direction;
  }else if(direction == "SE"){
    return direction;
  }else{
    return "A";
  }

}
#endif
