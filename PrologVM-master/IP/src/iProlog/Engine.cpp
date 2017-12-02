/*
==============================================================================================
Author: Karthik Venkataramana Pemmaraju.
Compilation: g++ Engine.cpp -std=c++11 -c 
Written on 11/25/2017
===============================================================================================
*/

#include <stdexcept> 
#include "IntStack.h"
#include "ObStack.h"
#include "IntMap.h"
#include "IMap.h"
#include "Spine.h"
#include "Clause.h"
#include "IntList.h"
#include "Engine.h"
#include <string> 
#include <map> 
#include <iterator>
#include <vector>

using namespace std;
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
		int value = itr -> second;
		if (value == 0){ // If value is not found, then do ...
			const int i = syms.size();
			syms.insert(std::pair <string, int> (sym, i));
			slist.push_back(sym);
		}
		return value;
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
		heap = std::vector<int>(size);
		clear();
  	}

	int Engine::getTop(){
		return top;
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
		const int l = heap.size();
		std::vector<int> newstack(l << 1);
		newstack.assign(heap.begin() , heap.begin() +l);
		heap = newstack;
	}

	void Engine::ensureSize(const int more){
		if (1 + top + more >= heap.size())
			expand();
	}

	std::vector<std::vector<std::string>>* Engine::maybeExpand(std::vector<std::string> Ws){
		const int l = Ws.size();
		std::vector<std::vector<std::string>> *Rss; // ArrayList<String[]>
		const std::string W = Ws[0];
		if (W.length() < 2 || "l:" != W.substr(0, 2))
	 	 	return nullptr;
		std::string V = W.substr(2);
		for (int i = 1; i < l; i++){
			std::vector<std::string> Rs(4);
			std::string Vi = 1 == i ? V : V + "__" + std::to_string(i - 1);
			std::string Vii = V + "__" + std::to_string(i);
			Rs[0] = "h:" + Vi;
			Rs[1] = "c:list";
			Rs[2] = Ws[i];
			Rs[3] = i == l - 1 ? "c:nil" : "v:" + Vii;
			Rss -> push_back(Rs);
		}
		return Rss;
	}
		
	/**
	 * expands, if needed, "lists" statements in sequence of statements
	*/
	std::vector<std::vector<std::string>>* Engine::mapExpand(std::vector<std::vector<std::string>> Wss){
		std::vector<std::vector<std::string>>* Rss;
		std::vector<std::vector<std::string>>::iterator Ws;
		for (Ws= Wss.begin(); Ws < Wss.end(); Ws++){
			std::vector<std::vector<std::string>> *Hss = maybeExpand(*Ws);
			if (nullptr == Hss){
    			std::vector<std::string> ws = std::vector<std::string>(Ws -> size());
				for (int i = 0; i < ws.size(); i++){
						ws[i] = Ws -> at(i);
				}
				Rss -> push_back(ws);
			}
			else{
				for (std::vector<std::vector<std::string>>::const_iterator X = Hss -> begin(); X < Hss -> end(); X++){
					Rss -> push_back(*X);
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
		// std::vector<std::vector<std::vector<std::string>>> Wsss = Toks::toSentences(&s, fromFile); (TO - DO on linux).
		std::vector<std::vector<std::vector<std::string>>> Wsss;
		std::vector<Clause*> Cs;
		for (std::vector<std::vector<std::vector<std::string>>>::iterator Wss = Wsss.begin(); Wss != Wsss.end(); ++Wss){
			// clause starts here
			std::unordered_map<std::string, IntStack*> refs;
			IntStack *cs = new IntStack();
			IntStack *gs = new IntStack(); 
			std::vector<std::vector<std::string>> *Rss = mapExpand(*Wss);
			int k = 0;
		 	for(std::vector<std::vector<std::string>>::iterator ws= Rss -> begin(); ws != Rss -> end(); ++ws){
				// head or body element starts here
				const int l = ws-> size();
				gs->push(tag(R, k++));
				cs->push(tag(A, l));
				for (std::vector<std::string>::iterator w = ws -> begin(); w != ws -> end(); ++w){
					// head or body subterm starts here
					if (1 == w ->size()){ 
						*w = "c:" + *w;
					}
					std::string L = w ->substr(2);
					switch (w -> at(0)){
						case 'c':
							cs -> push(encode(C, L));
							k++;
							break;
						case 'n':
							cs -> push(encode(N, L));
							k++;
							break;
						case 'v':
							{
							std::unordered_map<std::string, IntStack*>::iterator itr = refs.find(L);
							IntStack *Is = itr -> second; // returns map value.
							if (nullptr == Is){
								Is = new IntStack(); // NECESSARY?
								refs.insert({L, Is}); // puts into hash map.
							}
							Is->push(k);
							cs->push(tag(BAD, k)); // just in case we miss this
							k++;
							}
						 	break;
						case 'h':
							{
							std::unordered_map<std::string, IntStack*>::iterator itr = refs.find(L);
							IntStack *Is = itr -> second;
							if (nullptr == Is){
								Is = new IntStack(); // NECESSARY?
								refs.insert({L, Is}); // puts into hash map.
							}
							Is->push(k - 1);
							cs->set(k - 1, tag(A, l - 1));
							gs->pop();
							}
							break;
						default:
							std::cout << " FORGOTTEN= " <<  *w ;
					} // end subterm
				} // end element
		  	} // end clause	
		// linker
		for(auto &itr: refs){
			IntStack* Is = itr.second;
			// finding the A among refs
			int leader = -1;
			for (auto &j: Is -> toArray()){
				if (A == tagOf(cs->get(j))){
					leader = j;
					break;
			  	}
			}
			if (-1 == leader){
				// for vars, first V others U
			  	leader = Is -> get(0);
			  	for (auto &i: Is -> toArray()){
					if (i == leader)
						cs->set(i, tag(V, i));
					else{
						cs->set(i, tag(U, leader));
					}
				 }
			}
			else{
				for (auto &i: Is -> toArray()){
					if (i == leader)
						continue;	
					cs->set(i, tag(R, leader));
				}
			} 
		}
		const int neck = 1 == gs->size() ? cs->size() : detag(gs->get(1));
		std::vector<int> tgs = gs->toArray();
		Clause* C = putClause(cs->toArray(), tgs, neck); // (TO - DO)
		Cs.push_back(C);
		} // end clause set
		const int ccount = Cs.size();
		std::vector<Clause*> cls(ccount);
		for (int i = 0; i < ccount; i++){
			cls[i] = Cs[i];
		}
		return cls; 
	}
	/*
	 * encodes string constants into symbols while leaving
	 * other data types untouched
	*/
	int Engine::encode(const int  t,std::string s){
		int w;
		try{
		  w = std::stoi(s);
		}
		catch (const std::exception &e)
		{
		  if (C == t)
			w = addSym(s);
		  else
			//pp("bad in encode=" + t + ":" + s);
			return tag(BAD, 666);
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
 		return tagOf(cell) < 3 ? cell + b : cell;
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
	template <typename T>
	T* Engine::exportTerm(int x){
		x = deref(x);
		const int t = tagOf(x);
		const int w = detag(x);
		T res = nullptr;
		switch(t){
		  	case Engine::C:
				res = getSym(w);
		 	 	break;
			case Engine::N:
				res = w; // res = new Integer(w) ( Thought this is the way of doing this.).
		 		break;
		  	case Engine::V: 
				res = "V" + std::to_string(w);
		  		break;
		  	case Engine::R:
		  		{
					int a = heap[w];
					if (A != tagOf(a)){
						return "*** should be A, found=" + showCell(a);
					}
					int n = detag(a);
					std::vector<T> arr(n);
					int k = w + 1;
					for (int i = 0; i < n; i++){
						const int j = k + i;
						arr[i] = exportTerm<T>(heap[j]);
					}
					res = arr;
		  		}
		  		break;
		  	default:
				res = "*BAD TERM*" + showCell(x);
		}
		return &res;
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
	template<typename T>
	void Engine::showTerm(int x){
		showTerm<T>(exportTerm<T>(x));
	}
  
	/**
   	* raw display of a externalized term
   	*/
	template<typename T>
	void Engine::showTerm(const T& O){
		cout << O; // Print the object value here itself.
	}

	template<typename T>
	void Engine::ppTrail(){
		for (int i = 0; i <= trail -> getTop(); i++){
		  const int t = trail -> get(i);
		  cout << "trail[" + std::to_string(i) + "]=" + showCell(t) + ":" + showTerm<T>(t);
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
		std::vector<int> xs(MAXIND);
		for (int i = 0; i < n; i++)
		{
		  const int cell = deref(heap[p + i]);
		  xs[i] = cell2index(cell);
		}
		G->xs = xs;
		if (imaps.size() == 0)
		  return;
		iProlog::IMap<int> iM;
		std::vector<int> cs = iM.get(imaps, vmaps, xs);
		G->cs = cs;
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
		makeIndexArgs(G, goal);
		const int last = G -> cs.size();
		for (int k = G->k; k < last; k++){
		Clause* C0 = clauses[G->cs[k]];
		if (!match(G->xs, C0))
		{
			continue;
		}
		  const int base0 = base - C0->base;
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
		  IntList* newgs = IntList::getTail(IntList::app(gs, IntList::getTail(G->gs)));
		  G->k = k + 1;
		  if (!IntList::isempty(newgs))
		  {
			return new Spine(gs, base, IntList::getTail(G->gs), ttop, 0, cls);
		  }
		  else
		  {
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
		return clauses[clauses.size() - 1];
	}

	/**
    * returns the initial spine built from the
    * query from which execution starts
	*/
	Spine* Engine::init(){	
		IntList* ptr;
		const int base = size();
		Clause* G = getQuery();
		Spine* Q = new Spine(G->hgs, base, ptr -> empty, trail->getTop(), 0, cls);
		spines -> push(Q);
		return Q;
	}
	/**
     * returns an answer as a Spine while recording in it
     * the top of the trail to allow the caller to retrieve
     * more answers by forcing backtracking
    */
   	Spine* Engine::answer(int const ttop){
		return new Spine(spines ->top()-> hd, ttop); // ATTTENNNNNNNNNTIOOOOOOOOOOOOOONNNNNNNN!!!!!!!!
	}

 	/**
     * detects availability of alternative clauses for the
     * top goal of this spine
    */
    bool Engine::hasClauses(Spine* S){
		return S->k < S->cs.size();
	}

 	/**
     * true when there are no more goals left to solve
    */
	bool Engine::hasGoals(Spine* S){
		return !IntList::isempty(S->gs);
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
		  if (nullptr == C){
			popSpine(); // no matches
			continue;
		  }
		  if (hasGoals(C))
		  {
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
	template <typename T>
	T* Engine::ask(){
		query = yield();
		if (nullptr == query)
		{
		  return nullptr;
		}
		const int res = answer(query->ttop)->hd;
		T* R = exportTerm<T>(res);
		unwindTrail(query->ttop);
		return R;
	}
  
	/**
   	 * initiator and consumer of the stream of answers
   	 * generated by this engine
	*/
	template <typename T>
	void Engine::run(){
		long long ctr = 0;
		for (;; ctr++){
		  T* abc = ask<T>();
		  if (nullptr == abc)
		  {
			break;
		  }
		  if (ctr < 5)
		  {
			//  Prog::println("[" + std::to_string(ctr) + "] " + "*** ANSWER=" + showTerm<T>(A));
			;
		  }
		}
		if (ctr > 5)
		{
			;//	Prog::println(L"...");
		}
		// Prog::println(L"TOTAL ANSWERS=" + std::to_wstring(ctr));
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
		for (int i = 0; i < clauses.size(); i++)
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
		delete trail;
		delete ustack;
		delete spines;
		delete query;
	}

	Engine::Engine(const std::string fname){
		makeHeap();
		query = init();
		trail = new IntStack();
		ustack = new IntStack();
		clauses = dload(fname);
    	cls = toNums(clauses);
    	vmaps = vcreate(MAXIND);
    	imaps = *(index(clauses, vmaps));
	}
	Engine& Engine::operator=(const Engine& other){ // Assignment overload.
		if( this == &other) return *this;
		else{
			slist = other.slist;
			heap = other.heap;
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
		heap = other.heap;
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