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
      int head;
      IntList* tail; // We need to use pointers because compiler doesn't size of IntList yet.
      IntList* empty = NULL;
    public:
      IntList(int h);
      IntList(int X,IntList *Xs);
      static bool isempty(IntList *Xs);
      static int getHead(IntList *Xs); // Changing name to gethead since head is already class variable.
      static IntList* getTail(IntList *Xs);
      static IntList* cons(int X, IntList *Xs);
      static IntList* app(std::vector<int> Xs,IntList *Ys);
      static IntStack* toInts(IntList* Xs);
      static int len(IntList *Xs);
      std::string toString();
      /*
        Rule of 3.
      */
      IntList& operator=(const IntList&);
      IntList(IntList &);
      ~IntList(); 
  };
}
#endif
