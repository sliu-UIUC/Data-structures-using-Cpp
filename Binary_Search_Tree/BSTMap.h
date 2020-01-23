//Pledged by Shiyu

#include <utility>
#include <algorithm>
#include <iostream>

template<typename K,typename V>
class BSTMap {
	struct Node {
		Node(Node *n):left(nullptr), right(nullptr),parent(n) {}
		std::pair<K,V> data;
		Node *left;
		Node *right;
		Node *parent;
	};
	Node *root;
	int numOfElems;

public:
    typedef K key_type;
    typedef V mapped_type;
    typedef std::pair<K,V> value_type;

    class const_iterator;

    class iterator {
	Node *n;
	bool end;
 public:
        friend class const_iterator;
        iterator(Node *node):n(node),end(n==nullptr) {} 
	iterator(Node *node, bool isEnd):n(node), end(isEnd) {}
        bool operator==(const iterator &i) const {
		return end==i.end && n == i.n; 
	}
        bool operator!=(const iterator &i) const {
		return (end!= i.end) || (n!=i.n);
	}
	std::pair<K,V> &operator*() {
		return n->data;
	}
        iterator &operator++() {
		if(n==nullptr) return *this;
		if(n->right==nullptr){
			Node *tmp1 = n;
			Node *tmp2 = n;
			n = n->parent;
			while(n!=nullptr && tmp1==n->right){
				tmp1=n;
				n = n->parent;
			}
			if (n==nullptr) {
				n = tmp2;
				end = true;
			}
		} else {
			n = n->right;
			while(n->left!=nullptr) n = n->left;
		}
        	return *this;
        }

        iterator &operator--() {
		if(end) {	
			end = !end;	
		} else {
			if(n->left==nullptr) {
				Node *tmp1 = n;
				Node *tmp2 = n;
				n = n->parent;
				while(n!=nullptr && tmp1==n->left) {
					tmp1 = n;
					n = n->parent;
				}
				if(n==nullptr) {
					n = tmp2;
					end = true;
				}
			} else {
				n = n->left;
				while(n->right!=nullptr) n = n->right;
			}
		}
		return *this;
        } 
        iterator operator++(int) {
            iterator tmp(*this);
            ++(*this);
            return tmp;
        }
        iterator operator--(int) {
            iterator tmp(*this);
            --(*this);
            return tmp;
        }
    };

    class const_iterator {
		Node *n;
		bool end;
    public: 
	friend class BSTMap<K,V>;  
	const_iterator (Node *node):n(node),end(n==nullptr) {} 
        const_iterator (Node *node, bool isEnd):n(node), end(isEnd) {}
        const_iterator(const iterator &iter):n(iter.n),end(iter.end) {}
	bool operator==(const const_iterator &i) const {
		return end==i.end && n==i.n;
	} 
	bool operator!=(const const_iterator &i) const {
		return end!=i.end || n!=i.n;	
	}
	const std::pair<K,V> &operator*() {
		return n->data;
	}
	const_iterator &operator++(){
                if(n==nullptr) return *this;
                if(n->right==nullptr){
                        Node *tmp1 = n;
                        Node *tmp2 = n;
                        n = n->parent;
                        while(n!=nullptr && tmp1==n->right){
                                tmp1=n;
                                n = n->parent;
                        }
                        if (n==nullptr) {
                                n = tmp2;
                                end = true;
                        }
                } else {
                        n = n->right;
                        while(n->left!=nullptr) n = n->left;
                }	
	    return *this;
        }
        const_iterator &operator--() {
                if(end) {
                        end = !end;
                } else {
                        if(n->left==nullptr) {
                                Node *tmp1 = n;
                                Node *tmp2 = n;
                                n = n->parent;
                                while(n!=nullptr && tmp1==n->left) {
                                        tmp1 = n;
                                        n = n->parent;
                                }
                                if(n==nullptr) {
                                        n = tmp2;
                                        end = true;
                                }
                        } else {
                                n = n->left;
                                while(n->right!=nullptr) n = n->right;
                        }
                }
	    return *this;
	} 
        const_iterator operator++(int) {
            const_iterator tmp(*this);
            ++(*this);
            return tmp;
        }
        const_iterator operator--(int) {
            const_iterator tmp(*this);
            --(*this);
            return tmp;
        }
    };

	BSTMap():root(nullptr),numOfElems(0) {}
	BSTMap(const BSTMap<K,V> &that):numOfElems(that.numOfElems) {
		root = copyTree(that.root,nullptr);
	} 
	~BSTMap() {
		deleteAll(root);
	}  
         
	BSTMap &operator=(const BSTMap<K,V> &that) {
                if(&that == this) return this;
                deleteAll(root);
                root = copyTree(that.root,nullptr);
                numOfElems = that.numOfElems;
	} 

	bool empty() const {
		return numOfElems == 0;
	}

        unsigned size() const {
		return numOfElems;	
	}

    iterator find(const key_type& k);

    const_iterator find(const key_type& k) const;

    unsigned int count(const key_type& k) const;

    std::pair<iterator,bool> insert(const value_type& val);

    template <class InputIterator>
    void insert(InputIterator first, InputIterator last) {
        for(auto iter = first; iter!=last; ++iter) {
            insert(*iter);
        }
    }

    iterator erase(const_iterator position);

    unsigned int erase(const key_type& k);

    void clear();

    mapped_type &operator[](const K &key);

    bool operator==(const BSTMap<K,V>& rhs) const;

    bool operator!=(const BSTMap<K,V>& rhs) const;

    iterator begin() { 
	Node *n = root;
	while(n->left!=nullptr) n = n->left;
	return iterator(n); 
    }

    const_iterator begin() const {
        Node *n = root;
        while(n->left!=nullptr) n = n->left;
        return const_iterator(n);	
    }

    iterator end() {
 	Node *n = root;
	while(n->right!=nullptr) n = n->right;
	return iterator(n,true);
    }

    const_iterator end() const {
	Node *n = root;
        while(n->right!=nullptr) n = n->right;
        return iterator(n,true);	
    }

    const_iterator cbegin() const {
        Node *n = root;
        while(n->left!=nullptr) n = n->left;
        return const_iterator(n);
    }

    const_iterator cend() const {
        Node *n = root;
        while(n->right!=nullptr) n = n->right;
        return const_iterator(n,true);
    }

private:
	Node *copyTree (Node *n, Node *p) {
		if(n==nullptr) return nullptr;
		Node *n2 = new Node(p);
		n2->data = n->data;
		n2->left = copyTree(n->left,n2);
		n2->right = copyTree(n->right,n2);
		return n2;
	}

        void deleteAll(Node *n) {
                if(n!=nullptr) {
                        deleteAll(n->left);
                        deleteAll(n->right);
                        delete(n);
                }
        }

	void eraseNode(Node *n) {
		if (n->left==nullptr && n->right==nullptr) {
			if(n==root) {root=nullptr;} 
			else if (n==n->parent->left) {n->parent->left=nullptr;}
			else {n->parent->right=nullptr;}
			delete n;
		} else if(n->left==nullptr) {
			if(n==root) {root= n->right;}
			else if (n==n->parent->left) {
				n->parent->left = n->right;
				n->right->parent = n->parent;
			} else {
				n->parent->right = n->right;
				n->right->parent = n->parent;
			}
			delete n;
		} else if(n->right == nullptr) {
			if(n==root) {root=n->left;} 
			else if (n==n->parent->left) {
				n->parent->left = n->left;
				n->left->parent = n->parent;
			} else {
				n->parent->right = n->left;
				n->left->parent = n->parent;
			} 
			delete n;
		} else {
			if(n->left->right==nullptr) {
				Node *tmp = n->left;
				n->data = n->left->data;
				n->left = n->left->left;
				if(n->left!=nullptr) {
					n->left->parent = n;
				}
				delete tmp;
			} else {
				Node *tmp = n->left->right;
				while(tmp->right!=nullptr) {
					tmp=tmp->right;
				} 
				tmp->parent->right = tmp->left;
				if(tmp->left!=nullptr) {
					tmp->left->parent = tmp->parent;
				}
				n->data = tmp->data;
				delete tmp;
			}
		}
	}
};

template<typename K, typename V>
typename BSTMap<K,V>::iterator BSTMap<K,V>::find(const K& key) {
	Node *mover = root;
	while(mover!=nullptr) {
		if(mover->data.first==key) return iterator(mover);
		if(key < (mover->data.first) ) {
			mover = mover -> left;
		} else {
			mover = mover -> right;
		}
	}
	return end();
}

template<typename K, typename V>
typename BSTMap<K,V>::const_iterator BSTMap<K,V>::find(const K& key) const {
	Node *mover = root;
        while(mover!=nullptr) {
                if(mover->data.first==key) return const_iterator(mover);
                if(key < (mover->data.first) ) {
                        mover = mover -> left;
                } else {
                        mover = mover -> right;
                }
        }
        return end();
}

template<typename K, typename V>
unsigned int BSTMap<K,V>::count(const key_type& key) const {
	if(find(key) == end()) {
		return 0;
	} else {
		return 1;
	}
}

template<typename K, typename V>
std::pair<typename BSTMap<K,V>::iterator, bool> BSTMap<K,V>::insert(const value_type& val) {
	Node *mover = root;
	Node *tmp = nullptr;
	while(mover!=nullptr) {
		if(mover->data.first==val.first) {
			return make_pair(iterator(mover),false);
		}
		tmp = mover;
		if(val.first < (mover->data.first)) {
			mover = mover->left;
		} else {
			mover = mover->right;
		}
	}
	numOfElems = numOfElems + 1;
	Node *n = new Node(tmp);
	n->data = val;
	if(tmp==nullptr) {
		root = n;
	} else {
		if(val.first < (tmp->data.first)){
			tmp->left = n;
		} else {
			tmp->right = n;
		}
	}
	return make_pair(iterator(n),true);
}

template<typename K, typename V>
typename BSTMap<K,V>::iterator BSTMap<K,V>::erase(const_iterator position) {
	const_iterator tmp = position;
	++tmp;
	eraseNode(position.n);
	numOfElems = numOfElems -1;
	return iterator(tmp.n);
}

template<typename K, typename V>
unsigned int BSTMap<K,V>::erase(const K& key) {
	Node *mover = root;
	while(mover!=nullptr) {
		if(mover->data.first==key) {
			eraseNode(mover);
			numOfElems = numOfElems-1;
			return 1;
		} 
		if (key < (mover->data.first)) {
			mover = mover->left;
		} else {
			mover = mover->right;
		}
	}
	return 0;
}

template<typename K, typename V>
void BSTMap<K,V>::clear(){
	deleteAll(root);
	numOfElems = 0;
	root = nullptr;
}

template<typename K, typename V>
typename BSTMap<K,V>::mapped_type &BSTMap<K,V>::operator[] (const K &key) {
	Node *mover = root;
	Node *tmp = nullptr;
	while(mover!=nullptr) {
		if(mover->data.first==key){
			return mover -> data.second;
		}
		tmp = mover;
		if(key < (mover->data.first)) {
			mover = mover->left;
		} else {
			mover = mover->right;
		}
	}
	numOfElems = numOfElems + 1;
	Node *n = new Node(tmp);
	n->data.first = key;
	if(tmp==nullptr) {
		root = n;
	} else {
		if(key < (tmp->data.first)) {
			tmp->left = n;
		} else {
			tmp->right = n;
		}
	} 
	return n->data.second;
}

template<class K, class V>
bool BSTMap<K,V>::operator==(const BSTMap<K,V>& rhs) const {
	if(size()!=rhs.size()) {
		return false;
	}
	for(auto &p:rhs) {
		auto iter = find(p.first);
		if(iter==end() || p.second!=(*iter).second) {
			return false;
		}
	}
	return true;
}  

template<class K,class V>
bool BSTMap<K,V>::operator!=(const BSTMap<K,V>& rhs) const {
	return !(*this==rhs);
}
