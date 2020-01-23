#include<iostream>

using namespace std;

template<typename T>

class ArrayList { 

public: 
	
	ArrayList();
	ArrayList(const ArrayList &that);
	ArrayList<T> &operator = (const ArrayList<T> &al);

	~ArrayList();
	void push_back(const T &t); //add to the end 
	void pop_back(); 	//remove last element
	int size() const;
	void clear(); 
	void insert (const T &t, int index); //insert the elem before a index 
	const T &operator[] (int index) const; //get the element at a index
	T &operator[] (int index) ; //get the element ata index
	void remove(int index); //remove the item at a given index
 
	public:
                typedef T value_type;

                class iterator {
                                T *iter;
                        public:
                                iterator(T *l):iter(l){}
                                iterator():iter(nullptr) {}
                                iterator(const iterator &i):iter(i.iter) {}
                                T &operator*() { return *iter; }
                                bool operator==(const iterator &i) const { 
					return iter == i.iter;
				}
                                bool operator!=(const iterator &i) const {  
					return iter != i.iter;
				}
                                iterator &operator=(const iterator &i) {
					return iter = i.iter; 
				}
                                iterator &operator++() { 
					++iter;
					return *this;  
				}
                                iterator &operator--() { 
					--iter;
					return *this; 
				}
                                iterator operator++(int) {
                                        iterator tmp(iter);
                                        ++iter;
                                        return tmp;
                                }
                                iterator operator--(int) {
                                        iterator tmp(iter);
                                        --iter;
                                        return tmp;
                                }
                };
   		class const_iterator {
                                T *iter;
                        public:
                                const_iterator(T *l):iter(l) {}
                                const_iterator():iter(nullptr) {}
                                const_iterator(const const_iterator &i):iter(i.iter){}
                                const T &operator*() { 
					return *iter; 
				}
                                bool operator==(const const_iterator &i) const {
					 return iter == i.iter; 
				}
                                bool operator!=(const const_iterator &i) const { 
					return iter != i.iter; 
				}
                                const_iterator &operator=(const const_iterator &i) { 
					return iter = i.iter;
				}
                                const_iterator &operator++() { 
					++iter;
					return *this;
				}
                                const_iterator &operator--() { 
					--iter;
					return *this;
				}
                                const_iterator operator++(int) {
                                        const_iterator tmp(iter);
                                        ++iter;
                                        return tmp;
                                }
                                const_iterator operator--(int) {
                                        const_iterator tmp(iter);
                                        --iter;
                                        return tmp;
                                }
                };

	iterator begin();
	const_iterator begin() const ;
	iterator end();	
	const_iterator end() const;
	const_iterator cbegin() const;
	const_iterator cend() const ;
	 
private: 
	T *arr;
	int sz;
	int numOfElem; 
};

template<typename T>
typename ArrayList<T>::iterator ArrayList<T>::begin(){
	return iterator(arr);
}

template<typename T>
typename ArrayList<T>::const_iterator ArrayList<T>::begin() const {
	return const_iterator(arr);
}

template<typename T> 
typename ArrayList<T>::iterator ArrayList<T>::end() {
	return iterator(arr+numOfElem);
}

template<typename T>
typename ArrayList<T>::const_iterator ArrayList<T>::end() const {
	return const_iterator(arr+numOfElem);
}

template<typename T>
typename ArrayList<T>::const_iterator ArrayList<T>::cbegin() const {
	return const_iterator(arr);
}

template<typename T> 
typename ArrayList<T>::const_iterator ArrayList<T>::cend() const {
	return const_iterator(arr+numOfElem);
}
 
template<typename T>
ArrayList<T>::ArrayList() {
	sz = 20;
	numOfElem = 0;
	arr = new T[sz];
}

template<typename T> 
ArrayList<T>::ArrayList(const ArrayList &that) {
	sz = that.sz;
	numOfElem = that.numOfElem;
	arr = new T[sz];
	for(int i = 0; i< sz; i++) {
		arr[i] = that.arr[i];
	}
}

template<typename T>
ArrayList<T> &ArrayList<T>::operator = (const ArrayList<T> &al) { 
	T *tmp = new T [al.sz];
	for(int i=0; i<al.sz;++i) {
		tmp[i] = al.arr[i];
	}
	sz = al.sz;
	numOfElem = al.numOfElem;
	arr = tmp;
	return *this;
}
//ArrayList<T> &operator = (const ArrayList<T> &al)
template<typename T> 
int ArrayList<T>::size() const {
	return numOfElem;
}

template<typename T> 
void ArrayList<T>::clear() {
	numOfElem = 0;
}

template<typename T>
ArrayList<T>::~ArrayList() {
	delete[] arr;
}

template<typename T>
void ArrayList<T>::push_back(const T &t) {
	if(numOfElem == sz-1) {
                T *tmp = arr;
                arr = new T[sz*2];
                for(int i=0;i!=sz;++i) {
                        arr[i] = tmp[i];
                }
		sz = sz*2;
	}
		arr[numOfElem++] = t;
	
}

template<typename T>
void ArrayList<T>::pop_back(){
	if(numOfElem != 0) {
		T *tmp = arr;
		arr = new T[sz];
		for(int i =0; i<numOfElem-1; i++) {
			arr[i] = tmp[i];
		}
		numOfElem = numOfElem-1;
	} else {
		cout<<"No element in the list"<<endl;
	}
}

template<typename T>
void ArrayList<T>::insert(const T&t, int index) {
	T *tmp = arr;
	int oldNum = numOfElem;
	numOfElem = numOfElem +1;
	if(numOfElem == sz+1) {
                T *tmp = arr;
                arr = new T[sz*2];
                for(int i=0;i!=sz;++i) {
                        arr[i] = tmp[i];
        	}
		sz = sz*2;
	}

	arr = new T[sz];
	for(int i=0; i<index;i++) {
		arr[i] = tmp[i];
	}
	arr[index] = t;
	for(int j = index; j<oldNum;j++) {
		arr[j+1] = tmp[j];
	} 
}

template<typename T>
const T &ArrayList<T>::operator[] (int index) const {
	return arr[index];
}

template<typename T>
T &ArrayList<T>::operator[] (int index) {
	return arr[index];
}

template<typename T>
void ArrayList<T>::remove (int index) {
	T *tmp = arr;
	arr = new T[sz];
	int oldNum = numOfElem;
	numOfElem = numOfElem-1;
	for(int i=0; i<index;i++) {
		arr[i] = tmp[i];
	}
	for(int j = index; j<=oldNum; j++) {
		arr[j] = tmp[j+1];
	}
}
