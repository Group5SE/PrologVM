
package iProlog;

import java.util.Arrays;

/**
 * representation of a clause
 */
class Clause {
  Clause(final int len, final int[] hgs, final int base, final int neck, final int[] xs) {
    this.hgs = hgs; // head+goals pointing to cells in cs
    this.base = base; // heap where this starts
    this.len = len; // length of heap slice
    this.neck = neck; // first after the end of the head
    this.xs = xs; // indexables in head
  }

  final int len;
  final int[] hgs;
  final int base;
  final int neck;
  final int[] xs;
  
  public static void main(String[] args) {
	
	  Clause c = new Clause(10, new int[]{11, 22, 33},0,3, new int[]{0,1,2});
	 System.out.println("length of heap slice: "+c.len);
	 System.out.println("head+goals pointing to cells in cs: "+Arrays.toString(c.hgs));
	 System.out.println("heap where this starts: "+ c.base);
	 System.out.println("first after the end of the head: "+c.neck);
	 System.out.println("indexables in head: "+Arrays.toString(c.xs));
	 //c.len = 15; //try to change the values of varaibles to check whethere final keyword is working or not
	 
}
  
  
}
