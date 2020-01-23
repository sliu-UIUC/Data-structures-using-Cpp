#include <vector>
#include <algorithm>
#include <utility>

template<typename K,typename V,typename Hash>
class HashMap {
    Hash hashFunction;
    int numOfElems;
    std::vector<std::vector<std::pair<K,V>>>table;
 // Data to store the hash table and the number of elements.

public:
    typedef K key_type;
    typedef V mapped_type;
    typedef std::pair<K,V> value_type;

    class const_iterator;

    class iterator {
 // NOTE: These might be different depending on how you store your table.
        decltype(table.begin()) mainIter;
        decltype(table.begin()) mainEnd;
        decltype(table[0].begin()) subIter;
    public:
        friend class const_iterator;

        // NOTE: These might be different depending on how you store your table
	iterator(const decltype(mainIter) mi,const decltype(mainEnd) me):mainIter(mi),mainEnd(me) {
            if(mainIter!=mainEnd) subIter = mainIter->begin();
            while(mainIter!=mainEnd && subIter == mainIter->end()) {
                ++mainIter;
                if(mainIter!=mainEnd) subIter = mainIter->begin();
            }
        }
        // NOTE: These might be different depending on how you store your table.
        iterator(const decltype(mainIter) mi,
                const decltype(mainEnd) me,
                const decltype(subIter) si):
                mainIter(mi),mainEnd(me),subIter(si) {}

	bool operator==(const iterator &i) const { return mainIter==i.mainIter && (mainIter==mainEnd || subIter==i.subIter); }
        bool operator!=(const iterator &i) const { return !(*this==i); }
        std::pair<K,V> &operator*() { return *subIter; }
        iterator &operator++() {
            ++subIter;
            while(mainIter!=mainEnd && subIter==mainIter->end()) {
                ++mainIter;
                if(mainIter!=mainEnd) subIter = mainIter->begin();
            }
            return *this;
        }
        iterator operator++(int) {
            iterator tmp(*this);
            ++(*this);
            return tmp;
        }
    };

    class const_iterator {
        // NOTE: These might be different depending on how you store your table.
	decltype(table.cbegin()) mainIter;
        decltype(table.cbegin()) mainEnd;
        decltype(table[0].cbegin()) subIter;
    public:
        // NOTE: These might be different depending on how you store your table.     
	const_iterator(const decltype(table.cbegin()) mi,const decltype(table.cbegin()) me):mainIter(mi),mainEnd(me) {
            if(mainIter!=mainEnd) subIter = mainIter->begin();
            while(mainIter!=mainEnd && subIter == mainIter->end()) {
                ++mainIter;
                if(mainIter!=mainEnd) subIter = mainIter->begin();
            }
        }

	// NOTE: These might be different depending on how you store your table.

	const_iterator(const decltype(table.begin()) mi,
            const decltype(table.begin()) me,
            const decltype(table[0].begin()) si):
                mainIter(mi),mainEnd(me),subIter(si) {}
        // NOTE: These might be different depending on how you store your table.
	const_iterator(const iterator &i):mainIter(i.mainIter),mainEnd(i.mainEnd),subIter(i.subIter) {

        }

	bool operator==(const const_iterator &i) const { return mainIter==i.mainIter && (mainIter==mainEnd || subIter==i.subIter); }
        bool operator!=(const const_iterator &i) const { return !(*this==i); }
        const std::pair<K,V> &operator*() const { return *subIter; }
        const_iterator &operator++() {
            ++subIter;
            while(mainIter!=mainEnd && subIter==mainIter->end()) {
                ++mainIter;
                if(mainIter!=mainEnd) subIter = mainIter->begin();
            }
            return *this;
        }
        const_iterator operator++(int) {
            const_iterator tmp(*this);
            ++(*this);
            return tmp;
        }
    };

    HashMap(const Hash &hf):hashFunction(hf),table(11),numOfElems(0){}
    
    bool empty() const {
	return numOfElems == 0;
    }

    unsigned int size() const {
	return numOfElems;
    }

    iterator find(const key_type& k);

    const_iterator find(const key_type& k) const;

    int count(const key_type& k) const;

    std::pair<iterator,bool> insert(const value_type& val);

    template <class InputIterator>
    void insert(InputIterator first, InputIterator last) {
          for (auto iterator = first; iterator!=last; ++iterator) {
		K key = iterator->first;
		int bin = hashFunction(key) % table.size();
		auto iter = find_if(table[bin].begin(), table[bin].end(),[&key] (const std::pair<K,V> &p) { return p.first==key;});
		if(iter==table[bin].end()) {
				numOfElems = numOfElems +1;
				table[bin].push_back(*iterator);
		} 
	  }
    }

    iterator erase(const_iterator position);

    int erase(const key_type& k);

    void clear();

    mapped_type &operator[](const K &key);

    bool operator==(const HashMap<K,V,Hash>& rhs) const;

    bool operator!=(const HashMap<K,V,Hash>& rhs) const;

    iterator begin(){
	return iterator(table.begin(),table.end());
    }

    const_iterator begin() const {
	return const_iterator(table.begin(),table.end());
    }

    iterator end() {
	return iterator(table.end(),table.end());
    }

    const_iterator end() const {
	return const_iterator(table.end(),table.end());
    }

    const_iterator cbegin() const{
        return const_iterator(table.begin(),table.end());
    }

    const_iterator cend() const {
        return const_iterator(table.end(),table.end());
    }

private:
    void growTableAndRehash();
};


template <typename K, typename V, typename Hash>
typename HashMap<K,V,Hash>::iterator HashMap<K,V,Hash>::find(const K& key){
	int bin = hashFunction(key) % table.size();
	for(auto iter=table[bin].begin();iter!=table[bin].end();iter++){
		if(iter->first == key){
			return iterator(table.begin()+bin,table.end(), iter);
		}
	}
}

template <typename K, typename V, typename Hash>
typename HashMap<K,V,Hash>::const_iterator HashMap<K,V,Hash>::find(const K& key) const {
        int bin = hashFunction(key) % table.size();
	for(auto iter=table[bin].begin();iter!=table[bin].end();iter++){
        	if(iter->first==key){
			return iterator(table.begin()+bin,table.end(), iter);
		}
	}
}
template <typename K, typename V, typename Hash>
int HashMap<K,V,Hash>::count(const key_type& key) const {
	int bin = hashFunction(key) % table.size();
	int i = 0;
        for(auto iter=table[bin].begin();iter!=table[bin].end();iter++){
		if(iter == table[bin].end()) {
			i = i+0;
		} else {
			i=i+1;
		}
	}
	return i;
}

template <typename K, typename V, typename Hash>
std::pair<typename HashMap<K,V,Hash>::iterator,bool> HashMap<K,V,Hash>::insert (const value_type& val) {
	K key = val.first;
	int bin = hashFunction(key) % table.size();
	auto iter = find_if(table[bin].begin(), table[bin].end(),[&key] (const std::pair<K,V> &p) { return p.first==key;});	
	if (iter == table[bin].end()) {
		numOfElems = numOfElems + 1;
		if(numOfElems>(table.size()/2)) {
			growTableAndRehash();
			bin = hashFunction(key) % table.size();
		}
		table[bin].push_back(val);
		return make_pair(iterator(table.begin()+bin, table.end(),--(table[bin].end())),true);
	} else {
		return make_pair(iterator(table.begin()+bin,table.end(),iter),false);
	}
}

template <typename K, typename V, typename Hash>
typename HashMap<K,V,Hash>::iterator HashMap<K,V,Hash>::erase(const_iterator position) {
	if(position==cend()) return end();
	K key = (*position).first;
	int bin = hashFunction(key) % table.size();
	for(auto iter=table[bin].begin();iter!=table[bin].end();iter++){
		auto tmp = iterator(table.begin()+bin, table.end(),iter);
		table[bin].erase(iter);
		numOfElems = numOfElems -1;
		return (++tmp);
	}
}

template <typename K, typename V, typename Hash>
int HashMap<K,V,Hash>::erase(const K &key) {
	int bin = hashFunction(key) % table.size();
	for(auto iter=table[bin].begin();iter!=table[bin].end();++iter){
		if(iter->first == key){
			table[bin].erase(iter);
			numOfElems = numOfElems -1;
			return 1;
		}
	}
	return 0;
}

template <typename K, typename V, typename Hash>
void HashMap<K,V,Hash>::clear() {
	numOfElems = 0;
	for (auto &h:table) {
		h.clear();
	} 
	table.resize(11);
}

template <typename K, typename V, typename Hash>
typename HashMap<K,V,Hash>::mapped_type &HashMap<K,V,Hash>::operator[] (const K &key) {
        int bin = hashFunction(key) % table.size();
        auto iter = find_if(table[bin].begin(), table[bin].end(),[&key] (const std::pair<K,V> &p) { return p.first==key;});
	if(iter == table[bin].end()) {
		numOfElems = numOfElems + 1;
		if(numOfElems > (table.size()/2)) {
			growTableAndRehash();
			bin = hashFunction(key) % table.size();
		}
		table[bin].push_back(make_pair(key,V()));
		return table[bin].back().second;
	} else if(iter->first==key){
		return iter->second;
	}
}

template <typename K, typename V, typename Hash>
void HashMap<K,V,Hash>::growTableAndRehash(){
	std::vector<std::vector<std::pair<K,V>>> newTable(table.size()*2+1);
	for(auto &h:table) {
		for(auto &p:h){
			int bin = hashFunction(p.first) % newTable.size();
			newTable[bin].push_back(p);
		}
	}
	table =newTable;
}

template <class K, class V, class Hash>
bool HashMap<K,V,Hash>::operator==(const HashMap<K,V,Hash>& rhs) const {
	if(size()!=rhs.size()) return false;
	for(auto p: *this) {
		int bin = hashFunction(p.first) % table.size();
		for(auto iter = rhs.table[bin].begin();iter!=rhs.table[bin].end();iter++){
			if(p.first!=iter->first||p.second!=iter->second) {
				return false;
			}
		}
	}
	return true;
}

template <class K, class V, class Hash>
bool HashMap<K,V,Hash>::operator!=(const HashMap<K,V,Hash>& rhs) const {
	return !((*this)==rhs);
}
