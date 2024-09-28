/*
IDObject.cpp
authors: M00774667, M00916537, M00829986, M00843428, M00951627
created: 20/04/2024
updated: 20/04/2024
*/
#include "IDObject.hpp"

IDObject::IDObject(){

}

// returns the numerical value associated with an id string
int IDObject::getIdValue(){
  std::stringstream ss(this->id);
  std::string temp;
  std::vector<std::string> strVec;
  while(getline(ss, temp, this->idHeader)){
    if(temp != ""){
      strVec.push_back(temp);
    }
  }

  int val = -1;
  try{
    return stoi(strVec[0]);
  }catch(std::invalid_argument){
    return val;
  }
  return val;
}
