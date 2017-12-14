#ifndef OBSTACK
#define OBSTACK

#include <iostream>
#include <vector>
#include <cstdlib>
#include <string>
#include <stdexcept>
 
namespace iProlog{
      template <class T>
      class ObStack { 
            public: 
                  std::vector<T*> elems;    
            public: 
                  void push(T* const& elem);      // push functionality
                  T* pop();                // pop functionality 
                  T* top() const;             // return top element in the list(peek)
                  bool empty() const{        // return true if List is empty
                        return elems.empty(); 
                  } 
                  int obSize(); 
                  bool empty();
      }; 

}
#endif