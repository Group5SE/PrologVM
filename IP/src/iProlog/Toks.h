/*
Author: Karthik Venkataramana Pemmaraju
Date: 09/25/2017
Description: .
*/
#include <iostream>
#include <vector>
#include <string>
using namespace std;

namespace iProlog {
  class Toks{
    public:
      // reserved words - with syntactic function
      string IF = "if"; // Declaring these as static does not allow in class initialization.
      string AND = "and";
      string DOT = ".";
      string HOLDS = "holds";
      string LISTS = "lists"; // todo
      string IS = "is"; // todo

      // Function declarations.
      Toks makeToks(const string s, const bool fromFile);

  };
}
