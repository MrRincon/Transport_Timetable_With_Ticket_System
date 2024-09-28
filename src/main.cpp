/*
main.cpp
authors: M00774667, M00916537, M00829986, M00843428, M00951627
created: 01/03/2024
updated: 21/04/2024
*/
#include <iostream>
#include "./classes/Helper.hpp"
#include "./classes/ReadWrite.hpp"
#include "./classes/Menu.hpp"


int main(){
  ReadWrite &r = ReadWrite::instance();
  Menu menu;
  menu.initialDatasetMenu();
  menu.printMenu();
  return 0;
}
