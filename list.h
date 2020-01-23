#ifndef ARRAY_LIST
#define ARRAY_LIST
using namespace std;

template<typename T>
class list {
                unsigned int msize;
                unsigned int capacity;
                T *data;
        public:
                typedef T value_type;

                class iterator {
                                T *loc;
                        public:
                                iterator(T *l):loc(l) {}
                                iterator():loc(nullptr) {}
                                iterator(const iterator &i):loc(i.loc) {}
                                T &operator*() { return *loc; }
                                bool operator==(const iterator &i) const { return loc == i.loc; }
                                bool operator!=(const iterator &i) const { return !(*this==i); }
                                iterator &operator=(const iterator &i) { loc = i.loc; return *this; }
                                iterator &operator++() { ++loc; return *this; }
                                iterator &operator--() { --loc; return *this; }
                                iterator operator++(int) {
                                        iterator tmp(loc);
                                        ++loc;
                                        return tmp;
                                }
                                iterator operator--(int) {
                                        iterator tmp(loc);
                                        --loc;
                                        return tmp;
                                }
                };

                class const_iterator {
                                T *loc;
                        public:
                                const_iterator(T *l):loc(l) {}
                                const_iterator():loc(nullptr) {}
                                const_iterator(const const_iterator &i):loc(i.loc) {}
                                const T &operator*() { return *loc; }
                                bool operator==(const const_iterator &i) const { return loc == i.loc; }
                                bool operator!=(const const_iterator &i) const { return !(*this==i); }
                                const_iterator &operator=(const const_iterator &i) { loc = i.loc; return *this; }
                                const_iterator &operator++() { ++loc; return *this; }
                                const_iterator &operator--() { --loc; return *this; }
                                const_iterator operator++(int) {
                                        const_iterator tmp(loc);
                                        ++loc;
                                        return tmp;
                                }
                                const_iterator operator--(int) {
                                        const_iterator tmp(loc);
                                        --loc;
                                        return tmp;
                                }
                };
       list():msize(0),capacity(10),data(new T[capacity]) {}
                list(const list &al):msize(al.msize),capacity(al.msize),
                                data(new T[capacity]) {
                        for(unsigned int i=0; i<msize; ++i) data[i]=al.data[i];
                }
                list &operator=(const list &al) {
                        T* tmp = new T[al.msize];
                        for(unsigned int i=0; i<al.msize; ++i) tmp[i]=al.data[i];
                        msize = al.msize;
                        capacity = msize;
                        data = tmp;
                }
                ~list() { delete[] data; }
                void push_back(const T &t);           // add to the end.
                void pop_back();                      // remove last element.
                int size() const;
                void clear();
                void insert(const T &t,int index);    // insert this element before the given index.
                const T &operator[](int index) const; // get the element at index.
                T &operator[](int index);             // get the element at index.
                void remove(int index);

   	iterator begin();
                const_iterator begin() const;
                iterator end();
                const_iterator end() const;
                const_iterator cbegin() const;
                const_iterator cend() const;
};

template<typename T>
void list<T>::push_back(const T &t) {
        if(msize>=capacity) {
                T *tmp = new T[capacity*2];
                for(unsigned int i = 0; i<msize; ++i) tmp[i] = data[i];
                data = tmp;
                capacity *= 2;
        }
        data[msize] = t;
        ++msize;
}

template<typename T>
void list<T>::pop_back() {
        --msize;
}

template<typename T>
int list<T>::size() const {
        return msize;
}

template<typename T>
void list<T>::clear() {
        msize = 0;
}

template<typename T>
void list<T>::insert(const T &t,int index) {
        if(msize>=capacity) {
                T *tmp = new T[capacity*2];
                for(unsigned int i = 0; i<msize; ++i) tmp[i] = data[i];
                data = tmp;
                capacity *= 2;
        }
        for(unsigned int i = msize+1; i>index; --i) {
                data[i] = data[i-1];
        }
        data[index] = t;
        ++msize;
}

template<typename T>
const T &list<T>::operator[](int index) const {
        return data[index];
}

template<typename T>
T &list<T>::operator[](int index) {
        return data[index];
}

template<typename T>
void list<T>::remove(int index) {
        for(unsigned int i = index; i<msize-1; ++i) {
                data[i] = data[i+1];
        }
        --msize;
}

template<typename T>
typename list<T>::iterator list<T>::begin() {
        return iterator(data);
}

template<typename T>
typename list<T>::const_iterator list<T>::begin() const {
        return const_iterator(data);
}

template<typename T>
typename list<T>::iterator list<T>::end() {
        return iterator(data+msize);
}

template<typename T>
typename list<T>::const_iterator list<T>::end() const {
        return const_iterator(data+msize);
}

template<typename T>
typename list<T>::const_iterator list<T>::cbegin() const {
        return const_iterator(data);
}

template<typename T>
typename list<T>::const_iterator list<T>::cend() const {
        return const_iterator(data+msize);
}

#endif

