/*
==================================================================
Author: Karthik Venkataramana Pemmaraju.
Compilation: g++ Spine.cpp -c
Description: Implements the run time elements on heap.
Compiled and tested on 09/27/2017
==================================================================
*/ 

#include <vector>
#include "IntList.h" // We need IntList.h file. 
#include "Spine.h"
using namespace std;

namespace iProlog{
   /**
   * creates a specialized spine returning an answer (with no goals left to solve)
   */
   Spine::Spine(int h, int t)
    : hd(h),
      ttop(t),
      base(0),
      k(-1){ // assigned constant values here.
        Spine::cs.clear(); // Make cs an empty array std::vector.
        Spine::gs = gs -> empty;
   }

   /**
    * creates a spine - as a snapshot of some runtime elements
    */
   Spine::Spine(std::vector<int> gs0,int b,IntList *g, int top, int ks, std::vector<int> c)
    : hd(gs0.at(0)),
      base(b),
      ttop(top){
        k = ks;
        IntList temp = IntList::getTail(IntList::app(gs0, g)); // prepends the goals of clause with head hs
        Spine::gs = &temp; // Since gs is of type pointer.
        cs = c;
    }
}