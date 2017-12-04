/*
 * author: Keerthana Sadam ; Date: 11/13/2017
 * Included test cases which covers all functions
 * modified test cases using random generator on 11/29/2017 
 */
/**
Dynamic Stack for int data.
 */
package iPrologUpdate;
import java.util.Arrays;

class IntStack {

  private int stack[];

  private int top;

  static int SIZE = 16; // power of 2

  static int MINSIZE = 1 << 15; // power of 2

  IntStack() {
    this(SIZE);
  }

  IntStack(final int size) {
    stack = new int[size];
    clear();
  }

  final int getTop() {
    return top;
  }

  final int setTop(final int top) {
    return this.top = top;
  }

  final void clear() {
    //for (int i = 0; i <= top; i++)
    //stack[i] = 0;
    top = -1;
  }

  final boolean isEmpty() {
    return top < 0;
  }

  /**
   * Pushes an element - top is incremented first than the
   * element is assigned. This means top point to the last assigned
   * element - which can be returned with peek().
   */
  final void push(final int i) {
    // IO.dump("push:"+i);
    if (++top >= stack.length) {
      expand();
    }
    stack[top] = i;
  }

  final int pop() {
    final int r = stack[top--];
    shrink();
    return r;
  }

  final int get(final int i) {
    return stack[i];
  }

  final void set(final int i, final int val) {
    stack[i] = val;
  }

  final int size() {
    return top + 1;
  }

  /**
   * dynamic array operation: doubles when full
   */
  private final void expand() {
    final int l = stack.length;
    final int[] newstack = new int[l << 1];

    System.arraycopy(stack, 0, newstack, 0, l);
    stack = newstack;
  }

  /**
  * dynamic array operation: shrinks to 1/2 if more than than 3/4 empty
  */
  private final void shrink() {
    int l = stack.length;
    if (l <= MINSIZE || top << 2 >= l)
      return;
    l = 1 + (top << 1); // still means shrink to at 1/2 or less of the heap
    if (top < MINSIZE) {
      l = MINSIZE;
    }

    final int[] newstack = new int[l];
    System.arraycopy(stack, 0, newstack, 0, top + 1);
    stack = newstack;
  }

  int[] toArray() {
    final int[] array = new int[size()];
    if (size() > 0) {
      System.arraycopy(stack, 0, array, 0, size());
    }
    return array;
  }

  public final void reverse() {
    int l = size();
    int h = l >> 1;
    // Prolog.dump("l="+l);
    for (int i = 0; i < h; i++) {
      int temp = stack[i];
      stack[i] = stack[l - i - 1];
      stack[l - i - 1] = temp;
    }
  }

  @Override
  public String toString() {
    return Arrays.toString(toArray());
  }
  
public static void main(String args[]){
	  int n = 7777;
	  n = CustomGenerator.random(n);
	  IntStack stackValues = new IntStack(n);
	  System.out.println("Is stack Empty? "+stackValues.isEmpty());
	  n = CustomGenerator.random(n);
	  stackValues.push(n);
	  System.out.println("Value of 'Top' in stack is: "+stackValues.getTop());
	  n = CustomGenerator.random(n);
	  stackValues.push(n);
	  System.out.println("Set Top of stack: " + stackValues.setTop(2));
	  n = CustomGenerator.random(n);
	  stackValues.push(n);
	  System.out.println("Element that is popped out: "+ stackValues.pop());
	  System.out.println("Element at index 1 is: "+ stackValues.get(1));
	  n = CustomGenerator.random(n);
	  stackValues.set(2,n);
	  System.out.println("Element in the stack in Normal Order: "+ stackValues.toString());
	  stackValues.reverse();
	  System.out.println("Element in the stack in reverse Order: "+ stackValues.toString());
	  n = CustomGenerator.random(n);
	  stackValues.push(n);
	  n = CustomGenerator.random(n);
	  stackValues.push(n);
	  n = CustomGenerator.random(n);
	  stackValues.push(n);
	  System.out.println("Current stack elements after calling expand(): "+ stackValues.toString());
	  for(int i = 0; i < 4; i++){
		  stackValues.pop();
	  }
	  System.out.println("Current stack elements after calling shrink(): "+ stackValues.toString());
	  stackValues.clear();
	  System.out.println("Size of stack after clearing is: "+stackValues.size());
	  
	  
  }
  
  /*public static void main(String args[]){
	  
	  IntStack stackValues = new IntStack(5);
	  System.out.println("Is stack Empty? "+stackValues.isEmpty());
	  stackValues.push(10);
	  System.out.println("Value of 'Top' in stack is: "+stackValues.getTop());
	  stackValues.push(20);
	  System.out.println("Set Top of stack: " + stackValues.setTop(2));
	  stackValues.push(40);
	  System.out.println("Element that is popped out: "+ stackValues.pop());
	  System.out.println("Element at index 1 is: "+ stackValues.get(1));
	  stackValues.set(2,50);
	  System.out.println("Element in the stack in Normal Order: "+ stackValues.toString());
	  stackValues.reverse();
	  System.out.println("Element in the stack in reverse Order: "+ stackValues.toString());
	  stackValues.push(30);
	  stackValues.push(40);
	  stackValues.push(60);
	  System.out.println("Current stack elements after calling expand(): "+ stackValues.toString());
	  for(int i = 0; i < 4; i++){
		  stackValues.pop();
	  }
	  System.out.println("Current stack elements after calling shrink(): "+ stackValues.toString());
	  stackValues.clear();
	  System.out.println("Size of stack after clearing is: "+stackValues.size());
	  
	  
  }*/

/*Java Output with Random Input: 
		Is stack Empty? true
		Value of 'Top' in stack is: 0
		Set Top of stack: 2
		Element that is popped out: -737382
		Element at index 1 is: -796122
		Element in the stack in Normal Order: [232043, -796122, -690523]
		Element in the stack in reverse Order: [-690523, -796122, 232043]
		Current stack elements after calling expand(): [-690523, -796122, 232043, 32124, 412485, -661361]
		Current stack elements after calling shrink(): [-690523, -796122]
		Size of stack after clearing is: 0

 */

}
