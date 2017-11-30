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
      ObStack<String> ob=new ObStack<String>();
      ob.push("insert 1");
      ob.push("insert 2");
      ob.push("insert 3");
      ob.push("insert 4");
      System.out.println("Top "+ob.peek());
      ob.pop();
      System.out.println("Top After Pop "+ob.peek());
	}

}

