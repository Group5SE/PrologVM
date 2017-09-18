#include <iostream>
#include <vector>
using namespace std;

namespace iProlog {

class Spine{
private:
const int hd; // head of the clause to which this corresponds
const int base; // top of the heap when this was created
const IntList gs; // goals - with the top one ready to unfold
const IntList gs; // goals - with the top one ready to unfold
const int k;
const vector<int> xs ;// index elements
onst vector<int> xs ;// array of  clauses known to be unifiable with top goal in gs

public:
Spine(vector<int> gs0,int base,IntList gs,int ttop,int k,vector<int> cs)
};

Spine::Spine(vector<int> gs0,int b,IntList glis,int t,int ki,vector<int> csx)
    :hd(gs0[0])
	,base(b)
	,gs(glis)
	,ttop(t)
	,k(ki)
	,cs(csx){
}


Spine::Spine(int hd2,int t2)
  	:hd(hd2)
	,ttop(t2){
}

	

}