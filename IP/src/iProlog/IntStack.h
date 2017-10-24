/*
Author: Karthik Venkataramana Pemmaraju & Charishma Damuluri.
Compilation: g++ IntStack.h -c
Description: Stack implementation of ints.

Compiled and tested on 09/21/2017.
*/

#include <iostream>
#include <string.h>
#include <vector>

using namespace std;

namespace iProlog {
  class IntStack {
    private:
      vector <int> stack;
    	int top;
    	static const int SIZE = 16; // power of 2
    	static const int MINSIZE = 1 << 15; // power of 2

    public:
      IntStack(int size);
    	int getTop();
    	void setTop(const int top);
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
    	// TO - DO (Not sure if these are required in C++.)
    	string toString();
    	vector <int> toArray();
  };

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
  void IntStack::setTop(const int top) {
    this -> top = top;
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
    cout << " Here in expand ";
    vector < int > ::iterator it;
    const int l = stack.size();
    vector < int > newstack(l << 1);
    it = stack.begin();
    newstack.assign(it, (it + l)); // Copy l elements from stack to new stack System.arraycopy(stack, 0, newstack, 0, l);
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
      vector < int > newstack(l);
      it = stack.begin();
      newstack.assign(it, (it + top + 1)); // Copy (top + 1) elements from stack to new stack
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
} // name space close.

/*
Driver functions to test IntList.h (09/18/2017)
***********************************************
int main(){
	iProlog::IntStack is;
	is.setTop(40); // Calling setTop() function.
	cout << is.getTop() << endl ; // returns top of stack.
	cout << is.isEmpty() << endl; // 0 for false , 1 for true
	is.clear();
	cout << is.getTop() << endl; // returns top of stack which is -1.
	cout << "Pushing 1 \n";
	is.push(1);
	cout << "Popped up: " << is.pop() << endl ;
	cout << "Size of Stack is : " << is.size() << endl;
	cout << "Pushing 1 3 2 \n";
	is.push(1);
	is.push(3);
	is.push(2);
	cout << "Reversing: \n";
	is.reverse();
	cout << "Now element at top is: " << is.get(0);
	return 0;
}
*/
