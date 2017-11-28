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
using namespace std;

namespace iProlog{
    IntList::IntList(int h){ // Our head is initialized to h.
        head = h;
        tail = NULL;
    }

    IntList::IntList(int X,  IntList *Xs) {
        head = X;
        tail = Xs;
    }

    bool IntList::isempty(IntList *Xs){ // C++ grammar defines static to be declared only once inside class. 
        return NULL == Xs -> tail;
    }

    int IntList::getHead( IntList *Xs){
        return Xs -> head;
    }

    IntList* IntList::getTail( IntList *Xs) {
        return &(*Xs ->tail);
    }

    IntList* IntList::cons( int X,  IntList *Xs) {
        return new IntList(X, Xs);  // creating a new IntList.
    }
    
    IntList* IntList::app(vector<int> xs, IntList *Ys) {
        IntList *Zs = Ys; 
        for (int i = xs.size() - 1; i >= 0; i--){
            Zs = cons(xs[i], Zs);
        }
        return Zs;
    }

    int IntList::len(IntList* Xs) {
        return toInts(Xs) -> size();
    }

    IntStack* IntList::toInts(IntList* Xs){
        IntStack* is = new IntStack();
        while (!isempty(Xs)) {
            is -> push(getHead(Xs));   
            Xs = getTail(Xs);  
            if(Xs -> tail == NULL)
                is -> push(getHead(Xs));
        }
        return is;
    }

    string IntList::toString(){
      return IntList::toInts(this) -> toString();
    }

    IntList::IntList(IntList &other){ // Copy constructor (deep copy)
        head = other.head;
        *tail = *(other.tail);
        *empty = *(other.empty); 
    }

    IntList& IntList::operator=(const IntList&other){
        if( this == &other) return *this;
        else{
            head = other.head;
            *tail = *(other.tail);
            *empty = *(other.empty); 
        }
    }

    IntList::~IntList(){
        delete tail;
        delete empty;
    }

 
 
}
    /*
    Driver functions to test IntList.h (09/18/2017)
    ***********************************************
    
    */
    // int main(int argc, char  *argv[]) {
     
    //   iProlog::IntList *headEle = new iProlog::IntList(10); 
	//   iProlog::IntList *curList = new iProlog::IntList(20, headEle); 
	//   cout << "Element in list are: "<<  curList -> toString() << endl;
	//   cout << "Head Element in list: "<<  iProlog::IntList::getHead(curList) << endl;
	//   cout << "Tail Element in list: "<<  iProlog::IntList::getTail(curList)->head << endl;
	//   cout << "Length of list: "<<  iProlog::IntList::len(curList)<< endl;
	//   cout << "New List after adding one element using cons(): " <<  iProlog::IntList::cons(30, curList) -> toString() << endl;;
    //   cout << "New List after adding array of elements: " << iProlog::IntList::app(vector<int> {40,50,60}, curList) -> toString();
    //   return 0;
    // }
