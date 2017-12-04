package iProlog;
import java.util.ArrayList;
class ObStack<T> extends ArrayList<T> {

  private static final long serialVersionUID = 1L;

  final T pop() {
    final int last = this.size() - 1;
    return this.remove(last);
  }

  final void push(final T O) {
    add(O);
  }

  final T peek() {
    return get(this.size() - 1);
  } 

 
	public static void main(String[] args) {  
      CustomGenerator cg = new CustomGenerator();
      ObStack<Integer> ob = new ObStack<Integer>();
      int number= 23456;
      System.out.print("The random numbers are:\n "); 
      for(int i = 0; i < 9; i++)
      {
          number = cg.random(number);
          System.out.print(number+",");
          ob.push(number);
      } 
      System.out.println("\nTop "+ob.peek());
      ob.pop();
      System.out.println(" \nTop After Pop "+ob.peek());
	}

}

