
package iProlog;
class IntList {

  private final int head;
  private final IntList tail;

  private IntList(final int head) {
    this.head = head;
    tail = null;
  }

  private IntList(final int X, final IntList Xs) {
    head = X;
    tail = Xs;
  }

  static final boolean isEmpty(final IntList Xs) {
    return null == Xs;
  }

  static final int head(final IntList Xs) {
    return Xs.head;
  }

  static final IntList empty = null;

  static final IntList tail(final IntList Xs) {
    return Xs.tail;
  }

  static final IntList cons(final int X, final IntList Xs) {
    return new IntList(X, Xs);
  }

  static final IntList app(final int[] xs, final IntList Ys) {
    IntList Zs = Ys;
    for (int i = xs.length - 1; i >= 0; i--) {
      Zs = cons(xs[i], Zs);
    }
    return Zs;
  }

  static final IntStack toInts(IntList Xs) {
    final IntStack is = new IntStack();
    while (!isEmpty(Xs)) {
      is.push(head(Xs));
      Xs = tail(Xs);
    }
    return is;
  }

  static final int len(final IntList Xs) {
    return toInts(Xs).size();
  }

  @Override
  public String toString() {
    return toInts(this).toString();
  }
  

  
  
 public static void main(String args[]){
	  SimpleRandom r = new SimpleRandom();
	  int n = 23456, n1,n2,n3; 
	  n = CustomGenerator.random(n);
	  IntList headEle = new IntList(n);
	  n = CustomGenerator.random(n);
	  IntList curList = new IntList(n, headEle);
	  System.out.println("Element in list are: "+ curList.toString());
	  System.out.println("Head Element in list: "+ IntList.head(curList));
	  System.out.println("Tail Element in list: "+ IntList.tail(curList));
	  System.out.println("Length of list: "+ IntList.len(curList));
	  n = CustomGenerator.random(n);
	  System.out.println("New List after adding one element using cons(): " + IntList.cons(n, curList));
	  n1 = CustomGenerator.random(n);
	  n2 = CustomGenerator.random(n1);
	  n3 = CustomGenerator.random(n2);
	  System.out.println("New List after adding array of elements: "+ IntList.app(new int[]{n1,n2,n3}, curList));

 
}
 //Test cases with static input
 
/* public static void main(String args[]){
	
		  IntList headEle = new IntList(10);
		  IntList curList = new IntList(20, headEle);
		  System.out.println("Element in list are: "+ curList.toString());
		  System.out.println("Head Element in list: "+ IntList.head(curList));
		  System.out.println("Tail Element in list: "+ IntList.tail(curList));
		  System.out.println("Length of list: "+ IntList.len(curList));
		  System.out.println("New List after adding one element using cons(): " + IntList.cons(30, curList));
		  System.out.println("New List after adding array of elements: "+ IntList.app(new int[]{40,50,60}, curList));

	 
 }*/
 
 /*	Java output with random input:
 		Element in list are: [466228, 220028]
		 Head Element in list: 466228
		 Tail Element in list: [220028]
		 Length of list: 2
		 New List after adding one element using cons(): [-669348, 466228, 220028]
		 New List after adding array of elements: [540024, -172465, -128109, 466228, 220028]

 */
}
