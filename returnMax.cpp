#include<vector>
#include<iostream>
using namespace std;

template<typename C>
typename C::value_type myMax(const C &c) {
	typename C::value_type best = *c.begin();
	for(auto x:c){
		if(best<x) best = x; 
	}

	return best;
}

int main () {
	
}
