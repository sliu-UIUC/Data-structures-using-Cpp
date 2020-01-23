#include<string>
#include<cstdio>
#include<iostream>
template<typename T>
class FileArrayList {
	FileArrayList (const FileArrayList<T> & that) = delete;
	FileArrayList<T> operator= (const FileArrayList<T> &that) = delete;
	
	FILE *f;
	int numOfElem;
	
	void writeElems (int idx, const T &elems) const {
		fseek(f,sizeof(int)+idx*sizeof(T), SEEK_SET);
		fwrite(&elems, sizeof(T), 1, f);
	}
	void readElems (T &elems, int idx) const {
		fseek(f, sizeof(int)+idx*sizeof(T), SEEK_SET);
		int num = fread (&elems,sizeof(T), 1, f);
	}
	void writeSZ() const {
		fseek(f, 0, SEEK_SET);
		fwrite(&numOfElem, sizeof(int),1, f);
	}

    public:
	typedef T value_type;
	
	class const_iterator {
		int idx;
		FILE *file;
	   public:
		const_iterator(int i, FILE *f):idx(i),file(f){}
		const_iterator(const const_iterator &i):idx(i.idx), file(i.file){}
		T operator*() {
			fseek(file, sizeof(int)+idx*sizeof(T),SEEK_SET);
			T tmp;
			int n = fread(&tmp, sizeof(T),1,file);
			return tmp;
		}
		bool operator==(const const_iterator &i) const {
			return idx == i.idx && file == i.file;
		}
		bool operator!=(const const_iterator &i) const {
			return idx != i.idx || file != i.file;
		}
		const_iterator &operator = (const const_iterator &i){
			idx = i.idx;
			file= i.file;
		}
		const_iterator &operator++(){
			idx = idx+1;
			return *this;
		}
		const_iterator &operator--(){
			idx = idx-1;
			return *this;
		}
		const_iterator operator++(int){
			const_iterator tmp (*this);
			idx = idx+1;
			return tmp;
		}
		const_iterator operator--(int){
		        const_iterator tmp (*this);
                        idx = idx+1;
                        return tmp;
		}
		
		friend class FileArrayList;
	};

	//General Methods 
	FileArrayList(const std::string &fname) {
		f = fopen(fname.c_str(), "r+");
		if(f==nullptr) f = fopen(fname.c_str(),"w+");
       		fseek(f,0,SEEK_END);
        	if(ftell(f)>0) {
                	fseek(f,0,SEEK_SET);
                	int num = fread(&numOfElem,sizeof(int),1,f);
        	} else {
                	numOfElem = 0;
                	fwrite(&numOfElem,sizeof(int),1,f);
        	}
	}
	
	template<typename I> //The type I will be an iterator.
	FileArrayList(I begin, I end, const std::string &fname) {
		f = fopen(fname.c_str(), "w+");
		numOfElem = 0;
		fseek(f,sizeof(int), SEEK_SET);
		while(begin != end){
			T tmp = *begin;
			fwrite(&tmp, sizeof(T),1,f);
			++begin;
			numOfElem = numOfElem +1;
		}
		fseek(f, 0,SEEK_SET);
		fwrite(&numOfElem, sizeof(int), 1, f);
	}

	~FileArrayList() {
		fclose(f);
	}
	void push_back(const T &t);
	void pop_back();
	int size() const;
	void clear();
	const_iterator insert(const_iterator position, const T &t);
	T operator[] (int index) const;
	const_iterator erase(const_iterator position);
	void set(const T &value, int index);

	const_iterator begin() {
		return const_iterator(0,f);
	}
	const_iterator begin() const{
		return const_iterator (0,f);
	}
	const_iterator end(){
		return const_iterator(numOfElem, f);
	}
	const_iterator end() const{
		return const_iterator(numOfElem, f);
	}
	const_iterator cbegin() const {
		return const_iterator (0,f);
	}
	const_iterator cend() const {
		return const_iterator(numOfElem, f);
	}	
};

template<typename T>
void FileArrayList<T>::push_back(const T &t) {
	writeElems(numOfElem, t);
	numOfElem = numOfElem + 1;
	writeSZ();
}

template<typename T>
void FileArrayList<T>::pop_back() {
	numOfElem = numOfElem -1;
	writeSZ();
}

template<typename T>
int FileArrayList<T>::size() const {
	return numOfElem;
}

template<typename T>
void FileArrayList<T>::clear() {
	numOfElem = 0;
	writeSZ();
}

template<typename T>
T FileArrayList<T>::operator[] (int index) const {
	T tmp; 
	readElems(tmp, index);
	return tmp;
}

template<typename T>
void FileArrayList<T>::set(const T &value, int index) {
	writeElems(index, value);
}

template<typename T>
typename FileArrayList<T>::const_iterator FileArrayList<T>::insert(const_iterator position, const T &t) {
	T tmp;
	int num = position.idx;
	for(int i = numOfElem; i > num; --i){
		readElems(tmp, i-1);
		writeElems(i, tmp);
	}	
	writeElems(num,t);
	numOfElem = numOfElem +1;
	writeSZ();	
	return position;
}

template<typename T>
typename FileArrayList<T>::const_iterator FileArrayList<T>::erase(const_iterator position) {
	T tmp;
	for(int i = position.idx; i<numOfElem-1; ++i) {
		readElems(tmp,i+1);
		writeElems(i, tmp);
	}	
	numOfElem = numOfElem - 1;
	writeSZ();
	return position;
}
