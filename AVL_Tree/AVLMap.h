//Pledged by Shiyu

#include <utility>
#include <algorithm>
#include <iostream>

template<typename K,typename V>
class AVLMap {
	struct Node {
		Node(Node *n):left(nullptr), right(nullptr),parent(n) {}
		std::pair<K,V> data;
		Node *left;
		Node *right;
		Node *parent;
		int height;
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
	friend class AVLMap<K,V>;  
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

	AVLMap():root(nullptr),numOfElems(0) {}
	AVLMap(const AVLMap<K,V> &that):numOfElems(that.numOfElems) {
		root = copyTree(that.root,nullptr);
	} 
	~AVLMap() {
		deleteAll(root);
	}  
         
	AVLMap &operator=(const AVLMap<K,V> &that) {
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

    bool operator==(const AVLMap<K,V>& rhs) const;

    bool operator!=(const AVLMap<K,V>& rhs) const;

    iterator begin() {
	if(root==nullptr) return iterator(root); 
	Node *n = root;
	while(n->left!=nullptr) n = n->left;
	return iterator(n); 
    }

    const_iterator begin() const {
	if(root==nullptr) return iterator(root);
        Node *n = root;
        while(n->left!=nullptr) n = n->left;
        return const_iterator(n);	
    }

    iterator end() {
        if(root==nullptr) return iterator(root);
 	Node *n = root;
	while(n->right!=nullptr) n = n->right;
	return iterator(n,true);
    }

    const_iterator end() const {
        if(root==nullptr) return iterator(root);
	Node *n = root;
        while(n->right!=nullptr) n = n->right;
        return iterator(n,true);	
    }

    const_iterator cbegin() const {
        if(root==nullptr) return iterator(root);
        Node *n = root;
        while(n->left!=nullptr) n = n->left;
        return const_iterator(n);
    }

    const_iterator cend() const {
        if(root==nullptr) return iterator(root);
        Node *n = root;
        while(n->right!=nullptr) n = n->right;
        return const_iterator(n,true);
    }

private:

        void lrotate(Node *n) {
                Node *m = n->right;
                n->right = m->left;
                if(m->left!=nullptr) {
                        m->left->parent = n;
                }
                m->parent = n->parent;
                if(n->parent == nullptr) {
                        root = m;
                } else if(n==n->parent->left) {
                        n->parent->left = m;
                } else n->parent->right = m;
                m->left = n;
                n->parent = m;

                seth(n);
                seth(m);
        }

        void rrotate(Node *n) {
                Node *m = n->left;
                n->left = m->right;
                if(m->right!=nullptr) {
                        m->right->parent = n;
                }
                m->parent = n->parent;
                if(n->parent == nullptr) {
                        root = m;
                } else if(n==n->parent->right) {
                        n->parent->right = m;
                } else n->parent->left = m;
                m->right = n;
                n->parent = m;

                seth(n);
                seth(m);
        }

	int geth (Node *n) {
		if(n==nullptr) return -1;
		else return n->height;
	}

	void seth(Node *n) {
		n->height = std::max(geth(n->left),geth(n->right))+1;
	}

	
	void balanceTree(Node *n) {
		while(n!=nullptr) {
			if(geth(n->left)-geth(n->right)>1) {
				if(geth(n->left->right)>geth(n->left->left)){ 
					lrotate(n->left); 
				}
				rrotate(n);
			} else if(geth(n->right)-geth(n->left)>1) {
				if(geth(n->right->left)>geth(n->right->right)) {
					rrotate(n->right);
				}
				lrotate(n);
			}
			seth(n);
			n=n->parent;
		}
	}

	void transfer(Node *m, Node *n) {
		if(m->parent==nullptr){
			root=n;
		} else if(m==m->parent->left) {
			m->parent->left=n;
		} else {
			m->parent->right=n;
		}
		if(n!=nullptr) n->parent=m->parent;
	}
	
	Node *copyTree (Node *n, Node *p) {
		if(n==nullptr) return nullptr;
		Node *n2 = new Node(p);
		n2->data = n->data;
		n2->height=n->height;
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
		if(n->left==nullptr) {
			Node *r = n->right;
			transfer(n, n->right);
			balanceTree(r);
		} else if(n->right==nullptr) {
			Node *l = n->left;
			transfer(n,n->left);
			balanceTree(l);
		} else {
			Node *m = n->right;
			while(m->left!=nullptr) m=m->left;
			Node *tmp;
			if(m==n->right) {
				if(m->right==nullptr) tmp = m;
				else tmp = m->right;
			} else {
				if(m->right==nullptr) tmp = m->parent;
				else tmp = m->right;	
			}
			if(m->parent!=n) {
				transfer(m,m->right);
				m->right=n->right;
				m->right->parent=m;
			}
			transfer(n,m);
			m->left=n->left;
			m->left->parent=m;
			balanceTree(tmp);
		}
		delete n;
	}
};

template<typename K, typename V>
typename AVLMap<K,V>::iterator AVLMap<K,V>::find(const K& key) {
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
typename AVLMap<K,V>::const_iterator AVLMap<K,V>::find(const K& key) const {
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
unsigned int AVLMap<K,V>::count(const key_type& key) const {
	if(find(key) == end()) {
		return 0;
	} else {
		return 1;
	}
}

template<typename K, typename V>
std::pair<typename AVLMap<K,V>::iterator, bool> AVLMap<K,V>::insert(const value_type& val) {
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
	balanceTree(n);
	return make_pair(iterator(n),true);
}

template<typename K, typename V>
typename AVLMap<K,V>::iterator AVLMap<K,V>::erase(const_iterator position) {
	const_iterator tmp = position;
	++tmp;
	eraseNode(position.n);
	numOfElems = numOfElems -1;
	return iterator(tmp.n);
}

template<typename K, typename V>
unsigned int AVLMap<K,V>::erase(const K& key) {
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
void AVLMap<K,V>::clear(){
	deleteAll(root);
	numOfElems = 0;
	root = nullptr;
}

template<typename K, typename V>
typename AVLMap<K,V>::mapped_type &AVLMap<K,V>::operator[] (const K &key) {
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
	balanceTree(n); 
	return n->data.second;
}

template<class K, class V>
bool AVLMap<K,V>::operator==(const AVLMap<K,V>& rhs) const {
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
bool AVLMap<K,V>::operator!=(const AVLMap<K,V>& rhs) const {
	return !(*this==rhs);
}
