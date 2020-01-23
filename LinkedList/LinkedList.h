template<typename T>
class LinkedList {
	struct Node {
		Node() {}
		Node(const T &n, Node *pre, Node *ne):data(n),prev(pre), next(ne) {}
		T data;
		Node *prev, *next;
	}; 
  
   public:
	typedef T value_type;
	
	class iterator {
		Node *iter;
	   public:
		iterator(Node *l):iter(l){}
		iterator():iter(nullptr) {}
		iterator(const iterator &i):iter(i.iter){}
		T &operator *() {return iter -> data; }
		bool operator ==(const iterator &i) const {
			return iter == i.iter;
		}
		bool operator != (const iterator &i) const {
			return iter != i.iter;
		}
		iterator &operator = (const iterator &i) {
			iter = i.iter;
			return *this;
		}
		iterator &operator++() {
			iter = iter -> next;
			return *this;
		}
		iterator &operator--(){
			iter = iter -> prev;
			return *this;
		}
		iterator operator++(int){
			iterator tmp(iter);
			iter = iter.next;
			return tmp;
		}
		iterator operator--(int){
			iterator tmp(iter);
			iter = iter.prev;
			return tmp;
		}
		friend class const_iterator;
		friend class LinkedList;
	};

	class const_iterator {
                const Node *iter;
           public:
		const_iterator(const Node *l):iter(l) {}
		const_iterator():iter(nullptr){}
		const_iterator(const const_iterator &i):iter(i.iter){}
		const T &operator *(){
			return iter -> data;
		}
		bool operator==(const const_iterator &i) const{
			return iter == i.iter;
		}
		bool operator!=(const const_iterator &i) const{
			return iter != i.iter;
		}
		const_iterator &operator++() {
			iter = iter -> next;
			return *this;
		}
		const_iterator &operator--() {
			iter = iter -> prev;
			return *this;
		}
		const_iterator operator++(int){
			iterator tmp(iter);
			iter = iter -> next;
			return tmp;
		}    
		const_iterator operator--(int) {
			iterator tmp(iter);
			iter = iter -> prev;
			return tmp;
		}
	};
	
	//General Methods
	
	LinkedList (){ 
		sz = 0;
		sentinel.next = &sentinel;
		sentinel.prev = &sentinel;
	}
	
	LinkedList(const LinkedList &al){
		sz = 0;
		sentinel.next = &sentinel;
		sentinel.prev = &sentinel;
		for (auto &x:al) push_back(x);
	}
	LinkedList &operator = (const LinkedList &al) {
		for (Node *mover = sentinel.next; mover !=&sentinel; mover = mover -> next) {delete mover;}
		sentinel.next = &sentinel;
		sentinel.prev = &sentinel;
		sz = 0;
		for(auto &x:al) push_back(x);
		return *this;
	}
	~LinkedList() {
		for (Node *mover = sentinel.next; mover !=&sentinel; mover = mover -> next) {delete mover;}

	}
	void push_back(const T &t); //add to the end
	void pop_back(); //remove last element
	int size() const;
	void clear();
	iterator insert(iterator position, const T &t); //insert this element before the given index
	const T &operator[] (int index) const;
	T &operator[] (int index);
	iterator erase(iterator position);

	iterator begin();
	const_iterator begin() const; 
	iterator end();
	const_iterator end() const;
	const_iterator cbegin() const;
	const_iterator cend() const;

private: 
	Node sentinel;
	int sz;
};

template<typename T>
void LinkedList<T>::push_back(const T &t) {
	sz = sz + 1;
	Node *n = new Node(t, sentinel.prev, &sentinel);
	n -> prev -> next = n;
	n -> next -> prev = n;	
}

template<typename T>
void LinkedList<T>::pop_back() { 
	Node *n = sentinel.prev;
	n -> prev -> next = &sentinel;
	sentinel.prev = n -> prev;
	delete n;
	sz = sz-1;
}

template<typename T>
int LinkedList<T>::size() const {
	return sz;
}

template<typename T>
void LinkedList<T>::clear() {
	for (Node *i= sentinel.next; i != &sentinel; i = i -> next) delete i;
	sentinel.next = &sentinel;
	sentinel.prev = &sentinel;
	sz = 0;
}

template<typename T>
typename LinkedList<T>::iterator LinkedList<T>::insert(iterator position, const T &t) {
	auto p = position.iter;
	auto newNode = new Node (t, p -> prev, p);
	p -> prev -> next = newNode;
	p -> prev = newNode;
	
sz = sz + 1;
}
template<typename T>
typename LinkedList<T>::iterator LinkedList<T>::erase(iterator position) {
	auto p = position.iter;
	p -> next -> prev = p -> prev;
	p -> prev -> next = p -> next;
	delete p;
	sz = sz -1;
	return p -> next;
}

template<typename T>
const T &LinkedList<T>::operator[] (int index) const {
	Node *mover = sentinel.next;
	for (int i =0; i<index; ++i) mover = mover -> next;
	return mover -> data;
}

template<typename T>
T &LinkedList<T>::operator[](int index) {
	Node *mover = sentinel.next;
        for (int i =0; i<index; ++i) mover = mover -> next;
        return mover -> data;
}

template<typename T>
typename LinkedList<T>::iterator LinkedList<T>::begin(){
	return iterator(sentinel.next);
}
template<typename T>
typename LinkedList<T>::const_iterator LinkedList<T>::begin() const{
	return const_iterator(sentinel.next);
}
template<typename T>
typename LinkedList<T>::iterator LinkedList<T>::end() {
	return iterator(&sentinel);
}
template<typename T>
typename LinkedList<T>::const_iterator LinkedList<T>::end() const {
	return const_iterator(&sentinel);
}
template<typename T>
typename LinkedList<T>::const_iterator LinkedList<T>::cbegin() const {
	return const_iterator(sentinel.next);
}
template<typename T>
typename LinkedList<T>::const_iterator LinkedList<T>::cend() const {
	return const_iterator(&sentinel);
}
