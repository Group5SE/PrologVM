/*
==============================================================================================
Author: Karthik Venkataramana Pemmaraju.
Compilation: g++ Engine.cpp -std=c++11 -c 
Written on 11/11/2017
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
			IntStack *cs, *gs; 
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
								//Is = new IntStack(); NECESSARY?
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
								//Is = new IntStack(); NECESSARY?
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
		Clause* C; // TO - DO = putClause(cs->toArray(), tgs, neck); (TO - DO)
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
 
	// /// places a clause built by the Toks reader on the heap 
	// Clause *putClause(std::vector<int> &cs, std::vector<int> &gs, int const neck){
	// 	const int base = size();
	// 	const int b = tag(V, base);
	// 	const int len = cs.size();
	// 	pushCells(b, 0, len, cs);
	// 	for (int i = 0; i < gs.size(); i++){
	// 	  gs[i] = relocate(b, gs[i]);
	// 	}
	// 	const std::vector<int> xs = getIndexables(gs[0]);
	// 	return new Clause(len, gs, base, neck, xs);
	//   }
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

}