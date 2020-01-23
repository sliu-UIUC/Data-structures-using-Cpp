#include <cstdio>
#include <string>

template<typename T>
class FileLinkedList {
                FILE *file;
                int numElems;
                int firstFree;

                void writeElem(int index,const T &elem,int prev,int next) const;
                void readElem(int index,T &elem) const;
                int readNext(int index) const;
                int readPrev(int index) const;
                void writeNext(int index,int next) const;
                void writePrev(int index,int prev) const;
                void writeValue(int index,const T &elem) const;
                void writeSizeAndFF() const;

                FileLinkedList(const FileLinkedList<T> &that) {}
                FileLinkedList<T> operator=(const FileLinkedList<T> &that) {}
        public:
		typedef T value_type;
		
		class const_iterator {
		 	int index;
			FILE *file;
 const_iterator(int i,FILE *f):index(i),file(f) {}
                                const_iterator(const const_iterator &i):index(i.index),file(i.file) {}
                                T operator*() {
                                        std::fseek(file,4*sizeof(int)+index*(sizeof(T)+2*sizeof(int)),SEEK_SET);
                                        T ret;
                                        int num = fread(&ret,sizeof(T),1,file);
                                        return ret;
                                }
                                bool operator==(const const_iterator &i) const { return index==i.index && file==i.file; }
                                bool operator!=(const const_iterator &i) const { return !(*this==i); }
                                const_iterator &operator=(const const_iterator &i) { index = i.index; file = i.file; }
                                const_iterator &operator++() {
                                        std::fseek(file,2*sizeof(int)+index*(sizeof(T)+2*sizeof(int)),SEEK_SET);
                                        int num = std::fread(&index,sizeof(int),1,file);
                                        return *this;
                                }
                                const_iterator &operator--() {
                                        std::fseek(file,3*sizeof(int)+index*(sizeof(T)+2*sizeof(int)),SEEK_SET);
                                        int num = std::fread(&index,sizeof(int),1,file);
                                        return *this;
                                }
 			 const_iterator operator++(int) {
                                        const_iterator tmp(*this);
                                        std::fseek(file,2*sizeof(int)+index*(sizeof(T)+2*sizeof(int)),SEEK_SET);
                                        int num = std::fread(&index,sizeof(int),1,file);
                                        return tmp;
                                }
                                const_iterator operator--(int) {
                                        const_iterator tmp(*this);
                                        std::fseek(file,3*sizeof(int)+index*(sizeof(T)+2*sizeof(int)),SEEK_SET);
                                        int num = std::fread(&index,sizeof(int),1,file);
                                        return tmp;
                                }
                };
	FileLinkedList(const std::string &fname);

                template<typename I>
                FileLinkedList(I begin,I end,const std::string &fname) {
                        file = std::fopen(fname.c_str(),"w+");
                        firstFree = -1;
                        numElems = 1;
                        T tmp;
                        writeElem(0,tmp,0,0);
                        while(begin!=end) {
                                push_back(*begin);
                                ++begin;
                        }
                        writeSizeAndFF();
                }
                ~FileLinkedList() {
                        fclose(file);
                }
                void push_back(const T &t);
                void pop_back();
                int size() const;
                void clear();
                const_iterator insert(const T &t,const_iterator position);
                T operator[](int index) const;
                const_iterator erase(const_iterator position);
                void set(const T &value,int index);
		void set(const T &value, const_iterator position);
              const_iterator begin() { return const_iterator(readNext(0),file); }
                const_iterator begin() const { return const_iterator(readNext(0),file); }
                const_iterator end() { return const_iterator(0,file); }
                const_iterator end() const { return const_iterator(0,file); }
                const_iterator cbegin() const { return const_iterator(readNext(0),file); }
                const_iterator cend() const { return const_iterator(0,file); }
};


template<typename T>
FileLinkedList<T>::FileLinkedList(const std::string &fname) {
        file = std::fopen(fname.c_str(),"r+");
        if(file==nullptr) file = std::fopen(fname.c_str(),"w+");
        std::fseek(file,0,SEEK_END);
        if(std::ftell(file)>0) {
                std::fseek(file,0,SEEK_SET);
                int num = std::fread(&numElems,sizeof(int),1,file);
                num = std::fread(&firstFree,sizeof(int),1,file);
        } else {
                numElems = 1;
                firstFree = -1;
                std::fwrite(&numElems,sizeof(int),1,file);
                std::fwrite(&firstFree,sizeof(int),1,file);
                T sent;
                writeElem(0,sent,0,0);
        }
}

template<typename T>
void FileLinkedList<T>::writeElem(int index,const T &elem,int prev,int next) const {
        std::fseek(file,2*sizeof(int)+index*(sizeof(T)+2*sizeof(int)),SEEK_SET);
        std::fwrite(&next,sizeof(int),1,file);
        std::fwrite(&prev,sizeof(int),1,file);
        std::fwrite(&elem,sizeof(T),1,file);
}

template<typename T>
void FileLinkedList<T>::readElem(int index,T &elem) const {
        std::fseek(file,4*sizeof(int)+index*(sizeof(T)+2*sizeof(int)),SEEK_SET);
        int num = std::fread(&elem,sizeof(T),1,file);
}

template<typename T>
int FileLinkedList<T>::readNext(int index) const {
        std::fseek(file,2*sizeof(int)+index*(sizeof(T)+2*sizeof(int)),SEEK_SET);
        int ret;
        int num = std::fread(&ret,sizeof(int),1,file);
        return ret;
}

template<typename T>
int FileLinkedList<T>::readPrev(int index) const {
        std::fseek(file,3*sizeof(int)+index*(sizeof(T)+2*sizeof(int)),SEEK_SET);
        int ret;
        int num = std::fread(&ret,sizeof(int),1,file);
        return ret;
}
template<typename T>
void FileLinkedList<T>::writeNext(int index,int next) const {
        std::fseek(file,2*sizeof(int)+index*(sizeof(T)+2*sizeof(int)),SEEK_SET);
        std::fwrite(&next,sizeof(int),1,file);
}

template<typename T>
void FileLinkedList<T>::writePrev(int index,int prev) const {
        std::fseek(file,3*sizeof(int)+index*(sizeof(T)+2*sizeof(int)),SEEK_SET);
        std::fwrite(&prev,sizeof(int),1,file);
}

template<typename T>
void FileLinkedList<T>::writeValue(int index,const T &elem) const {
        std::fseek(file,4*sizeof(int)+index*(sizeof(T)+2*sizeof(int)),SEEK_SET);
        std::fwrite(&elem,sizeof(T),1,file);
}

template<typename T>
void FileLinkedList<T>::push_back(const T &t) {
        int n;
        if(firstFree<0) {
                n = numElems;
        } else {
                n = firstFree;
                firstFree = readNext(firstFree);
        }
        int tail = readPrev(0);
        writeElem(n,t,tail,0);
        writePrev(0,n);
        writeNext(tail,n);
        ++numElems;
        writeSizeAndFF();
}

template<typename T>
void FileLinkedList<T>::pop_back() {
        int tail = readPrev(0);
        int tailPrev = readPrev(tail);
        writeNext(tail,firstFree);
        firstFree = tail;
        writeNext(tailPrev,0);
        writePrev(0,tailPrev);
        --numElems;
        writeSizeAndFF();
}
template<typename T>
int FileLinkedList<T>::size() const {
        return numElems-1;
}

template<typename T>
void FileLinkedList<T>::clear() {
        for(int i = 1; i<numElems-1; ++i) {
                writeNext(i,i+1);
        }
        writeNext(numElems-1,-1);
        writeNext(0,0);
        writePrev(0,0);
        if(numElems>1) firstFree = 1;
        numElems = 1;
        writeSizeAndFF();
}
template<typename T>
typename FileLinkedList<T>::const_iterator FileLinkedList::insert(const T &t,const_iterator position) {
        T tmp;
        int rover = readNext(0);
        int prev = 0;
        for(int i = 0; i<position.index; ++i) {
                prev = rover;
                rover = readNext(rover);
        }
        int n;
        if(firstFree<0) {
                n = numElems;
        } else {
                n = firstFree;
                firstFree = readNext(n);
        }
        writeElem(n,t,prev,rover);
        writeNext(prev,n);
        writePrev(rover,n);
        ++numElems;
        writeSizeAndFF();
	return position;
}

template<typename T>
T FileLinkedList<T>::operator[](int index) const {
        int rover = readNext(0);
        for(int i = 0; i<index; ++i) {
                rover = readNext(rover);
        }
        T ret;
        readElem(rover,ret);
        return ret;
}
template<typename T>
typename FileLinkedList<T>::const_iterator FileLinkedList<T>::remove(const_iterator position) {
        T tmp;
        int rover = readNext(0);
        int prev = 0;
        for(int i = 0; i<position.index; ++i) {
                prev = rover;
                rover = readNext(rover);
        }
        int next = readNext(rover);
        writeNext(prev,next);
        writePrev(next,prev);
        writeNext(rover,firstFree);
        firstFree = rover;
        --numElems;
        writeSizeAndFF();
	return position;
}

template<typename T>
void FileLinkedList<T>::set(const T &value,int index) {
        int rover = readNext(0);
        for(int i = 0; i<index; ++i) {
                rover = readNext(rover);
        }
        writeValue(rover,value);
}

template<typename T>
void FileLinkedList<T>::set(const T &value,const_iterator position) {
        int rover = readNext(0);
        for(int i = 0; i<position.index; ++i) {
                rover = readNext(rover);
        }
        writeValue(rover,value);
}

