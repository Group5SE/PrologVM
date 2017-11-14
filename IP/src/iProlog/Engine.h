/*
==============================================================================================
Author: Karthik Venkataramana Pemmaraju.
Compilation: g++ Engine.h -std=c++11 -c 
Written on 11/11/2017
===============================================================================================
*/

#ifndef ENGINE // Fileguards to eliminate circular dependencies.
#define ENGINE

#include <string> 
#include <map> 
#include <iterator>
#include <vector>
#include <stdexcept> 
#include "IntStack.h"
#include "ObStack.h"
#include "IntMap.h"
#include "IMap.h"
#include "Spine.h"
#include "Clause.h"
#include "IntList.h"

namespace iProlog{
	// Implements execution mechanism
	class Engine
	{
		private:
			std::vector<std::string> slist;
			/** runtime areas:
			 *
			 * the heap contains code for and clauses their their copies
			 * created during execution
			 *
			 * the trail is an undo list for variable bindings
			 * that facilitates retrying failed goals with alternative
			 * matching clauses
			 *
			 * the unification stack ustack helps handling term unification non-recursively
			 *
			 * the spines stack contains abstractions of clauses and goals and performs the
			 * functions of  both a choice-point stack and goal stack
			 *
			 * imaps: contains indexes for up toMAXIND>0 arg positions (0 for pred symbol itself)
			 *
			 * vmaps: contains clause numbers for which vars occur in indexed arg positions
			*/

 	    	std::vector<int> heap;
 	 		int top = 0;
			int MINSIZE = 1 << 15; // power of 2
			IntStack *trail;
			IntStack *ustack; 
			ObStack<Spine> *spines = new ObStack<Spine>();
			/**
			 * tags of our heap cells - that can also be seen as
			 * instruction codes in a compiled implementation
			 */
			const int V = 0;
			const int U = 1;
			const int R = 2;
			const int C = 3;
			const int N = 4;
			const int A = 5;
			// G - ground?
			const int BAD = 7;
		public:
			Spine *query;
			std::vector<IMap<int>> imaps;
			std::vector<IntMap> vmaps;
			const int MAXIND = 3; // number of index args
			const int START_INDEX = 20; // switches off indexing for less then START_INDEX clauses e.g. <20
			/**
   			* trimmed down clauses ready to be quickly relocated to the heap
			*/
			std::vector<Clause>  clauses;
			std::vector<int> cls;
			std::map<std::string, int> syms;
			Engine(const std::string fname);
			~Engine(); 
			int tag(const int t, const int w);
			// removes tag after flipping sign
			int detag(const int w);
			//extracts the tag of a cell 
			int tagOf(int const w);
			int addSym(std::string sym);
			std::string getSym(const int w);
			void makeHeap(int const size);
			void makeHeap();
			int getTop();
			int setTop(const int);
			void clear();
			void push(const int i);
			int size();
			void expand();
			void ensureSize(const int more);
			std::vector<std::vector<std::string>>* maybeExpand(std::vector<std::string> Ws);
			std::vector<std::vector<std::string>>* mapExpand(std::vector<std::vector<std::string>> Wss);
			std::vector<Clause*> dload(std::string s);
			int encode(const int  t,std::string s);
			int relocate(int const b, int const cell);
			std::vector<int> toNums(std::vector<Clause*> clauses);
			bool isVAR(int  x); 
			int getRef(int x);
			void setRef(int w, int r);
			void unwindTrail(int savedTop);
			int deref(int x);
			std::string showCell(int w);
			template <typename T>
			T* exportTerm(int x); 
			template<typename T>
			void showTerm(int x);
			template<typename T>
			void showTerm(const T& O);
			template<typename T>
			void ppTrail();
			std::vector<int> getSpine(std::vector<int> cs);
			std::string showCells(int const base, int const len);
			std::string showCells(std::vector<int>);
			bool unify_args(int const w1, int const w2);
			bool unify(int const base);
	};
}
#endif