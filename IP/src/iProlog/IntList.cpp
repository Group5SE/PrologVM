/*
==================================================================
Author: Karthik Venkataramana Pemmaraju.
Compilation: g++ IntList.cpp -c
Description: Implements data structure of sequence of ints.
Compiled and tested on 09/17/2017
==================================================================
*/

#include "IntList.h"
#include "IntStack.h"

namespace iProlog{
    IntList::IntList(int h): head(h){ // Our head is initialized to h.
        IntList::tail = NULL;
        IntList::empty = NULL;
    }

    IntList::IntList(int X, const IntList *Xs) : head (X), tail(Xs){
    }

    bool IntList::isempty(const IntList *Xs){ // C++ grammar defines static to be declared only once inside class.
        if(Xs == NULL)
            return true;
        else
            return false;
    }

    int IntList::getHead(const IntList *Xs){
        return Xs -> head;
    }

    IntList IntList::getTail(const IntList *Xs) {
        return *Xs ->tail;
    }

    IntList IntList::cons(const int X, const IntList *Xs) {
        IntList newIntList(X, Xs);  // creating a new IntList.
        return newIntList;
    }
    
    IntList* IntList::app(vector<int> xs, IntList *Ys) {
        IntList *Zs = Ys; 
        for (int i = xs.size() - 1; i >= 0; i--){
        IntList temp = cons(xs[i], Zs);
        Zs = &temp;
        }
        return Zs;
    }

    int IntList::len(IntList* Xs) {
        return toInts(Xs).size();
    }

    IntStack IntList::toInts(IntList* Xs){
        IntStack is;
        while (!IntList::isempty(Xs)) {
        is.push(IntList::getHead(Xs));
        IntList temp = getTail(Xs);
        Xs = &temp;
        }
        return is;
    }

    // string IntList::toString(){
    //   return IntList::toInts(this).toString();
    // }
    /*
    Driver functions to test IntList.h (09/18/2017)
    ***********************************************
    int main(int argc, char const *argv[]) {
        iProlog::IntList il(1);
        iProlog::IntList il1(2, &il);
        cout << iProlog::IntList::isempty(&il) << endl; // 0 if false
        cout << iProlog::IntList::getHead(&il1) << endl; // Head is 2
        iProlog::IntList il2 = iProlog::IntList::getTail(&il1);
        cout << iProlog::IntList::getHead(&il2) << endl; // Tail of il1 is il = 1
        iProlog::IntList il3 = iProlog::IntList::cons(4, &il2);
        cout << iProlog::IntList::getHead(&il3) << endl;
        std::vector<int> second (4); // creates a vector of 4 100's
        iProlog::IntList il4 = iProlog::IntList::app(second, NULL);
        iProlog::IntList il5 = iProlog::IntList::getTail(&il4);
        cout << iProlog::IntList::isempty(&il5);

    return 0;
    }
    */
}