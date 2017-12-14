/*
==================================================================
Author: Karthik Venkataramana Pemmaraju.
Compilation: g++ Spine.h
Description: Represents the run time elements on heap.
Compiled and tested on 09/27/2017
==================================================================
*/ 

#ifndef SPINE
#define SPINE
 
#include <vector>
#include "IntList.h" // We need IntList.h file. 

/**
 * runtime representation of an immutable list of goals
 * together with top of heap and trail pointers
 * and current clause tried out by head goal
 * as well as registers associated to it
 *
 * note that parts of this immutable lists
 * are shared among alternative branches
 */

 namespace iProlog{

   class Spine{
      public:
          int hd; // head of the clause to which this corresponds
          int base; // top of the heap when this was created
          IntList *gs; // goals - with the top one ready to unfold
          int ttop; // top of the trail when this was created
          int k;
          std::vector<int> xs; // index elements
          std::vector<int> cs; // array of  clauses known to be unifiable with top goal in gs
      public:
          ~Spine();
          Spine(int h, int t);
          Spine(const Spine &);
          Spine(std::vector<int> gs0,int b,IntList *g, int top, int ks, std::vector<int> c);
          Spine& operator= (const Spine&);
          template<typename T>
          void printVector(std::vector<T> x);

   };
}
#endif