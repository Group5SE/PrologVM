/*
==================================================================
Author: Karthik Venkataramana Pemmaraju
Description: Data structure representation of a prolog Clause.
Compilation: g++ Clause.h
Compiled and tested on  09/17/2017
==================================================================
*/

#include <iostream>
#include <vector>
using namespace std;

namespace iProlog {
/*
    @type: class
    @desc: Provides a template for a prolog clause.
*/

  class Clause {
    private:
      const int len; // length of heap slice
      const vector<int> hgs; // head+goals pointing to cells in cs
      const int base; // heap where this starts
      const int neck; // first after the end of the head
      const vector<int> xs; // indexables in head
    public:
      Clause(int l, vector<int> h, int b, int n, vector<int> x); // Parameterized constructor.
  };

  // Parameterized constructor to instantiate const variables.
  Clause::Clause(int l, vector<int> h, int b, int n, vector<int> x)
    : len(l)
    , hgs(h)
    , base(b)
    , neck(n)
    , xs(x){ // Default constructor for const variables.
  }
}
