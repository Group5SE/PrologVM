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
#include "random.cpp"
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
        if(Xs == NULL) return true; 
        return false;
    }

    int IntList::getHead( IntList *Xs){
        if(Xs != NULL)
        return Xs -> head;
        return 0;
    }

    IntList* IntList::getTail( IntList *Xs) {
        if(Xs == NULL)
        { 
            return NULL;
        }
        else if( Xs -> tail == NULL)
        { 
            return NULL;
        }   
        IntList* Ys = &(*Xs -> tail); 
        return Ys;
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
             if(getTail(Xs) == NULL) break; 
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
    //     int n = 23456, n1 , n2 , n3; 
    //     n = iProlog::random(n);
    //     iProlog::IntList* s = NULL;
    //     iProlog::IntList *headEle = new iProlog::IntList(n); 
    //     n = iProlog::random(n);
    //     iProlog::IntList *curList = new iProlog::IntList(n, headEle); 
    //     cout << "Element in list are: "<<  curList -> toString() << endl;
    //     cout << " IS EMPTY ? " << iProlog::IntList::isempty(s) << endl;
    //     cout << "Head Element in list: "<<  iProlog::IntList::getHead(curList) << endl;
    //     cout << "Tail Element in list: "<<  iProlog::IntList::getTail(headEle)<< endl;
    //     cout << "Length of list: "<<  iProlog::IntList::len(curList)<< endl;
    //     n = iProlog::random(n);
    //     cout << "New List after adding one element using cons(): " <<  iProlog::IntList::cons(n, curList) -> toString() << endl;
    //     n1 = iProlog::random(n);
    //     n2 = iProlog::random(n1);
    //     n3 = iProlog::random(n2);
    //     cout << "New List after adding array of elements: " << iProlog::IntList::app(vector<int> {n1 , n2, n3}, curList) -> toString() << "\n";
    //     delete s;
    //     delete headEle;
    //     return 0;
    // }
/*
    UNIT TESTING 
    JAVA OUTPUT:
    E:\Software Engineering\Term Project Clone\IP\src\IProlog_Java>javac -d . IntList.java

    E:\Software Engineering\Term Project Clone\IP\src\IProlog_Java>java iProlog/IntList
    Element in list are: [20, 10]
    Head Element in list: 20
    Tail Element in list: [10]
    Length of list: 2
    New List after adding one element using cons(): [30, 20, 10]
    New List after adding array of elements: [40, 50, 60, 20, 10]

    C++ OUTPUT:
    E:\Software Engineering\Term Project Clone\IP\src\iProlog>g++ IntList.cpp Spine.cpp IntStack.cpp -std=c++11

    E:\Software Engineering\Term Project Clone\IP\src\iProlog>a.exe
    Element in list are: 20,10
    Head Element in list: 20
    Tail Element in list: 10
    Length of list: 2
    New List after adding one element using cons(): 30,20,10
    New List after adding array of elements: 40,50,60,20,10
*/


/*
    RANDOM TESTING OUTPUT (11/29/2017):

    C++ OUTPUT:
    E:\Software Engineering\Term Project Clone\IP\src\iProlog>g++ IntList.cpp IntStack.cpp -std=c++11

    E:\Software Engineering\Term Project Clone\IP\src\iProlog>a.exe
    Element in list are: 466228,220028
    Head Element in list: 466228
    Tail Element in list: 220028
    Length of list: 2
    New List after adding one element using cons(): -669348,466228,220028
    New List after adding array of elements: 540024,-172465,-128109,466228,220028

*/
