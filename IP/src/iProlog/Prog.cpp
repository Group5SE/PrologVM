/*
==============================================================================================
Author: Keertana Sadam, Bhavana 
Modifications and Enhancements: Karthik Venkataramana Pemmaraju.
Individual Compilation:g++ Prog.cpp Engine.cpp -std=c++11 -c 
Written on 12/11/2017
===============================================================================================
*/


#include "Prog.h"  
#include <map> 
#include <iterator>
#include <vector>
#include <array>
#include <type_traits> 
using namespace std;

namespace iProlog {
	Prog::Prog(const string fname) :Engine(fname) // Extending Engine Class.
	{

	}
	template<typename T>
	string Prog::showTerm(T* ptr){	 // Overriding the Engine method
		return (to_string(2)); 
	}

	void Prog::ppCode() { // Printing Clauses.
		cout << "\nSYMS:";
		printMap(syms);
		cout << "\n\nCLAUSES:\n";
		for (int i = 0; i < clauses.size(); i++) {
			Clause *C = clauses[i];
			cout << "["  << i  << "]:" << showClause(C);
		}
		cout << "";
	}

	string Prog::showClause(Clause *s){
		int l = s->hgs.size();
		Engine *E;
		string buf = "";
		buf +="---base:[" + std::to_string(s->base) + "] neck: " + std::to_string(s->neck) + "-----\n";
		buf +=showCells(s->base, s->len); // TODO
		buf +="\n";
		buf +=showCell(s->hgs[0]);  
		buf +=" :- [";
		for (int i = 1; i < l; i++){
			int e = s->hgs[i];
			buf +=showCell(e);
			if (i < l - 1)
			{
				buf +=", ";
			}
		}
		buf +="]\n";
		int i = s -> hgs[0];
		buf += showTerm(i);
		if (l > 1){
			buf +=":-\n";
			for (int i = 1; i < l; i++){
				int e = s->hgs[i];
				buf +="   ";
				buf += showTerm(e);
				buf +=".\n";
			}
		}
		else
		{
			buf +=".\n";
		}
		buf +="\n";
		return buf; // convert to toString();
	}

	string Prog::showTerm(int x){
		return showTerm(exportTerm(x)) + ")";
	}

	string Prog::showTerm(vector<string> O){ 
		 return printVector(O, false);
	}
 
   	template<typename K>
  	string Prog::printVector(vector<K> x, bool flag){
	  	string s = "";
	  	if(flag == true)
			s += "";
      for(int t= 0; t < x.size(); t++){
		s += x[t];
		if(t == 0)
			s += "(";
		else if(t < x.size() - 1)
			s += ",";
      } 
	  return s;
	} 
}