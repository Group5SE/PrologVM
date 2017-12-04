/*
==================================================================
Author: Karthik Venkataramana Pemmaraju & Charishma Damuluri.
Compilation: g++ IntStack.h -c
Description: Stack implementation of ints.
Compiled and tested on 09/21/2017.
==================================================================
*/
 
#ifndef INTSTACK
#define INTSTACK

#include <iostream>
#include <string.h>
#include <vector>
 

namespace iProlog {
  class IntStack {
    private:
      std::vector <int> stack;
    	int top;
    	static const int SIZE = 16; // power of 2
    	static const int MINSIZE = 1 << 15; // power of 2

		public:
			IntStack();
      IntStack(int size);
    	int getTop();
    	int setTop(const int top);
    	void clear();
    	bool isEmpty();
    	void push(const int i);
    	int pop();
    	int get(const int i);
    	void set(const int i, const int val);
    	int size();
    	void expand();
    	void shrink();
    	void reverse();
    	std::vector <int> toArray(); 
    	std::string toString();
  };

} // name space close.
#endif
