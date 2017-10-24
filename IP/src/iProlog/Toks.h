/*
Author: Karthik Venkataramana Pemmaraju and Charishma Damuluri.
Compilation: g++ Toks.h -std=c++11
Description: Splits the given file into tokens.
Date: 10/23/2017.
Reviewers:Keerthana Sadam,Bhavana
*/
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

namespace iProlog
{
	class Toks{
  	public:
			// reserved words - with syntactic function
			const string IF = "if";
	 		const string AND = "and";
			const string DOT = ".";
	 		const string HOLDS = "holds";
			const string LISTS = "lists"; // todo
 			const string IS = "is"; // todo
			Toks makeToks(const string s, const bool fromFile);
			Toks(ifstream *ifs); // TO - DO
			string getWord();
			vector<vector<vector<string>>> toSentences(const string &s, bool const fromFile);
		};

	  Toks Toks::makeToks(const string s, const bool fromFile){
			if(fromFile){
			ifstream ifs(s, ifstream::in);
			ifstream *inputStream = &ifs;
			Toks T(inputStream);
		  return T;
			}
		}

	  Toks::Toks(ifstream *ifs)
	  {
		// resetSyntax();
		// eolIsSignificant(false);
		// ordinaryChar(L'.');
		// ordinaryChars(L'!', L'/'); // 33-47
		// ordinaryChars(L':', L'@'); // 55-64
		// ordinaryChars(L'[', L'`'); // 91-96
		// ordinaryChars(L'{', L'~'); // 123-126
		// wordChars(L'_', L'_');
		// wordChars(L'a', L'z');
		// wordChars(L'A', L'Z');
		// wordChars(L'0', L'9');
		// slashStarComments(true);
		// slashSlashComments(true);
		// ordinaryChar(L'%');
	  }
//
// 	  virtual std::wstring getWord()
// 	  {
// 		std::wstring t = L"";
//
// 		int c = TT_EOF;
// 		try
// 		{
// 		  c = nextToken();
// 		  while (std::isspace(c) && c != TT_EOF)
// 		  {
// 			c = nextToken();
// 		  }
// 		}
// //JAVA TO C++ CONVERTER WARNING: 'final' catch parameters are not available in C++:
// //ORIGINAL LINE: catch (final IOException e)
// 		catch (const IOException &e)
// 		{
// 		  return L"*** tokenizer error:" + t;
// 		}
//
// 		switch (c)
// 		{
// 		  case TT_WORD:
// 		  {
// 			const wchar_t first = sval->charAt(0);
// 			if (std::isupper(first) || L'_' == first)
// 			{
// 			  t = L"v:" + sval;
// 			}
// 			else
// 			{
// 			  try
// 			  {
// 				const int n = static_cast<Integer>(sval);
// 				if (std::abs(n) < 1 << 28)
// 				{
// 				  t = L"n:" + sval;
// 				}
// 				else
// 				{
// 				  t = L"c:" + sval;
// 				}
// 			  }
// //ORIGINAL LINE: catch (final Exception e)
// 			  catch (const std::exception &e)
// 			  {
// 				t = L"c:" + sval;
// 			  }
// 			}
// 		  }
// 		  break;
//
// 		  case StreamTokenizer::TT_EOF:
// 		  {
// 			t = L"";
// 		  }
// 		  break;
//
// 		  default:
// 		  {
// 			t = L"" + StringHelper::toString(static_cast<wchar_t>(c));
// 		  }
//
// 		}
// 		return t;
// 	  }
//
// 	  static std::vector<std::vector<std::vector<std::wstring>>> toSentences(const std::wstring &s, bool const fromFile)
// 	  {
// 		const std::vector<std::vector<std::vector<std::wstring>>> Wsss = std::vector<std::vector<std::vector<std::wstring>>>();
// 		std::vector<std::vector<std::wstring>> Wss;
// 		std::vector<std::wstring> Ws;
// 		Toks * const toks = makeToks(s, fromFile);
// 		std::wstring t = L"";
// 		while (L"" != (t = toks->getWord()))
// 		{
//
// 		  if (DOT == t)
// 		  {
// 			Wss.push_back(Ws);
// 			Wsss.push_back(Wss);
// 			Wss = std::vector<std::vector<std::wstring>>();
// 			Ws = std::vector<std::wstring>();
// 		  }
// 		  else if ((L"c:" + IF)->equals(t))
// 		  {
//
// 			Wss.push_back(Ws);
//
// 			Ws = std::vector<std::wstring>();
// 		  }
// 		  else if ((L"c:" + AND)->equals(t))
// 		  {
// 			Wss.push_back(Ws);
//
// 			Ws = std::vector<std::wstring>();
// 		  }
// 		  else if ((L"c:" + HOLDS)->equals(t))
// 		  {
// 			const std::wstring w = Ws[0];
// 			Ws[0] = L"h:" + w.substr(2);
// 		  }
// 		  else if ((L"c:" + LISTS)->equals(t))
// 		  {
// 			const std::wstring w = Ws[0];
// 			Ws[0] = L"l:" + w.substr(2);
// 		  }
// 		  else if ((L"c:" + IS)->equals(t))
// 		  {
// 			const std::wstring w = Ws[0];
// 			Ws[0] = L"f:" + w.substr(2);
// 		  }
// 		  else
// 		  {
// 			Ws.push_back(t);
// 		  }
// 		}
// 		return Wsss;
// 	  }
//
// 	  static std::wstring toString(std::vector<void*> &Wsss)
// 	  {
// 		return Arrays::deepToString(Wsss);
// 	  }
//
// 	  static void main(std::vector<std::wstring> &args)
// 	  {
// 		Main::pp(toSentences(L"prog.nl", true));
// 	  }

}
