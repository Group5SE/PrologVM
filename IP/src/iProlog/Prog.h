/*
==============================================================================================
Author: Keertana Sadam, Bhavana 
Modifications and Enhancements: Karthik Venkataramana Pemmaraju.
Compilation:g++ 
Written on 12/11/2017
===============================================================================================
*/


#ifndef PROG
#define PROG

#include "Engine.h" 
 

namespace iProlog {

	class Prog : public Engine
	{
	public:
		
			Prog(std::string fname);

			template<typename T>
			static void pp(T o);
			
			template<typename T>
			static void println(T o);
		
			template<typename T>
			std::string showTerm(T* o);
			
			std::string showTerm(int );

			template<typename K>  
			std::string printVector(std::vector<K>, bool flag);
			
			std::string showTerm(std::vector<std::string> O); 
			void ppCode();
			std::string showClause(Clause *s);
			void ppc(const Spine *S);
	};
}
#endif

