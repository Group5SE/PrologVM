/*
==================================================================
Author: Karthik Venkataramana Pemmaraju,Charishma Damuluri
Description: Data structure representation of a prolog Clause.
Compilation: g++ Clause.h
Compiled and tested on  09/17/2017
==================================================================
*/

#ifndef CLAUSE
#define CLAUSE
#include <iostream>
#include <vector> 
namespace iProlog {
/*
    @type: class
    @desc: Provides a template for a prolog clause.
*/

  class Clause {
    public:
      const int len; // length of heap slice
      const std::vector<int> hgs; // head+goals pointing to cells in cs
      //neck-first after the end of head
      const int neck; 
      const int base;// heap where this starts 
      const std::vector<int> xs; // indexables in head
      Clause(int l, std::vector<int> h, int b, int n, std::vector<int> x); // Parameterized constructor.
      template<typename T>
      static void printVector(std::vector<T> x);
  };
}
#endif
