/*
==================================================================
Author: Karthik Venkataramana Pemmaraju
Description: Data structure implementation of a prolog Clause.
Compilation: g<< <<  Clause.cpp -c
Compiled and tested on  09/17/2017
==================================================================
*/
#include "Clause.h"
#include "Spine.h"
using namespace std;
namespace iProlog{

    // Parameterized constructor to instantiate const variables.
    Clause::Clause(int l, vector<int> h, int b, int n, vector<int> x)
        : len(l)
        , hgs(h)
        , base(b)
        , neck(n)
        , xs(x){ // Default constructor for const variables.
    }
    template<typename T>
    void Clause::printVector(vector<T> x){
      cout << " [";
      for(auto t = x.begin(); t != x.end(); ++t){
        cout << *t << " ";
      }
      cout << "]";
    }
    
}

// int main(){
	
// 	 iProlog::Clause c(10, vector<int> {11, 22, 33},0,3, vector<int>{0,1,2});
// 	 cout << "length of heap slice: "<< c.len << endl;
// 	 cout << "head goals pointing to cells in cs: ";
//      iProlog::Clause::printVector<int>(c.hgs);
// 	 cout << "\n heap where this starts: "<<  c.base<< endl;
// 	 cout << "first after the end of the head: "<< c.neck<< endl;
// 	 cout << "indexables in head: "<< endl;
//      iProlog::Clause::printVector<int>(c.xs);
// 	 //c.len = 15; //try to change the values of varaibles to check whethere final keyword is working or not
	 
// }

/*
JAVA OUTPUT:
length of heap slice: 10
head+goals pointing to cells in cs: [11, 22, 33]
heap where this starts: 0
first after the end of the head: 3
indexables in head: [0, 1, 2]

C++ OUTPUT:
E:\Software Engineering\Term Project Clone\IP\src\iProlog>g++ Spine.cpp IntList.cpp  Clause.cpp IntStack.cpp -std=c++11

E:\Software Engineering\Term Project Clone\IP\src\iProlog>a.exe
length of heap slice: 10
head goals pointing to cells in cs:  [11 22 33 ]
 heap where this starts: 0
first after the end of the head: 3
indexables in head:
 [0 1 2 ]
*/
