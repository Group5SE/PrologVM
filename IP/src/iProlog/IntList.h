/*
==================================================================
Author: Karthik Venkataramana Pemmaraju.
Compilation: g++ IntList.h
Description: Represents a data structure of sequence of ints.
Compiled and tested on 09/17/2017
==================================================================
*/
#ifndef INTLIST
#define INTLIST 
#include <vector>

#include "IntStack.h" 

namespace iProlog{
  class IntList{
  public:
      const int head;
      const IntList *tail; // We need to use pointers because compiler doesn't size of IntList yet.
      const IntList *empty = NULL;
    public:
      IntList(int h);
      IntList(const int X, const IntList *Xs);
      static bool isempty(const IntList *Xs);
      static int getHead(const IntList *Xs); // Changing name to gethead since head is already class variable.
      static IntList getTail(const IntList *Xs);
      static IntList* cons(const int X, const IntList *Xs);
      static IntList* app(std::vector<int> Xs,IntList *Ys);
      static IntStack* toInts(IntList* Xs);
      static int len(IntList *Xs);
      std::string toString();
  };
}
#endif
