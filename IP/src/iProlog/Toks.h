/*
=========================================================================================
Author: Karthik Venkataramana Pemmaraju.
Compilation: g++ Toks.h -std=c++11 -c
Description: Splits the given file into tokens and creates a vector list.
Date: 10/23/2017.
Tested on 10/27/2017. For tests, see output_tokenizer.txt in test/test_tokenizer folder.
Dependencies:	Please make sure to include BOOST libraries available here:
				http://www.boost.org/doc/libs/1_36_0/libs/tokenizer/tokenizer.htm
				or via command line by: sudo apt-get install libboost-all-dev.
==========================================================================================
*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include <boost/lexical_cast.hpp>
#include <boost/tokenizer.hpp>
#include <boost/foreach.hpp>

using namespace std;
using namespace boost;
namespace iProlog
{
	/**
 	* Reads chars from char streams using the current default encoding
 	*/
	class Toks{
		private:
			// reserved words - with syntactic function
			const string IF = "if";
	 		const string AND = "and";
			const string DOT = ".";
	 		const string HOLDS = "holds";
			const string LISTS = "lists"; // todo
			const string IS = "is"; // todo
			const ifstream in_stream;
			char str[35];
			vector<vector<vector<string>>> Wsss; // Contains all the clauses.
			vector<vector<string>> Wss;	 // Contains compound clauses (:-).
			vector<string> Ws;	// Contains individual clauses (Ex: add(X,Y,Z).
		public:
			string getWord(string token);
			vector<vector<vector<string>>> toSentences(const string &s, bool fromFile);
			void buildOmitSymbolList();
			void buildList(string line);
			void display(vector<vector<vector<string>>>);
			void empty();
	};

	/**
	*	Given a token extracts the individual word or number and appends tag for it (c for condition, v for variable n for number).
	*/
	string Toks::getWord(string token)
	  {
		string t = "";
		char first = token[0];
		if((first == '_') || isupper(first)) // If it starts with _ or capital letters then it is a variable!
			t = "v:" + token;
		else{
			int number;
			try
			{
				number = lexical_cast<int>(token);
				if (abs(number) < 1 << 28) { // Number if in the given range.
					t = "n:" + token;
				} else {
					t = "c:" + token; 		 // condition (and, holds etc) if not any of the above.
				}
			}
			catch(bad_lexical_cast& e)		// Exception is thrown in case if a word is given to cast.
			{
				t = "c:" + token;
			}
		}
		return t;
	  }

	/**
	*	Builds our str class variable which consists of set of symbols that we ignore.
	*/
	void Toks::buildOmitSymbolList(){
		Toks::str[0] = ' ';
		int index = 1;
		for(int i = 33; i <= 126 ; i++){
			if((i == 95) || i== 46) // _ or . (We need both of them, Sigh!)
				continue;
			if( ((i >= 33) && (i <= 47)) || ((i >= 58) && (i <= 64)) || ((i >= 91) && (i <= 96)) || ((i >= 123) && (i <= 126)) )  // Professor wrote ASCII 55 - 64 in comments which is wrong, it is infact 58 - 64.
			{
				Toks::str[index]  = (char)i;
				index++;
			}
		}
	}

	/**
	*	Clear if any previous values are present in our vectors.
	*/
	void Toks::empty(){
		Toks::Ws.clear();
		Toks::Wss.clear();
		Toks::Wsss.clear();
	}
	/**
	*	Given a string, builds our vector list!
	*/
	void Toks::buildList(string line)
	{
		typedef tokenizer<char_separator<char>> tokenizer;
		char_separator<char> sep(Toks::str);
		tokenizer tok{line, sep};
		BOOST_FOREACH(string t, tok)
		{
		   t = Toks::getWord(t);
		   if (t.compare("c:.") == 0)
		   {
		   Toks::Wss.push_back(Toks::Ws);
		   Toks::Wsss.push_back(Toks::Wss);
		   Toks::Wss.clear();
		   Toks::Ws.clear();
		   }
		   else if (t.compare("c:" + Toks::IF) == 0)
		   {
		   Toks::Wss.push_back(Toks::Ws);
		   Toks::Ws.clear();
		   }
		   else if (t.compare("c:" + Toks::AND) == 0)
		   {
			Toks::Wss.push_back(Toks::Ws);
			Toks::Ws.clear();
		   }
		   else if (t.compare("c:" + Toks::HOLDS) == 0)
		   {
		   const string w = Toks::Ws[0];
		   Toks::Ws[0] = "h:" + w.substr(2, w.length()); // Gets the remaining characters after 3rd character.
		   }
		   else if (t.compare("c:" + Toks::LISTS) == 0)
		   {
		   const string w = Toks::Ws[0];
		   Toks::Ws[0] = "l:" + w.substr(2, w.length());
		   }
		   else if (t.compare("c:" + Toks::IS) == 0)
		   {
		   const string w = Toks::Ws[0];
		   Toks::Ws[0] = "f:" + w.substr(2, w.length());
		   }
		   else
		   {
			Toks::Ws.push_back(t);
		   }
	   	}
	}

	/**
	*	@param : s -  Name of the file, we want to tokenize.
	*	@param : fromFile - Specifies, if s is from file or entire code is in single string, s.
	* 	@return: returns Wsss which is an array of all clauses.
	*   @desc : Our main driver fucntion which does the majority of tokenizing work.
	*/
	vector<vector<vector<string>>> Toks::toSentences(const string &s, bool fromFile)
	{
		ifstream in_stream;
		in_stream.open(s);
		string line;
		Toks::buildOmitSymbolList();
		Toks::empty();
		if(fromFile)
		{
			while (in_stream.good())
			{
				getline(in_stream, line);
				Toks::buildList(line);
			}
		}
		else
		{
			Toks::buildList(s);
		}
		return Toks::Wsss;
	}

	/**
	*	Displays a 3-D vector(used for testing!).
	*/
	void Toks::display(vector<vector<vector<string>>> vec)
	{
		  cout << "[ ";
		  for (int i = 0; i < vec.size(); i++)
		  {
			  cout << "[";
			  for (int j = 0; j < vec[i].size(); j++)
			  {
				  cout << "[ ";
				  for (int k = 0; k < vec[i][j].size(); k++)
				  {
					  if(k == vec[i][j].size() - 1)
						  cout << vec[i][j][k];
					  else
						  cout << vec[i][j][k] << " , " ;

				  }
				  if(j == vec[i].size() - 1)
					  cout << "]";
				  else
					  cout << "], ";
			  }
			  cout << "]";
		  }
		  cout << "] \n";
	} // close dispay().
} // close name space.
	//	Driver functions to test Toks.h (09/27/2017)
	//	Karthik Venkataramana Pemmaraju
	//	Place add.pl.nl file in test/ directory into the current directory.
	//	TO - DO (SHOULD WORK ON REMOVING SOURCE COMMENTS IN THE PROGRAM :()
	// int main()
	// {
	// 	  	iProlog::Toks t;
	// 		vector<vector<vector<string>>> Fsss = t.toSentences("add.pl.nl", true); // Reading from file.
	// 		t.display(Fsss);
	// 		cout << "\nFor String: \n";
	// 		vector<vector<vector<string>>> Ssss = t.toSentences("add 0 X X .", false); // Reading from string.
	// 		t.display(Ssss);
	// 		return 0;
	//  }
