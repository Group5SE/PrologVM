/*
Author: Karthik Venkataramana Pemmaraju.
Compilation: g++ Spine.h
Description: Represents the run time elements on heap.
Compiled and tested on 09/17/2017
*/

#include <iostream>
#include <vector>
#include "IntList.h" // We need IntList.h file.
using namespace std;


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
      private:
          const int hd; // head of the clause to which this corresponds
          const int base; // top of the heap when this was created
          const IntList *gs; // goals - with the top one ready to unfold
          const int ttop; // top of the trail when this was created
          int k;
          vector<int> xs; // index elements
          vector<int> cs; // array of  clauses known to be unifiable with top goal in gs
      public:
          Spine(int h, int t);
          Spine(vector<int> gs0,int b,IntList *g, int top, int ks, vector<int> c);
   };

   /**
    * creates a specialized spine returning an answer (with no goals left to solve)
    */

   Spine::Spine(int h, int t)
    : hd(h),
      ttop(t),
      base(0),
      k(-1){ // assigned constant values here.
        Spine::cs.clear(); // Make cs an empty array vector.
        Spine::gs = IntList::empty;
   }

   /**
    * creates a spine - as a snapshot of some runtime elements
    */
   Spine::Spine(vector<int> gs0,int b,IntList *g, int top, int ks, vector<int> c)
    : hd(gs0.at(0)),
      base(b),
      ttop(top){
        k = ks;
        IntList temp = IntList::getTail(IntList::app(gs0, g)); // prepends the goals of clause with head hs
        Spine::gs = &temp; // Since gs is of type pointer.
        cs = c;
    }
}
