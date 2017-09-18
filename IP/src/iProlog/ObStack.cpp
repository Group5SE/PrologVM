#include<vector>
#include<iostream>
using namespace std;

template <class T>
class ObStack {
	
	private:
		static long const serialVersionUID = 1;
	public:
		T pop() const;
		void push(const T o) const;
		T peek() const;
};

int main(){
	return 0;
}
