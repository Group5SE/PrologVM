/*
=====================================================================================================
Author: Karthik Venkataramana Pemmaraju.
Compilation: g++ Toks.h -std=c++11 -c
Description: Splits the given file into tokens and creates a std::vector list.
Date: 10/23/2017.
Tested on 10/27/2017. For tests, see output_tokenizer.txt in test/test_tokenizer folder.
Dependencies:	Please make sure to include BOOST libraries available here:
				http://www.boost.org/doc/libs/1_36_0/libs/tokenizer/tokenizer.htm
				or via command line by: sudo apt-get install libboost-all-dev.
======================================================================================================
*/

#ifndef TOKS
#define TOKS

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include <boost/lexical_cast.hpp>
#include <boost/tokenizer.hpp>
#include <boost/foreach.hpp>
 
namespace iProlog{
	/**
 	* Reads chars from char streams using the current default encoding
 	*/
	class Toks{
		private:
			// reserved words - with syntactic function
			const std::string IF = "if";
	 		const std::string AND = "and";
			const std::string DOT = ".";
	 		const std::string HOLDS = "holds";
			const std::string LISTS = "lists"; // todo
			const std::string IS = "is"; // todo
			const std::ifstream in_stream;
			char str[35];
			std::vector<std::vector<std::vector<std::string>>> Wsss; // Contains all the clauses.
			std::vector<std::vector<std::string>> Wss;	 // Contains compound clauses (:-).
			std::vector<std::string> Ws;	// Contains individual clauses (Ex: add(X,Y,Z).
		public:
			std::string getWord(std::string token);
			std::vector<std::vector<std::vector<std::string>>> toSentences(const std::string &s, bool fromFile);
			void buildOmitSymbolList();
			void buildList(std::string line);
			void display(std::vector<std::vector<std::vector<std::string>>>);
			void empty();
	};
} // close name space.
#endif

