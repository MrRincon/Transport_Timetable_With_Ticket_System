/*
IDObject.hpp
authors: M00774667, M00916537, M00829986, M00843428, M00951627
created: 20/04/2024
updated: 20/04/2024
*/
#ifndef ID_OBJECT_HPP
#define ID_OBJECT_HPP

#include <vector>
#include <sstream>
#include <string>
#include <stdexcept>

// class that the main ID based objects inherit form
class IDObject{
  protected:
    char idHeader;
    std::string id;
  public:
    IDObject();
    int getIdValue();
};

#endif
