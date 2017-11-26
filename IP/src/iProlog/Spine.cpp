/*
==================================================================
Author: Karthik Venkataramana Pemmaraju.
Compilation: g++ Spine.cpp -c
Testing: g++ Spine.cpp IntList.cpp IntStack.cpp -std=c++11
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
        cout << "Inside constructor GS: " <<  gs -> getHead(gs) << endl;
        cs = c;
    }
}
  int main(){
    iProlog::IntList *il = NULL;
	  iProlog::Spine *s1 = new iProlog::Spine(0, -1);
	  iProlog::Spine *s2 = new iProlog::Spine(vector<int> {11,22,33},-2,il,5,10, vector <int>{0,1,2});
	  //cout <<s2.toString());
    cout << "head: " << s1 ->hd << endl;
	  cout << "base: " << s1 -> base << endl;
	  cout <<"Outside constructor Intlist (GS): " << (s2 -> gs) -> getHead(s2 -> gs)<< endl;
	  cout <<"ttop: " << s2 -> ttop << endl;
	  cout <<"s2 head : " << s2 -> hd<< endl;  
	  cout <<"s2 k: "<< s2 ->k << endl;
	//  cout <<"s2.cs: "+ Arrays.toString(s2.cs));
  }
/*
  JAVA OUTPUT:
  head: 0
  base: 0
  Intlist: [22, 33]
  ttop: 5
  s2 head : 11
  s2 k: 10
  s2.cs: [0, 1, 2]

  OUR OUTPUT:
  head: 0
  base: 0
  Outside constructor Intlist (GS): 0 (WHAT ?)
  ttop: 5
  s2 head : 11
  s2 k: 10
*/