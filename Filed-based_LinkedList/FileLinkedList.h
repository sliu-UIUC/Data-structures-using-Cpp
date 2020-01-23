#include<string>
#include<cstdio>
#include<iostream>

template<typename T>
class FileLinkedList {
        FileLinkedList(const FileLinkedList<T> &that) = delete;
        FileLinkedList<T> operator=(const FileLinkedList<T> &that) = delete;

	FILE *file;
	int numOfElems;
	int freelist;

	void writeElem (int idx, const T &elem, int prev, int next) const {
		fseek(file, 2*sizeof(int)+idx*(sizeof(T)+2*sizeof(int)), SEEK_SET);
		fwrite(&next, sizeof(int), 1, file); 
		fwrite(&prev, sizeof(int), 1, file);
		fwrite(&elem, sizeof(T), 1, file);
	}
	void writePrev (int idx, int prev)  const {
		fseek(file, 3*sizeof(int)+idx*(sizeof(T)+2*sizeof(int)),SEEK_SET);
		fwrite(&prev, sizeof(int),1,file);
	}
	void writeNext (int idx, int next) const {
		fseek(file, 2*sizeof(int)+idx*(sizeof(T)+2*sizeof(int)),SEEK_SET);
		fwrite(&next,sizeof(int),1,file);
	} 
	void writeValue (int idx, const T &elem) const {
		fseek(file, 4*sizeof(int)+idx*(sizeof(T)+2*sizeof(int)),SEEK_SET);
		fwrite(&elem,sizeof(int),1,file);
	}
	void getElem (int idx, T &elem) const {
		fseek(file, 4*sizeof(int)+idx*(sizeof(T)+2*sizeof(int)),SEEK_SET);
		int num = fread(&elem, sizeof(T),1,file);
	} 
	int getPrev (int idx) const {
		fseek(file, 3*sizeof(int)+idx*(sizeof(T)+2*sizeof(int)),SEEK_SET);
		int tmp;
		int num = fread(&tmp, sizeof(int),1,file);
		return tmp;
	}
	int getNext (int idx) const {
		fseek(file, 2*sizeof(int)+idx*(sizeof(T)+2*sizeof(int)),SEEK_SET);
                int tmp;
                int num = fread(&tmp, sizeof(int),1,file);
                return tmp;
	}
	void writeSZ() const {
		fseek(file,0,SEEK_SET);
		fwrite(&numOfElems, sizeof(int), 1, file);
		fwrite(&freelist, sizeof(int),1, file);
	}

    public:
        typedef T value_type;

        class const_iterator {
		int idx;
		FILE *file;
  	   public:
                const_iterator(int i,FILE *f):idx(i), file(f){}
                const_iterator(const const_iterator &i):idx(i.idx), file(i.file){}
                T operator*() {
			fseek(file, 4*sizeof(int)+idx*(sizeof(T)+2*sizeof(int)),SEEK_SET);
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
                const_iterator &operator=(const const_iterator &i) {
			idx = i.idx;
			file = i.file;
		}
                const_iterator &operator++() {
			fseek(file, 2*sizeof(int)+idx*(sizeof(T)+2*sizeof(int)), SEEK_SET);
			int num = fread(&idx, sizeof(int), 1, file);
			return *this;
		}
                const_iterator &operator--() {
			fseek(file, 3*sizeof(int)+idx*(sizeof(T)+2*sizeof(int)), SEEK_SET);
                        int num = fread(&idx, sizeof(int), 1, file);
			return *this;
		}
                const_iterator operator++(int) {
			const_iterator tmp (*this);
                        fseek(file, 2*sizeof(int)+idx*(sizeof(T)+2*sizeof(int)), SEEK_SET);
                        int num = fread(&idx, sizeof(int), 1, file);
			return tmp;
		}
                const_iterator operator--(int) {
			const_iterator tmp (*this);
                        fseek(file, 3*sizeof(int)+idx*(sizeof(T)+2*sizeof(int)), SEEK_SET);
                        int num = fread(&idx, sizeof(int), 1, file);
			return tmp;
		}

                friend class FileLinkedList;
        };

	FileLinkedList(const std::string &fname) {
		file = fopen(fname.c_str(), "r+");
                if(file==nullptr) file = fopen(fname.c_str(),"w+");
		fseek(file,0, SEEK_END);
		if(ftell(file)>0) {
                        fseek(file,0,SEEK_SET);
                        int num = fread(&numOfElems,sizeof(int),1,file);
			num = fread(&freelist, sizeof(int),1,file);
                } else {
                        numOfElems = 1;
			freelist = -1;
                        fwrite(&numOfElems,sizeof(int),1,file);
			fwrite(&freelist, sizeof(int), 1, file);
			T sentinel;
			writeElem (0,sentinel,0,0);
                }
	}
	
	template<typename I> 
	FileLinkedList(I begin,I end,const std::string &fname) {
		file = fopen(fname.c_str(), "w+");
		freelist = -1;
		numOfElems = 1;
		T tmp;
		writeElem(0,tmp,0,0);
		while (begin!= end) {
			push_back(*begin);
			++begin;
		}
		writeSZ();
	} 

 	~FileLinkedList(); 
        void push_back(const T &t);
        void pop_back();
        int size() const;
        void clear();
        const_iterator insert(const_iterator position, const T &t);
        T operator[](int index) const;
        const_iterator erase(const_iterator position);
        void set(const T &value,int index);
        void set(const T &value,const_iterator position);

        const_iterator begin() {
		return const_iterator(getNext(0), file) ; 
	}
        const_iterator begin() const {
		return const_iterator(getNext(0), file);
	}
        const_iterator end() {
		return const_iterator(0, file);
	}
        const_iterator end() const {
		return const_iterator(0,file);
	}
        const_iterator cbegin() const {
		return const_iterator(getNext(0), file);
	}
        const_iterator cend() const {
		return const_iterator(0,file); 
	}
};
template<typename T>
FileLinkedList<T>::~FileLinkedList(){
	fclose(file);
} 
template<typename T>
void FileLinkedList<T>::push_back(const T &t) {
	int tmp;
	if (freelist <0) {
		tmp = numOfElems;
	} else {
		tmp = freelist;
		freelist = getNext(freelist);
	}
	int end = getPrev(0);
	writePrev(0, tmp);
	writeElem(tmp,t,end,0); 
	writeNext(end, tmp); 
	numOfElems = numOfElems+1;
	writeSZ();
}

template<typename T>
void FileLinkedList<T>::pop_back() {
	int end = getPrev(0);
	int preEnd = getPrev(end);	
	writeNext(end,freelist);
	freelist = end;
	writeNext(preEnd, 0);
	writePrev(0, preEnd);
	numOfElems = numOfElems -1;
	writeSZ();
}

template<typename T>
int FileLinkedList<T>::size() const {
	return numOfElems -1;
}

template<typename T>
void FileLinkedList<T>::clear() {
	int i;
	for (i = 1; i < numOfElems -1; ++i) {
		writeNext(i, i+1);
	}
	writeNext(numOfElems-1, -1);
	writeNext(0,0);
	writePrev(0,0);
	if (numOfElems > 1) {
		freelist = 1;
	}
	numOfElems = 1;
	writeSZ();
} 

template<typename T>
T FileLinkedList<T>::operator[] (int index) const {
	int mover = getNext(0);
	int i;
	for (i =0; i<index;++i) {
		mover = getNext(mover);
	}
	T tmp;
	getElem(mover,tmp);
	return tmp;
}

template<typename T>
void FileLinkedList<T>::set (const T &value, int index) {
	int mover = getNext(0);
	int i;
	for (i =0; i<index;++i){
		mover = getNext(mover);
	}
	writeValue(mover, value);
}

template<typename T>
void FileLinkedList<T>::set (const T &value, const_iterator position) {
        writeValue(position.idx, value);
}

template<typename T> 
typename FileLinkedList<T>::const_iterator FileLinkedList<T>::insert(const_iterator position, const T &t) {
	T tmp;
	int mover = position.idx;
	int prev = getPrev(mover);
	int num;
	if(freelist<0) {
		num = numOfElems;
	} else {
		num = freelist;
		freelist = getNext(num);
	}
	writeElem(num,t, prev, mover);
	writeNext(prev, num);
	writePrev(mover,num);
	numOfElems = numOfElems +1;
	writeSZ();
	return position;
}

template<typename T>
typename FileLinkedList<T>::const_iterator FileLinkedList<T>::erase(const_iterator position) {
	T tmp;
	int mover = position.idx;
	int prev = getPrev(mover);
	int next = getNext(mover);
	auto temp = ++position;
	writeNext(prev,next);
	writePrev(next,prev);
	writeNext(mover, freelist);
	freelist = mover;
	numOfElems = numOfElems -1;
	writeSZ();
	return temp;
}
