#include "stack.h"
#include <iostream>

using namespace std;

template<class T>
  class Array_stack : public GeneralStack<T>{
	int sz,top;
	T*the_stack;
  public:
	Array_stack(int Nitems){
		 sz = Nitems; 
		 the_stack = new T[sz];
		 top = sz;
	 }

	Array_stack(){ 
		sz = 100; 
		the_stack = new T[sz];
		top = sz; 
	}

	~Array_stack() {
		 delete[] the_stack; 
	}

	void push(T x) {
	 	if(!isfull){
			the_stack[--top] = x;
		} else {return cout<<"Error";}
	 }
	
	T pop(){ 
		if(!isempty){
			return (the_stack[top++]); 
		} else {return cout<<"Error";}
	}

	bool isempty(){
		 return( top == sz ); 
	}

	bool isfull(){
		 return( top == 0 ); 
	}
};
