#include <iostream>
#include <vector>
#include <cstdlib>
#include <string>
#include <stdexcept>
#include "ObStack.h"
#include "random.cpp"
using namespace std;
namespace iProlog{

    template<class T>
    void ObStack<T>::push (T const& elem) { 
    // append copy of passed element 
    elems.push_back(elem);    
    } 

    template <class T>
    T ObStack<T>::pop () { 
        T obj = elems.back();
        if (elems.empty()) { 
            throw out_of_range("Stack<>::pop(): empty stack"); 
        }
        // remove last element 
        elems.pop_back();        
        return obj; 
    } 

    template <class T>
    T ObStack<T>::top () const { 
    if (elems.empty()) { 
        throw out_of_range("Stack<>::top(): empty stack"); 
    }
    
    // return copy of last element 
    return elems.back();      
    }
}

int main() { 
   try { 
      iProlog::ObStack<int> ob;    // stack of strings 
      int number= 23456;
      // manipulate string stack 
      cout << "The random numbers are:\n "; 
      for(int i = 0; i < 9; i++)
      {
          number = iProlog::random(number);
          cout << number << ",";
          ob.push(number);
      } 
      cout << "\nTop " << ob.top();
      ob.pop();
      cout << " \nTop After Pop " << ob.top();
   }catch (exception const& ex) { 
      cerr << "Exception: " << ex.what() <<endl; 
      return -1;
   } 
}

/*
    JAVA OUTPUT:
    E:\Software Engineering\Term Project Clone\IP\src\IProlog_Java>javac -d . ObStack.java

    E:\Software Engineering\Term Project Clone\IP\src\IProlog_Java>java iProlog/ObStack
    Top insert 4
    Top After Pop insert 3

    C++ OUTPUT:
    E:\Software Engineering\Term Project Clone\IP\src\iProlog>g++ ObStack.cpp -std=c++11

    E:\Software Engineering\Term Project Clone\IP\src\iProlog>a.exe
    Top insert 4
    Top After pop insert 3

*/

 /*
    Random Testing (11/29/2017):

    JAVA OUTPUT:
    E:\Software Engineering\Term Project Clone\IP\src\IProlog_Java>javac -d . ObStack.java

    E:\Software Engineering\Term Project Clone\IP\src\IProlog_Java>java iProlog/ObStack
    The random numbers are:
    220028,466228,-669348,540024,-172465,-128109,-306285,-270547,72343,
    Top 72343
    Top After Pop -270547
    C++ OUTPUT:
    E:\Software Engineering\Term Project Clone\IP\src\iProlog>g++ ObStack.cpp -std=c++11

    E:\Software Engineering\Term Project Clone\IP\src\iProlog>a.exe
    The random numbers are:
    220028,466228,-669348,540024,-172465,-128109,-306285,-270547,72343,
    Top 72343
    Top After Pop -270547
 */