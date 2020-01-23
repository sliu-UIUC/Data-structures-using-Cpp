#include "Stack.h"
#include<iostream>

using namespace std;

template<typename T>
class ArrayStack: public Stack <T> {
public: 
	ArrayStack();
	ArrayStack(const ArrayStack<T> &obj);
	~ArrayStack();
	void push(const T &t);
	T pop();
	T peek() const;
	bool isEmpty() const;
private:
	int size, top;
	T *stk_ptr;
};
template<typename T>
       ArrayStack<T>::ArrayStack() {
                size = 10;
                top = -1;
                stk_ptr = new T[size];
        }

template<typename T>
	ArrayStack<T>::ArrayStack(const ArrayStack<T> &obj) {
		size = obj.size;
		top = obj.top;
		stk_ptr = new T[size];
		for (int i =0; i<size; i++) {
			stk_ptr[i] = obj.stk_ptr[i];
		}
	} 

template<typename T>
        ArrayStack<T>::~ArrayStack() {
                delete[] stk_ptr;
        }

template<typename T>
        void ArrayStack<T>::push (const T &t) {
                if(top == size -1) {
                        T *tmp = stk_ptr;
                        stk_ptr = new T[size*2];
                        for (int i =0; i!=size;++i) {
                                stk_ptr[i] = tmp[i];
                        }
                        size = size*2;
                }
                stk_ptr[++top] = t;
        }

template<typename T>
        T ArrayStack<T>::pop() {
                if(!isEmpty()) {
                        return stk_ptr[top--];
                } else {
                        cout<<"None. Stack Is Empty"<<endl;
                }
                return 0;
        }

template<typename T>
        T ArrayStack<T>::peek() const {
                if(!isEmpty()) {
                        return stk_ptr[top];
                } else {
                        cout<<"None.Stack Is Empty"<<endl;
                }
                return 0;
        }

template<typename T>
        bool ArrayStack<T>::isEmpty() const { return top == -1;}
