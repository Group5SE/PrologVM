#include <iostream>
#include <vector>
#include <cstdlib>
#include <string>
#include <stdexcept>

using namespace std;
namespace iProlog{

    template <class T>
    class ObStack { 
        private: 
            vector<T> elems;    // elements 

        public: 
            void push(T const&);  // push element 
            void pop();               // pop element 
            T top() const;            // return top element 
            
            bool empty() const {      // return true if empty.
                return elems.empty(); 
            } 
    }; 

    template <class T>
    void ObStack<T>::push (T const& elem) { 
    // append copy of passed element 
    elems.push_back(elem);    
    } 

    template <class T>
    void ObStack<T>::pop () { 
    if (elems.empty()) { 
        throw out_of_range("Stack<>::pop(): empty stack"); 
    }
    
    // remove last element 
    elems.pop_back();         
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

// int main() { 
//    try { 
//       iProlog::ObStack<string> stringStack;    // stack of strings 
//       // manipulate string stack 
//       stringStack.push("insert 1"); 
// 	  stringStack.push("insert 2");
// 	  stringStack.push("insert 3");
// 	  stringStack.push("insert 4");
//       cout << "Top "<<stringStack.top() << std::endl; 
//       stringStack.pop(); 
//       cout <<"Top After pop "<< stringStack.top() << std::endl; 
//    }catch (exception const& ex) { 
//       cerr << "Exception: " << ex.what() <<endl; 
//       return -1;
//    } 
// }

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

 