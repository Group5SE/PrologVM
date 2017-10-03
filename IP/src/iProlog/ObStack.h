#include <iostream>
#include <vector>
#include <cstdlib>
#include <string>
#include <stdexcept>

using namespace std;
namespace iprolog{

template <class T>
class ObStack { 
   private: 
      vector<T> elems;    

   public: 
      void push(T const&);       // push functionality
      void pop();               // pop functionality 
      T top() const;            // return top element in the list(peek)
      
      bool empty() const {      // return true if List is empty
         return elems.empty(); 
      } 
}; 

template <class T>
void ObStack<T>::push (T const& elem) { 
  
   elems.push_back(elem);    
} 

template <class T>
void ObStack<T>::pop () { 
   if (elems.empty()) { 
      throw out_of_range("List is empty "); 
   }
   
   
   elems.pop_back();          // removing the last element
} 

template <class T>
T ObStack<T>::top () const { 
   if (elems.empty()) { 
      throw out_of_range("ObStack<>::top(): empty ObStack"); 
   }
   
   
   return elems.back();           // returns the last element 
} 
}