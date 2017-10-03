/*
Author: Karthik Venkataramana Pemmaraju.
Compilation: g++ IntList.h
Description: Represents a data structure of sequence of ints.
Compiled and tested on 09/17/2017
*/


#include <iostream>
#include <vector>
using namespace std;


namespace iProlog{

  class IntList{
  public:
      const int head;
      const IntList *tail; // We need to use pointers because compiler doesn't size of IntList yet.
      static const IntList *empty;
    public:
      IntList(int h);
      IntList(const int X, const IntList *Xs);
      static bool isempty(const IntList *Xs);
      static int getHead(const IntList *Xs); // Changing name to gethead since head is already class variable.
      static IntList getTail(const IntList *Xs);
      static IntList cons(const int X, const IntList *Xs);
      static IntList* app(vector<int> Xs,IntList *Ys);
      // To - DO
      // static IntStack toInts(IntList Xs);
      // static int len(IntList *EXs);
      // public String toString();
  };

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

  // To - DO ( Up for Review).
  IntList* IntList::app(vector<int> xs, IntList *Ys) {
      IntList *Zs = Ys;
      for (vector<int>::reverse_iterator i = xs.rbegin(); i != xs.rend(); ++i ) { // Starts from the end and returns to the first.
        IntList temp = cons(*i , Zs);
        Zs = &temp;
      }
      return Zs;
  }

  // static int IntList::len(const IntList Xs) {
  //   return 1;
  // //  return toInts(Xs).size();
  // }

}

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
    std::vector<int> second (4,100); // creates a vector of 4 100's
    iProlog::IntList il4 = iProlog::IntList::app(second, NULL);
    iProlog::IntList il5 = iProlog::IntList::getTail(&il4);
    cout << iProlog::IntList::isempty(&il5);

  return 0;
}
*/