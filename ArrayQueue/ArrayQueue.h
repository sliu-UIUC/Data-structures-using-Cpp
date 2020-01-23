#include "Queue.h"
#include<iostream>

using namespace std;

template <typename T>
class ArrayQueue: public Queue <T>{
public: 
	ArrayQueue();
	ArrayQueue(const ArrayQueue<T> &obj);
	~ArrayQueue();
	void enqueue(const T &t);
	T dequeue();
	T peek() const;
	bool isEmpty() const;
	
private: 
	int enq, top, size;
	T *q_ptr;
	
};

template<typename T>
	ArrayQueue<T>::ArrayQueue() {
		enq = 0;
		size = 10;
		top = -1;
		q_ptr = new T[size];
	}

template<typename T>
	ArrayQueue<T>::ArrayQueue(const ArrayQueue<T> &obj) {
		enq = obj.enq;
		size = obj.size;
		top = obj.top;
		q_ptr = new T[size];
		for(int i = 0;i<size; i++) {
			q_ptr[i] = obj.q_ptr[i];
		}
	}

template<typename T>
	ArrayQueue<T>::~ArrayQueue() {
		delete [] q_ptr;
	}

template<typename T>
	void ArrayQueue<T>::enqueue(const T &t) {
		if(top == size -1) {
			T *tmp = q_ptr;
			q_ptr = new T[size*2];
			for (int i=0; i!=size;++i) {
				q_ptr[i] = tmp[i];
			} 
			size = size*2;
		}
		q_ptr[++top] = t;
	}
	
template<typename T>
	T ArrayQueue<T>::dequeue() {
		if(!isEmpty()){
			return q_ptr[enq++];
		} else {
			cout<<"Error:Queue Is Empty"<<endl;
		}
		return 0;
	}

template<typename T>
	T ArrayQueue<T>::peek() const {
		if(!isEmpty()) {
			return q_ptr[enq];
		} else {
			cout<<"Error:Queue Is Empty"<<endl;
		}
		return 0;
	}

template<typename T>
	bool ArrayQueue<T>::isEmpty() const { return top-enq == -1;}
