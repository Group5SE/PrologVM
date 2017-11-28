/*
==================================================================
Author: Karthik Venkataramana Pemmaraju & Charishma Damuluri.
Compilation: g++ IntStack.cpp -std=c++11 -c
Description: Stack implementation of ints.
Compiled and tested on 09/21/2017.
==================================================================
*/

#include "IntStack.h"
#include <iostream>
#include <string.h>
#include <vector>
#include <iterator>
#include <sstream>

using namespace std;

namespace iProlog{
    
    IntStack::IntStack():IntStack(SIZE) {
    
    }
    /*
        @type: Constructor.
        @parameter: None (We declare it to be size(16))
        @desc: Creating a stack of size 16 elements initially.
    */
    IntStack::IntStack(int size = SIZE) { 
        this -> stack.resize(size);
        clear();
    }

    int IntStack::getTop() {
        return this -> top;
    }

    /*
        @type: function.
        @parameter: Top (integer)
        @desc: set the top of stack to arbitrary integer.
    */
    int IntStack::setTop(const int top) {
        return this -> top = top;
    }

    void IntStack::clear() {
        this -> top = -1;
    }

    bool IntStack::isEmpty() {
        return (this -> top < 0);
    }

    /**
    * Pushes an element - top is incremented first than the
    * element is assigned. This means top point to the last assigned
    * element - which can be returned with peek().
    */
    void IntStack::push(const int i) {
        // TO - DO
        if (++top >= stack.size()) { 
          expand();
        }
        stack[top] = i;
    }

    // Removes top element from stack.
    int IntStack::pop() { 
        const int r = stack[top--]; 
        shrink();
        return r;
    }

    /*
        @type: function.
        @parameter: Index i (integer)
        @desc: returns the value at index i in stack.
    */
    int IntStack::get(const int i) {
        return stack[i];
    }

    void IntStack::set(const int i, const int val) {
        stack[i] = val;
    }

    int IntStack::size() {
        return top + 1;
    }
    /*
    * dynamic array operation: doubles when full
    */
    void IntStack::expand() { 
        vector < int > ::iterator it;
        const int l = stack.size();
        vector < int > newstack(l << 1);
        it = stack.begin();
        newstack.assign(it, (it + l + 1)); // Copy l elements from stack to new stack System.arraycopy(stack, 0, newstack, 0, l);
        stack = newstack;
    }

    /**
    * dynamic array operation: shrinks to 1/2 if more than than 3/4 empty
    */
    void IntStack::shrink() {
        vector < int > ::iterator it;
        int l = stack.size();
        if ((l <= MINSIZE) || (top << 2 >= l))
            return;
        l = 1 + (top << 1); // still means shrink to at 1/2 or less of the heap
        if (top < MINSIZE) {
            l = MINSIZE;
        }
        cout << "*************" << l << endl;
        vector < int > newstack(l);
        it = stack.begin();
        newstack.assign(it, it + l); // Copy (top + 1) elements from stack to new stack
        stack = newstack;
        }
       
    /*
        @type: function.
        @parameter: None
        @desc: reverses the stack using a for- loop.
    */
    void IntStack::reverse() { // Code almost remains the same :)
        int l = size();
        int h = l >> 1;
        // Prolog.dump("l="+l);
        for (int i = 0; i < h; i++) {
        int temp = stack[i];
        stack[i] = stack[l - i - 1];
        stack[l - i - 1] = temp;
        }
    }

    vector<int> IntStack::toArray(){ 
        vector < int > ::iterator it; 
        it = stack.begin();
        vector<int> temp(it, it + size());
        return temp;
    }

    std::string IntStack::toString(){ 
        std::vector<int> vec = toArray();
        std::ostringstream oss; 
        if (!vec.empty()){ 
            std::copy(vec.begin(), vec.end()-1,
            std::ostream_iterator<int>(oss, ","));
            // Now add the last element with no delimiter
            oss << vec.back();
         }
        return oss.str();
    }
}
    /*
    Driver functions to test IntStack.cpp (09/18/2017)
    ***********************************************
    */
    // int main(){
    //     iProlog::IntStack* stackValues = new iProlog::IntStack(5);
    //     cout << "Is stack Empty? " << stackValues -> isEmpty() << endl;
    //     stackValues->push(10);
    //     cout << "Value of 'Top' in stack is: " << stackValues -> getTop() << endl;
    //     stackValues -> push(20);
    //     cout << "Set Top of stack: " << stackValues -> setTop(2) << endl;
    //     stackValues -> push(40);
    //     cout << "Element that is popped out: " << stackValues ->pop() << endl; 
    //     cout << "Element at index 1 is: " <<  stackValues ->get(1) << endl;
    //     stackValues -> set(2,50);
    //     cout << "Element in the stack in Normal Order: " <<  stackValues -> toString() << endl;
    //     stackValues -> reverse();
    //     cout << "Element in the stack in reverse Order: " <<  stackValues -> toString() << endl;
    //     stackValues -> push(30);
    //     stackValues -> push(40);
    //     stackValues -> push(60);
    //     cout << "Current stack elements after calling expand(): " <<  stackValues -> toString() << endl;
    //     for(int i = 0; i < 4; i++){
	// 	    stackValues -> pop();
    //     }    
    //     cout << "Current stack elements after calling shrink(): " <<  stackValues -> toString() << endl;
    //     stackValues -> clear();
    //     cout << "Size of stack after clearing is: " << stackValues -> size() << endl;
    //     return 0;
    // }
    
/*
    JAVA OUTPUT:
    E:\Software Engineering\Term Project Clone\IP\src\IProlog_Java>javac -d . IntStack.java

    E:\Software Engineering\Term Project Clone\IP\src\IProlog_Java>java iProlog/IntStack
    Is stack Empty? true
    Value of 'Top' in stack is: 0
    Set Top of stack: 2
    Element that is popped out: 40
    Element at index 1 is: 20
    Element in the stack in Normal Order: [10, 20, 50]
    Element in the stack in reverse Order: [50, 20, 10]
    Current stack elements after calling expand(): [50, 20, 10, 30, 40, 60]
    Current stack elements after calling shrink(): [50, 20]
    Size of stack after clearing is: 0

    C++ OUTPUT:
    E:\Software Engineering\Term Project Clone\IP\src\iProlog>g++ IntList.cpp Spine.cpp IntStack.cpp -std=c++11

    E:\Software Engineering\Term Project Clone\IP\src\iProlog>a.exe
    Is stack Empty? 1
    Value of 'Top' in stack is: 0
    Set Top of stack: 2
    Element that is popped out: 40
    Element at index 1 is: 20
    Element in the stack in Normal Order: 10,20,50
    Element in the stack in reverse Order: 50,20,10
    Current stack elements after calling expand(): 50,20,10,30,40,60
    Current stack elements after calling shrink(): 50,20
    Size of stack after clearing is: 0
*/