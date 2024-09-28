/*
Sort.hpp
authors: M00774667, M00916537, M00829986, M00843428, M00951627
created: 20/04/2024
updated: 21/04/2024
*/
#ifndef SORT_HPP
#define SORT_HPP

#include <vector>
#include <functional>
#include <iostream>

// templated class used for sorting vectors of a provided type
template<typename T>
class Sort{
  private:
    // quick sort is a divide and conquer algorithm
    // an element (the first) is selected from the vector and used as the pivot, the vector is then partitioned around the selected pivot
    // the pivot element is placed in its correct position in the vector and smaller elements are placed before it while larger elements are placed after it
    // continues until the start point is greater or equal to the end point, meaning each element has been placed in its correct location
    void quickSort(std::vector<T>& list, int start, int end, std::function<int(T)> func){
      if(start >= end){
        return;
      }
      int p = this->partition(list, start, end, func);
      this->quickSort(list, start, p - 1, func);
      this->quickSort(list, p + 1, end, func);
    }
    // core of the quick sort algorithm, in this implementation the pivot point is the first element in the vector
    int partition(std::vector<T>& list, int start, int end, std::function<int(T)> func){
      T pivot = list[start];
      int count = 0;
      for(int i = start + 1; i <= end; i ++){
        if(func(list[i]) <= func(pivot)){
          count++;
        }
      }
      int pivotIndex = start + count;
      std::swap(list[pivotIndex], list[start]);
      int i = start, j = end;
      while(i < pivotIndex && j > pivotIndex){
        while(func(list[i]) <= func(pivot)){
          i++;
        }
        while(func(list[j]) > func(pivot)){
          j--;
        }
        if(i < pivotIndex && j > pivotIndex){
          std::swap(list[i++], list[j++]);
        }
      }

      return pivotIndex;
    }
  public:
    Sort<T>(){};
    // sorts a provided list, using the provided lambda function as the way to retrieve whatever integer is to represent the items in the vector
    void sort(std::vector<T>& list, std::function<int(T)> func){
      this->quickSort(list, 0, list.size() - 1, func);
    }
};
#endif
