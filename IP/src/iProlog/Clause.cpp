/*
==================================================================
Author: Karthik Venkataramana Pemmaraju
Description: Data structure implementation of a prolog Clause.
Compilation: g++ Clause.cpp -c
Compiled and tested on  09/17/2017
==================================================================
*/
#include "Clause.h"

namespace iProlog{

    // Parameterized constructor to instantiate const variables.
    Clause::Clause(int l, vector<int> h, int b, int n, vector<int> x)
        : len(l)
        , hgs(h)
        , base(b)
        , neck(n)
        , xs(x){ // Default constructor for const variables.
    }
}