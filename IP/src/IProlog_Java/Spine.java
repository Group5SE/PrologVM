/*
 * author: Keerthana Sadam ; Date: 11/17/2017
 * Included test cases which covers all functions
 *
 */
package iProlog;

import java.util.Arrays;

/**
 * runtime representation of an immutable list of goals
 * together with top of heap and trail pointers
 * and current clause tried out by head goal
 * as well as registers associated to it
 *
 * note that parts of this immutable lists
 * are shared among alternative branches
 */
class Spine {

  /**
   * creates a spine - as a snapshot of some runtime elements
   */
  Spine(final int[] gs0, final int base, final IntList gs, final int ttop, final int k, final int[] cs) {
    hd = gs0[0];
    this.base = base;
    this.gs = IntList.tail(IntList.app(gs0, gs)); // prepends the goals of clause with head hs
    this.ttop = ttop;
    this.k = k;
    this.cs = cs;
  }

  /**
   * creates a specialized spine returning an answer (with no goals left to solve)
   */
  Spine(final int hd, final int ttop) {
    this.hd = hd;
    base = 0;
    gs = IntList.empty;
    this.ttop = ttop;

    k = -1;
    cs = null;
  }

  final int hd; // head of the clause to which this corresponds
  final int base; // top of the heap when this was created

  final IntList gs; // goals - with the top one ready to unfold
  final int ttop; // top of the trail when this was created

  int k;

  int[] xs; // index elements
  int[] cs; // array of  clauses known to be unifiable with top goal in gs
  
  public static void main(String[] args) {
	  IntList il = null;
	  Spine s1 = new Spine(0, -1);
	  Spine s2 = new Spine(new int[]{11,22,33},-2,il,5,10, new int[]{0,1,2});
	  //System.out.println(s2.toString());
	  System.out.println("head: "+s1.hd);
	  System.out.println("base: "+s1.base);
	  System.out.println("Intlist: "+s2.gs);
	  System.out.println("ttop: "+s2.ttop);
	  System.out.println("s2 head : "+s2.hd);
	  System.out.println("s2 k: "+ s2.k);
	  System.out.println("s2.cs: "+ Arrays.toString(s2.cs));
	  
}

}
