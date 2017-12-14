/*
==============================================================================================
Author: Karthik Venkataramana Pemmaraju.
Compilation:g++ Engine.cpp IntStack.cpp IntList.cpp IMap.cpp IntMap.cpp ObStack.cpp Spine.cpp Clause.cpp -std=c++11 -c
Written on 11/25/2017
===============================================================================================
*/

#include "IntStack.h"
#include "ObStack.h"
#include "IntMap.h"
#include "IMap.h"
#include "Spine.h"
#include "Clause.h"
#include "IntList.h"
#include "Engine.h"
#include "Toks.h" 
#include <string> 
#include <map> 
#include <iterator>
#include <vector>
#include <stdexcept> 
#include <stdlib.h>     /* realloc, free, exit, NULL */

using namespace std;
using namespace boost;
namespace iProlog{

	int Engine::tag(const int t, const int w){
		return -((w << 3) + t);
	}
 
	// removes tag after flipping sign
	int Engine::detag(const int w){
		return -w >> 3;
	}

	//extracts the tag of a cell 
	int Engine::tagOf(int const w){
		return -w & 7;
	}

	int Engine::addSym(std::string sym){
		std::map<std::string, int>::iterator itr;
		itr = syms.find(sym);
		int i = 0;
		if(itr == syms.end()){
			i = syms.size();
			syms.insert({sym, i});
			slist.push_back(sym); 
		}
		else
		{
			i = itr -> second;
		}
		return i;
	}
	
	/**
	 * returns the symbol associated to an integer index
	 * in the symbol table
	*/
	std::string Engine::getSym(const int w){
		if (w < 0 || w >= slist.size())
			return "BAD SYM REF=" + std::to_string(w);
		return slist[w];
	}
	
	void Engine::makeHeap(){
		makeHeap(MINSIZE);
  	}
  
	void Engine::makeHeap(const int size){
		heap = (int*) malloc(size * sizeof(int));
		heapSize = size;
		clear();
  	}

	int Engine::getTop(){
		return this -> top;
	}

	int Engine::setTop(const int top){
		return this -> top = top;
	}

	void Engine::clear(){ 
		this -> top = -1;
	}
 
	void Engine::push(const int i){
		heap[++top] = i;
	} 

	int Engine::size(){
		return top + 1;
	}
		  
	/**
	 * dynamic array operation: doubles when full
	*/
	void Engine::expand(){
		heap = (int *)realloc(heap, heapSize << 1);
		heapSize = heapSize << 1; 
	}

	void Engine::ensureSize(const int more){  
		if (1 + top + more >= heapSize)
			expand();
	}

	std::vector<std::vector<std::string>> Engine::maybeExpand(std::vector<std::string> &Ws){
		const int l = Ws.size();
		std::vector<std::vector<std::string>> Rss; // ArrayList<String[]>
		const std::string W = Ws[0];
		if (W.length() < 2 || "l:" != W.substr(0, 2))
	 	 	return Rss;
		std::string V = W.substr(2);
		for (int i = 1; i < l; i++){
			std::vector<std::string> Rs(4);
			std::string Vi = 1 == i ? V : V + "__" + std::to_string(i - 1);
			std::string Vii = V + "__" + std::to_string(i);
			Rs[0] = "h:" + Vi;
			Rs[1] = "c:list";
			Rs[2] = Ws[i];
			Rs[3] = i == l - 1 ? "c:nil" : "v:" + Vii;
			Rss.push_back(Rs);
		}
		return Rss;
	}
		
	/**
	 * expands, if needed, "lists" statements in sequence of statements
	*/
	std::vector<std::vector<std::string>> Engine::mapExpand(std::vector<std::vector<std::string>> &Wss){
		std::vector<std::vector<std::string>> Rss;
		std::vector<std::vector<std::string>>::iterator Ws;
		for (Ws= Wss.begin(); Ws != Wss.end(); Ws++){ 
			std::vector<std::vector<std::string>> Hss = maybeExpand(*Ws);
			std::vector<std::string> ws;
			if (Hss.size() == 0){ 
				for (int i =0; i < Ws->size(); i++){
						 ws.push_back((*Ws)[i]);
				} 
				Rss.push_back(ws); 
			}
			else{
				for (std::vector<std::vector<std::string>>::const_iterator X = Hss.begin(); X < Hss.end(); X++){
					Rss.push_back(*X);
				}
			}
		}
		return Rss;
	}
		  
	/**
   	* loads a program from a .nl file of
   	* "natural language" equivalents of Prolog/HiLog statements
   	*/
	std::vector<Clause*> Engine::dload(std::string s){
		const bool fromFile = true; 
		Toks t;
		std::vector<std::vector<std::vector<std::string>>> Wsss = t.toSentences(s, fromFile); // (TO - DO on linux).
		std::vector<Clause*> Cs;
		for (auto Wss = Wsss.begin(); Wss != Wsss.end(); ++Wss){
			// clause starts here
			std::map<std::string, IntStack*> refs; 
			IntStack *cs = new IntStack();
			IntStack *gs = new IntStack(); 
			std::vector<std::vector<std::string>> Rss = mapExpand(*Wss);
			int k = 0;
		 	for(std::vector<std::vector<std::string>>::iterator ws= Rss.begin(); ws != Rss.end(); ++ws){
				// head or body element starts here
				const int lm = ws-> size();
				gs->push(tag(R, k++));
				cs->push(tag(A, lm));
				for (std::vector<std::string>::iterator w = ws -> begin(); w != ws -> end(); ++w){
					
					// head or body subterm starts here
					if (1 == w ->size()){ 
						*w = "c:" + *w;
					}
					std::string L = w ->substr(2);
					std::map<std::string, IntStack*>::iterator itr1 = refs.find(L);
					std::map<std::string, IntStack*>::iterator itr = refs.find(L);
					IntStack* Is;  
					char c = w -> at(0);  
					switch (c){
						case 'c':
							cs -> push(encode(C, L));  
							k++;
							break;
						case 'n':
							cs -> push(encode(N, L));
							k++;
							break;
						case 'v': 
								// printUnorderedMap(refs);
								// KEY EXISTS;  
									if( itr == refs.end())
									{
											Is = new IntStack(); // NECESSARY?
											refs.insert({L, Is}); // puts into hash map.
									}
									else{
										 	Is = itr -> second; 
									}
											Is->push(k); 
											cs->push(tag(BAD, k)); // just in case we miss this
											k++;	
								
						 	 break;
						case 'h': 
								//	IntStack *Is; 
								if(itr1 == refs.end())
								{ 
										Is = new IntStack(); // NECESSARY?
										refs.insert({L, Is}); // puts into hash map.
								}
								else{
										 	Is = itr1 -> second;
										// cout << " IS ) VALUES " << Is -> getTop() << " K " << k << endl;
								} 
									Is->push(k - 1); 
									cs->set((k - 1), tag(A, (lm - 1)));
									gs->pop(); 

							break;
						default:
							std::cout << " FORGOTTEN= " <<  *w ;
						 } // end subterm 
		 			} // end element
		   	} // end clause	
		// // linker 

		for(auto &itr: refs){
			IntStack* Is = itr.second; 
			int leader = -1;
			for (auto &j: Is -> toArray()){ 
				if (A == tagOf(cs->get(j))){
					leader = j;
					break;
				}
					  
			}
			if (leader == -1){
				// for vars, first V others U
				leader = Is -> get(0);
			  	for (auto &&i: Is -> toArray()){  
					if (i == leader)
						{
							cs->set(i, tag(V, i)); 
						}
					else{ 
						cs->set(i, tag(U, leader)); 
					}
				 }
			}
			else{
				for (auto &&i : Is -> toArray()){ 
					if (i == leader)
						continue;	
					cs->set(i, tag(R, leader)); 
				}
			} 
		}

		const int neck = 1 == gs->size() ? cs->size() : detag(gs->get(1)); 
		std::vector<int> tgs = gs->toArray();
		Clause* C = putClause(cs->toArray(), tgs, neck); 
		Cs.push_back(C);
		} // end clause set
		const int ccount = Cs.size(); 
		std::vector<Clause*> cls(ccount);
		for (int i = 0; i < ccount; i++){
			cls[i] = Cs[i];
		} 
		return cls; 
	}
 
	void Engine::printMap(std::map<std::string, int>  map){  
		cout << "{";
		for(auto t =  map.begin(); t != map.end(); ++t){  
				cout << "[" << t -> first << ", " << t -> second<< "], ";
			}
		cout << "}";
	}
	


	/*
	 * encodes string constants into symbols while leaving
	 * other data types untouched
	*/
	int Engine::encode(const int t,std::string s){
		int w;
		try{
		  w = std::stoi(s); 
		}
		catch (const std::exception &e)
		{ 
		  if (C == t){
			w = addSym(s);  
			}
		  else{
			return tag(BAD, 666);
			}
			//pp("bad in encode=" + t + ":" + s);
		} 
		return tag(t, w);
	}
 
	// places a clause built by the Toks reader on the heap 
	Clause* Engine::putClause(std::vector<int> cs, std::vector<int> gs, int const neck){
		const int base = size();
		const int b = tag(V, base);
		const int len = cs.size();
		pushCells(b, 0, len, cs);
		for (int i = 0; i < gs.size(); i++){
		  gs[i] = relocate(b, gs[i]);
		}
		std::vector<int> xs = getIndexables(gs[0]);
		return new Clause(len, gs, base, neck, xs);
	}

	int Engine::relocate(int const b, int const cell){
 		return (tagOf(cell) < 3) ? (cell + b) : cell;
	}
	
	std::vector<int> Engine::toNums(std::vector<Clause*> clauses){
		const int l = clauses.size();
		std::vector<int> cls(l);
		for (int i = 0; i < l; i++)
		{
		  cls[i] = i;
		}
		return cls;
	}
	
	/**
   	  * true if cell x is a variable
   	  * assumes that variables are tagged with 0 or 1
   	*/
	bool Engine::isVAR(int  x){
		//final int t = tagOf(x);
		//return V == t || U == t;
		return tagOf(x) < 2;
	}
  
	int Engine::getRef(int x){
		return heap[detag(x)];
	}

	/*
	 * sets a heap cell to point to another one
	*/ 
	void Engine::setRef(int w, int r){
		heap[detag(w)] = r;
	}
 
  	/**
   	  * removes binding for variable cells
   	  * above savedTop
   	*/
	void Engine::unwindTrail(int savedTop){
		while (savedTop < trail->getTop()){
		 	int href = trail->pop();
		 	// assert href is var
		  	setRef(href, href);
		}
	}
	  
	/**
   	* scans reference chains starting from a variable
   	* until it points to an unbound root variable or some
   	* non-variable cell
   	*/
	int Engine::deref(int x){
		while(isVAR(x)){
		  const int r = getRef(x);
		  if (r == x){
			break;
		  }
		  x = r;
		}
		return x;
	} 
	
	/**
   	  * builds an array of embedded arrays from a heap cell
   	  * representing a term for interaction with an external function
   	  * including a displayer
   	*/
	/**
   	  * builds an array of embedded arrays from a heap cell
   	  * representing a term for interaction with an external function
   	  * including a displayer
   	*/
	vector<string> Engine::exportTerm(int x){
		x = deref(x);
		const int t = tagOf(x);
		const int w = detag(x);
		string res; 
		if(t == Engine::C){
				res = "" + getSym(w);
		}
		else if(t == Engine::N)
				res = "" + std::to_string(w) ; // res = new Integer(w) ( Thought this is the way of doing this.)
		else if(t == Engine::V) 
				res = "V" + std::to_string(w) ; 
		else if(t == Engine::R){
				int a = heap[w];
				if (A != tagOf(a)){
					return {"*** should be A, found=" + showCell(a)};
				}
				int n = detag(a);
				std::vector<string> arr(n);
				int k = w + 1;
				for (int i = 0; i < n; i++){
						const int j = k + i; 
						if(i  < n - 1)
							arr[i] =  convertToString(exportTerm(heap[j]));
						else
							arr[i] = "("+ convertToString(exportTerm(heap[j])) +  ")" ;
					}
				return arr;
		}
		else  
				res = "*BAD TERM*" + showCell(x);
		return {res};
	}
	
	string Engine::convertToString(std::vector<string> x){
		string res; 
		for(auto &i: x)
		{
			res += i ;
		}   
		return res;
	}

	std::string Engine::showCell(int w){
		const int t = tagOf(w);
		int val = detag(w);
		std::string s = "";
		if(t == V)
				s = "v:" + std::to_string(val);
		else if(t == U)
				s = "u:" + std::to_string(val);
		else if(t == N)
				s = "n:" + std::to_string(val);
		else if(t == C)
				s = "c:" + std::to_string(val);
		else if(t == R)
				s = "r:" + std::to_string(val);
		else if(t == A)
				s = "a:" + std::to_string(val);
		else{
			s = "*BAD*=" + std::to_string(w);
		} 
		return s;
	}
  
	// Not Sure if this is correct, peer review required! (ATTENTION!!!!!!!)
	/**
   	* raw display of a term - to be overridden
   	*/ 
	void Engine::showTerm(int x){
		showTerm(exportTerm(x));
	}
  
	/**
   	* raw display of a externalized term
   	*/ 
	void Engine::showTerm(vector<string> O){ 
		 printVector(O, false);
		// cout << O -> toString(); // Print the object value here itself.
	}
 
	void Engine::ppTrail(){
		for (int i = 0; i <= trail -> getTop(); i++){
		  const int t = trail -> get(i);
			cout << "trail[" << std::to_string(i) << "]=" << showCell(t) << ":";
			// showTerm(t);
		}
	}

 
  	/**
  	 * extracts an integer array pointing to
   	 * the skeleton of a clause: a cell
   	 * pointing to its head followed by cells pointing to its body's
   	 * goals
   	*/
	std::vector<int> Engine::getSpine(std::vector<int> cs){
		const int a = cs[1];
		const int w = detag(a);
		std::vector<int> rs(w - 1);
		for (int i = 0; i < w - 1; i++){
			const int x = cs[3 + i];
			const int t = tagOf(x);
			if (R != t){
				cout << "*** getSpine: unexpected tag="  << std::to_string(t);
				rs.erase(rs.begin(),rs.end()); // IMPORTANT - Cannot return null as in java, so sending an empty vector.
				return rs;
			}
			rs[i] = detag(x);
		} 
		return rs;
	} 


	/**
   	* raw display of a cell as tag : value
   	*/
   	std::string Engine::showCells(int const base, int const len){
		std::string buf;
		for (int k = 0; k < len; k++){
		  int instr = heap[base + k];
		  buf += "[" + std::to_string(base + k) + "]";
		  buf += showCell(instr);
		  buf += " ";
		}
		return buf;
	}

	std::string Engine::showCells(std::vector<int> cs){
		std::string buf;
		for (int k = 0; k < cs.size(); k++)
		{
		  buf += "[" + std::to_string(k) + "]";
		  buf += showCell(cs[k]);
		  buf += " ";
		}
		return buf;
	}
	
  	/**
   	 * unification algorithm for cells X1 and X2 on ustack that also takes care
   	 * to trail bindigs below a given heap address "base"
	*/
	
	bool Engine::unify(int const base){  
		while (!ustack -> isEmpty()){
 
		  const int x1 = deref(ustack -> pop());
		  const int x2 = deref(ustack -> pop());
		  if (x1 != x2){
			const int t1 = tagOf(x1);
			const int t2 = tagOf(x2);
			const int w1 = detag(x1);
			const int w2 = detag(x2);
			if (isVAR(x1)){ // unb. var. v1
				if (isVAR(x2) && w2 > w1){ // unb. var. v2
					heap[w2] = x1;
					if (w2 <= base)
					trail->push(x2); 
				}
				else{ // x2 nonvar or older
					heap[w1] = x2;
					if (w1 <= base)
					trail->push(x1); 
				}
			}
			else if (isVAR(x2)){ // x1 is NONVAR
				heap[w2] = x1;
			 	if (w2 <= base)
				trail->push(x2); 
			}
			else if (R == t1 && R == t2){ // both should be R
			  	if (!unify_args(w1, w2))
					return false;
			}
			else{
			  	return false;
			}
		  }
		}
		return true;
	}

	bool Engine::unify_args(int const w1, int const w2){
		const int v1 = heap[w1];
		const int v2 = heap[w2];
		// both should be A
		const int n1 = detag(v1);
		const int n2 = detag(v2);
		if (n1 != n2){
		  return false;
		}
		const int b1 = 1 + w1;
		const int b2 = 1 + w2;
		for (int i = n1 - 1; i >= 0; i--){
		  const int i1 = b1 + i;
		  const int i2 = b2 + i;
		  const int u1 = heap[i1];
		  const int u2 = heap[i2];
		  if (u1 == u2)
			continue;
		  ustack->push(u2);
		  ustack->push(u1);
		}
		return true;
	}
	 
	/* 
	 * pushes slice[from,to] of array cs of cells to heap
	*/
	void Engine::pushCells(int const b, int const from, int const to, int const base){
		ensureSize(to - from);
		for (int i = from; i < to; i++){
		
		  push(relocate(b, heap[base + i]));
		}
	}

	/*  
	 * pushes slice[from,to] of array cs of cells to heap
	*/  
	void Engine::pushCells(int const b, int const from, int const to, vector<int> cs){
		ensureSize(to - from);
		for (int i = from; i < to; i++){ 
		  push(relocate(b, cs[i]));
		}
	}

	/* 
	 * copies and relocates head of clause at offset from heap to heap
	*/   
	int Engine::pushHead(int const b, Clause * C){
		pushCells(b, 0, C->neck, C->base);
		const int head = C->hgs[0];
		return relocate(b, head);
	}

	/* 	 

	 * copies and relocates body of clause at offset from heap to heap
 	 * while also placing head as the first element of array gs that
	 * when returned contains references to the toplevel spine of the clause
	*/
	vector<int> Engine::pushBody(int const b, int const head, Clause* C){
		pushCells(b, C->neck, C->len, C->base);
		const int l = C->hgs.size();
		vector<int> gs(l);
		gs[0] = head;
		for (int k = 1; k < l; k++){
		  const int cell = C->hgs[k];
		  gs[k] = relocate(b, cell);
		}
		return gs;
	}

	/*
	 * makes, if needed, registers associated to top goal of a Spine
	 * these registers will be reused when matching with candidate clauses
	 * note that xs contains dereferenced cells - this is done once for
	 * each goal's toplevel subterms
	*/
	void Engine::makeIndexArgs(Spine* G, int const goal){
		if (0 !=G -> xs.size()){
		  return;
		}
		const int p = 1 + detag(goal);
		const int n = std::min(MAXIND, detag(getRef(goal))); 
		G -> xs.resize(MAXIND);
		for (int i = 0; i < n; i++)
		{
		  const int cell = deref(heap[p + i]);
		  G -> xs[i] = cell2index(cell);
		} 
		if (imaps.size() == 0)
		  return;
		IMap<int> iM;
		G -> cs  = iM.get(imaps, vmaps, G -> xs);  
	}
	
	int Engine::cell2index(int const cell){
		int x = 0;
		const int t = tagOf(cell);
		if(t == R)
			x = getRef(cell);
		else if(t == N) 
			x = cell; 
		  // 0 otherwise - assert: tagging with R,C,N <>0
		return x;
	}
	
	std::vector<int> Engine::getIndexables(int const ref){
		const int p = 1 + detag(ref);
		const int n = detag(getRef(ref));
		std::vector<int> xs(MAXIND);
		for (int i = 0; i < MAXIND && i < n; i++){
		  const int cell = deref(heap[p + i]);
		  xs[i] = cell2index(cell);
		}
		return xs;
	}

	/* 
	  * tests if the head of a clause, not yet copied to the heap
	  * for execution could possibly match the current goal, an
	  * abstraction of which has been place in xs
	*/ 
	bool Engine::match(std::vector<int> xs, Clause* C0){
		for (int i = 0; i < MAXIND; i++){
		  const int x = xs[i];
		  const int y = C0 -> xs[i];
		  if (0 == x || 0 == y)
			continue;
		  if (x != y)
		  {
			return false;
		  }
		}
		return true;
	}

	/*
	 * transforms a spine containing references to choice point and
	 * immutable list of goals into a new spine, by reducing the
	 * first goal in the list with a clause that successfully
	 * unifies with it - in which case places the goals of the
	 * clause at the top of the new list of goals, in reverse order
	*/
	Spine* Engine::unfold(Spine* G){ 
		const int ttop = trail->getTop();
		const int htop = getTop();
		const int base = htop + 1;
		const int goal = IntList::getHead(G->gs);
		//cout << "TTOP G" << G -> ttop << " BASE " << G -> base << " GOAL " << goal << " G GS "  << G-> gs->toString();
		makeIndexArgs(G, goal);
		const int last = G -> cs.size();
		for (int k = G->k; k < last; k++){ 
		Clause* C0 = clauses[G->cs[k]];
		if (!match(G->xs, C0))
		{  
			continue;
		}
		  const int base0 = base - (C0->base);
		  const int b = tag(V, base0);
		  const int head = pushHead(b, C0);

		  ustack->clear(); // set up unification stack
		  ustack->push(head);
		  ustack->push(goal); 
		  if (!unify(base))
		  {   
			unwindTrail(ttop);
			setTop(htop);
			continue;
		  }
		  std::vector<int> gs = pushBody(b, head, C0);
			IntList* newgs = nullptr;
			newgs = IntList::getTail(IntList::app(gs, IntList::getTail(G->gs))); 
			G->k = k + 1;  
		  if(!(newgs == nullptr)){ 
				return new Spine(gs, base, IntList::getTail(G->gs), ttop, 0, cls);
			}
		  else{   
			  return answer(ttop);
			}

		} // end for

		return nullptr;
	  }

    /**
     * extracts a query - by convention of the form
     * goal(Vars):-body to be executed by the engine
    */ 
	Clause* Engine::getQuery(){  
		if(clauses.size() >= 1)
			return clauses[clauses.size() - 1];
		return NULL;
	}

	/**
    * returns the initial spine built from the
    * query from which execution starts
	*/
	Spine* Engine::init(){	
	
		const int base = size();
		Clause* G = getQuery();
		if(G != NULL){ 
			Spine* Q = new Spine(G->hgs, base, NULL , trail->getTop(), 0, cls); 
			spines -> push(Q);	 
			return Q;
		} 
		return nullptr;
	}
	/**
     * returns an answer as a Spine while recording in it
     * the top of the trail to allow the caller to retrieve
     * more answers by forcing backtracking
    */
   	Spine* Engine::answer(int const ttop){ 
			if(spines->elems.size() > 0)
				return new Spine(spines ->elems.at(0)-> hd, ttop); // ATTTENNNNNNNNNTIOOOOOOOOOOOOOONNNNNNNN!!!!!!!!
			return nullptr;
		}

 	/**
     * detects availability of alternative clauses for the
     * top goal of this spine
    */
    bool Engine::hasClauses(Spine* S){
		if(S != NULL)
		return ((S->k) < (S->cs.size()) );
		return false;
	}

 	/**
     * true when there are no more goals left to solve
    */
	bool Engine::hasGoals(Spine* S){
		return !(S -> gs == NULL);
	}

 	/**
     * removes this spines for the spine stack and
     * resets trail and heap to where they where at its
     * creating time - while undoing variable binding
     * up to that point
    */
	void Engine::popSpine(){
		Spine*  G = spines->pop();
		unwindTrail(G->ttop);
		setTop(G->base - 1);
	}

	/**
	 * main interpreter loop: starts from a spine and works
	 * though a stream of answers, returned to the caller one
	 * at a time, until the spines stack is empty - when it
	 * returns null
	*/
	Spine* Engine::yield(){  
		while (!spines->empty()){ 
		  Spine* G = spines->top();
 
		  if (!hasClauses(G)){
				popSpine(); // no clauses left   
				continue;
		  }
		  Spine* C = unfold(G);
		  if (C == nullptr){
				popSpine(); // no matches   
				continue;
		  }
		  if (hasGoals(C)){ 
				spines->push(C);  
				continue;
			}  
			return C; // answer
		} 
		return nullptr;
	}

	/**
     * retrieves an answers and ensure the engine can be resumed
     * by unwinding the trail of the query Spine
     * returns an external "human readable" representation of the answer
	*/ 
	vector<string> Engine::ask(){
		vector<string> R; 
		query = yield(); 
		if (nullptr == query)
		{
		  return R;
		}
		const int res = answer(query->ttop)->hd;
		R = exportTerm(res);
		unwindTrail(query->ttop);
		return R;
	}
  
	/**
   	 * initiator and consumer of the stream of answers
   	 * generated by this engine
	*/ 
	void Engine::run(){
		long ctr = 0;
		for (;; ctr++){   
		vector<string> A = ask();  
		  if (A.size() == 0)
		  {
				break;
		  } 
		  if (ctr < 5)
		  {
				cout << "[" + std::to_string(ctr) + "] " << "*** ANSWER = ";
				showTerm(A);
				cout << endl;
		  }
		}
		if (ctr > 5)
		{
			cout << "...";
		}
		 cout << "\nTOTAL ANSWERS= " << std::to_string(ctr) << endl;
	}

	// // indexing extensions - ony active if START_INDEX clauses or more
	vector<IntMap*> Engine::vcreate(int const l){
		vector<IntMap*> vss(l);
		for (int i = 0; i < l; i++)
		{
		  vss[i] = new IntMap();
		} 
		return vss;
	}

	void Engine::put(vector<IMap<int>*> imaps, vector<IntMap*> vss, vector<int> keys, int const val){
		for (int i = 0; i < imaps.size(); i++){
			IMap<int> iM; // ATTTTTTTTTTTTTTENNNNNNNNNNNNTIONNNNNNNNNNNN!!!!!!!!!!!!!
			const int key = keys[i];
		  if (key != 0)
		  {
			iM.put(imaps, i, key, val);
		  }
		  else
		  {
			vss[i]->add(val);
		  }
		}
	}

	vector<IMap<int>*>* Engine::index(vector<Clause*> clauses, vector<IntMap*> vmaps){
		if (clauses.size() < START_INDEX)
		{
		  return nullptr;
		}
		IMap<int> im;
		vector<IMap<int>*> imaps = im.create(vmaps.size());
		for (int i = 0; i < clauses.size(); ++i)
		{
		  Clause* c = clauses[i];
		  put(imaps, vmaps, c->xs, i + 1); // $$$ UGLY INC

		}
		vector<IMap<int>*>* imPtr = &imaps;
	// 		TO - DO
	// 		Main::pp("INDEX");
	// 		Main::pp(IMap::show(imaps));
	// 		Main::pp(Arrays->toString(vmaps));
	// 		Main::pp(L"");
		return imPtr;
	}
	 
	// Builds a new engine from a natural-language style assembler.nl file
	Engine::~Engine(){
	//	delete syms;
		free(heap);
		delete trail;
		delete ustack;
		delete spines;
		delete query;
	}

	Engine::Engine(const std::string fname){
		makeHeap();
		trail = new IntStack();
		ustack = new IntStack();  
		clauses = dload(fname); 
		cls = toNums(clauses); 
		query = init();
		vmaps = vcreate(MAXIND);
		if(index(clauses, vmaps) != NULL)
    		imaps = *(index(clauses, vmaps));
		}

	Engine& Engine::operator=(const Engine& other){ // Assignment overload.
		if( this == &other) return *this;
		else{
			slist = other.slist;
			*heap = *(other.heap);
			*trail = *(other.trail);
			*ustack = *(other.ustack);
			*spines = *(other.spines);
			*query = *(other.query);
			imaps = other.imaps;
			vmaps = other.vmaps;
			clauses = other.clauses;
			cls = other.cls;
			syms = other.syms; 
		}
	}
	Engine::Engine(Engine &other){ // copy constructor.
		slist = other.slist;
		*heap = *(other.heap);
		*trail = *(other.trail);
		*ustack = *(other.ustack);
		*spines = *(other.spines);
		*query = *(other.query);
		imaps = other.imaps;
		vmaps = other.vmaps;
		clauses = other.clauses;
		cls = other.cls;
		syms = other.syms; 
	} 

  	template<typename K>
  	void Engine::printVector(vector<K> x, bool flag){
	  if(flag == true)
		cout << "(";
      for(auto t = x.begin(); t != x.end(); ++t){
        cout << *t;
      }
      cout << ")";
	}
	
	template<typename K>
  	void Engine::printVector(vector<K> x, int limit){
	  cout << " [";
	  int tlimit =0;
      for(auto t = x.begin(); t != x.end() && tlimit <= limit; ++t, ++tlimit){
        cout << *t << " ";
      }
      cout << "]";
    }
}

// int main()
// {
// 		string fname = "perms.pl.nl";
// 	  	iProlog::Engine obj(fname); 
// 		cout << "Heap length:" << obj.heap.size() << "\n";
// 		cout << "Clauses Array: ";
// 		iProlog::Engine::printVector<iProlog::Clause*>(obj.clauses, true);
// 		cout << "Int Clause Array with elements equal to 'Clause' :";
// 		iProlog::Engine::printVector<int>(obj.cls, true);
// 		cout  << "\n"; 
// 	   	cout << "Symbol map:";
// 		obj.printMap(obj.syms);
// 		cout  << "\n"; 
// 		cout << "Symbol List:";
// 		iProlog::Engine::printVector<string>(obj.slist, true);
// 		cout  << "\n";  
// 		obj.run();
// 	return 0;
// }
/*
  JAVA OUTPUT:
  
  perms.pl.nl:

  Heap length:32768
  Clauses Array: [iProlog.Clause@15db9742, iProlog.Clause@6d06d69c, iProlog.Clause@7852e922]
  Int Clause Array with elements equal to 'Clause' :[0, 1, 2]
  Symbol map:{add=0, s=1, goal=2}
  Symbol List:[add, s, goal]
  Spine Query:iProlog.Spine@4e25154f
  ObStack Spine:[iProlog.Spine@4e25154f]
  IMap array of Integer: null
  IntMap array:[{}, {}, {}]
  [0] *** ANSWER=[goal, [s, [s, [s, [s, 0]]]]]
  TOTAL ANSWERS=1

  perms.pl.nl:
  
	Heap length:32768
	Clauses Array: [iProlog.Clause@15db9742, iProlog.Clause@6d06d69c, iProlog.Clause@7852e922, iProlog.Clause@4e25154f, iProlog.Clause@70dea4e, iProlog.Clause@5c647e05, iProlog.Clause@33909752, iProlog.Clause@55f96302, iProlog.Clause@3d4eac69, iProlog.Clause@42a57993, iProlog.Clause@75b84c92]
	Int Clause Array with elements equal to 'Clause' :[0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10]
	Symbol map:{eq=0, sel=1, list=2, perm=3, nil=4, app=5, nrev=6, input=7, goal=8}
	Symbol List:[eq, sel, list, perm, nil, app, nrev, input, goal]
	Spine Query:iProlog.Spine@6bc7c054
	ObStack Spine:[iProlog.Spine@6bc7c054]
	IMap array of Integer: null
	IntMap array:[{}, {}, {}]
	[0] *** ANSWER=[goal, [list, 11, [list, 10, [list, 9, [list, 8, [list, 7, [list, 6, [list, 5, [list, 4, [list, 3, [list, 2, [list, 1, nil]]]]]]]]]]]]
	TOTAL ANSWERS=1

*/
