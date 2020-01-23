#include <utility>
#include <algorithm>
#include <iostream>

template<typename K,typename V>
class AVLMap {
        struct Node {
                Node(Node *p):left(nullptr),right(nullptr),parent(p) {}
                std::pair<K,V> data;
                Node *left;
                Node *right;
                Node *parent;
                int height;
        };

        Node *root;
        unsigned int numElems;

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
                iterator(Node *node,bool isEnd):n(node),end(isEnd) {}

                bool operator==(const iterator &i) const { return end==i.end && n==i.n; }
                bool operator!=(const iterator &i) const { return !(*this==i); }
                std::pair<K,V> &operator*() { return n->data; }
                iterator &operator++() {
                        if(n==nullptr) return *this;
                        if(n->right==nullptr) {
                                Node *tmp = n;
                                Node *c = n;
                                n = n->parent;
                                while(n!=nullptr && c==n->right) {
                                        c = n;
                                        n = n->parent;
                                }
                                if(n==nullptr) {
                                        n = tmp;
                                        end = true;
                                }
                        } else {
                                n = n->right;
                                while(n->left!=nullptr) n = n->left;
                        }
                        return *this;
                }
                iterator &operator--() {
                        if(end) end = !end;
                        else {
                                if(n->left==nullptr) {
                                        Node *tmp = n;
                                        Node *c = n;
                                        n = n->parent;
                                        while(n!=nullptr && c==n->left) {
                                                c = n;
                                                n = n->parent;
                                        }
                                        if(n==nullptr) {
                                                n = tmp;
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
                const_iterator(Node *node):n(node),end(n==nullptr) {}
                const_iterator(Node *node,bool isEnd):n(node),end(isEnd) {}
                const_iterator(const iterator &iter):n(iter.n),end(iter.end) {}

                bool operator==(const const_iterator &i) const { return end==i.end && n==i.n; }
                bool operator!=(const const_iterator &i) const { return !(*this==i); }
                std::pair<K,V> &operator*() { return n->data; }
                const_iterator &operator++() {
                        if(n==nullptr) return *this;
                        if(n->right==nullptr) {
                                Node *tmp = n;
                                Node *c = n;
                                n = n->parent;
                                while(n!=nullptr && c==n->right) {
                                        c = n;
                                        n = n->parent;
                                }
                                if(n==nullptr) {
                                        n = tmp;
                                        end = true;
                                }
                        } else {
                                n = n->right;
                                while(n->left!=nullptr) n = n->left;
                        }
                        return *this;
                }
                const_iterator &operator--() {
                        if(end) end = !end;
                        else {
                                if(n->left==nullptr) {
                                        Node *tmp = n;
                                        Node *c = n;
                                        n = n->parent;
                                        while(n!=nullptr && c==n->left) {
                                                c = n;
                                                n = n->parent;
                                        }
                                        if(n==nullptr) {
                                                n = tmp;
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

        AVLMap():root(nullptr),numElems(0) {}
        AVLMap(const AVLMap<K,V> &that):numElems(that.numElems) {
                root = recurCopy(that.root,nullptr);
        }
        ~AVLMap() {
                deleteAll(root);
        }

        AVLMap &operator=(const AVLMap<K,V> &that) {
                if(&that == this) return;
                deleteAll(root);
                root = recurCopy(that.root,nullptr);
                numElems = that.numElems;
        }

        bool empty() const { return numElems == 0; }

        unsigned size() const { return numElems; }

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
                if(root==nullptr) return const_iterator(root);
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
                if(root==nullptr) return const_iterator(root);
                Node *n = root;
                while(n->right!=nullptr) n = n->right;
                return const_iterator(n,true);
        }

        const_iterator cbegin() const {
                if(root==nullptr) return const_iterator(root);
                Node *n = root;
                while(n->left!=nullptr) n = n->left;
                return const_iterator(n);
        }

        const_iterator cend() const {
                if(root==nullptr) return const_iterator(root);
                Node *n = root;
                while(n->right!=nullptr) n = n->right;
                return const_iterator(n,true);
        }

        void printTree() {
                printTreeRecur(root);
                std::cout << std::endl;
        }

private:
        void deleteAll(Node *n) {
                if(n!=nullptr) {
                        deleteAll(n->left);
                        deleteAll(n->right);
                        delete(n);
                }
        }
        Node *recurCopy(Node *n,Node *p) {
                if(n==nullptr) return nullptr;
                Node *n2 = new Node(p);
                n2->data = n->data;
                n2->height = n->height;
                n2->left = recurCopy(n->left,n2);
                n2->right = recurCopy(n->right,n2);
                return n2;
        }
        void printTreeRecur(Node *n) {
                if(n!=nullptr) {
                        std::cout << "(";
                        printTreeRecur(n->left);
                        std::cout << n->data.first << "-" << n->height << " ";
                        printTreeRecur(n->right);
                        std::cout << ")";
                }
        }

        void transplant(Node *u,Node *v) {
                if(u->parent==nullptr) {
                        root = v;
                } else if(u==u->parent->left) {
                        u->parent->left = v;
                } else u->parent->right = v;
                if(v!=nullptr) v->parent = u->parent;
        }
        void removeNode(Node *z) {
                if(z->left==nullptr) {
                        Node *zr = z->right;
                        transplant(z,z->right);
                        rebalanceUp(zr);
                } else if(z->right==nullptr) {
                        Node *zl = z->left;
                        transplant(z,z->left);
                        rebalanceUp(zl);
                } else {
                        Node *y = z->right;
                        while(y->left!=nullptr) y = y->left;
                        Node *lowest = (y->right==nullptr) ? ((y==z->right) ? y : y->parent) : y->right;
                        if(y->parent!=z) {
                                transplant(y,y->right);
                                y->right = z->right;
                                y->right->parent = y;
                        }
                        transplant(z,y);
                        y->left = z->left;
                        y->left->parent = y;
                        rebalanceUp(lowest);
                }
                delete z;
        }

        void rotateLeft(Node *x) {
                Node *y = x->right;
                x->right = y->left;
                if(y->left!=nullptr) {
                        y->left->parent = x;
                }
                y->parent = x->parent;
                if(x->parent == nullptr) {
                        root = y;
                } else if(x==x->parent->left) {
                        x->parent->left = y;
                } else x->parent->right = y;
                y->left = x;
                x->parent = y;
                setHeight(x);
                setHeight(y);
        }

        void rotateRight(Node *x) {
                Node *y = x->left;
                x->left = y->right;
                if(y->right!=nullptr) {
                        y->right->parent = x;
                }
                y->parent = x->parent;
                if(x->parent == nullptr) {
                        root = y;
                } else if(x==x->parent->right) {
                        x->parent->right = y;
                } else x->parent->left = y;
                y->right = x;
                x->parent = y;
                setHeight(x);
                setHeight(y);
        }

        int getHeight(Node *n) {
                return (n==nullptr) ? -1 : n->height;
        }

        void setHeight(Node *n) {
                n->height = std::max(getHeight(n->left),getHeight(n->right))+1;
        }

        void rebalanceUp(Node *n) {
                while(n!=nullptr) {
                        if(getHeight(n->left)-getHeight(n->right)>1) {
                                if(getHeight(n->left->right)>getHeight(n->left->left)) {
                                        rotateLeft(n->left);
                                }
                                rotateRight(n);
                        } else if(getHeight(n->right)-getHeight(n->left)>1) {
                                if(getHeight(n->right->left)>getHeight(n->right->right)) {
                                        rotateRight(n->right);
                                }
                                rotateLeft(n);
                        }
                        setHeight(n);
                        n = n->parent;
                }
        }
};

template <class K, class V>
bool AVLMap<K,V>::operator==(const AVLMap<K,V>& rhs) const {
        if(size()!=rhs.size()) return false;
        for(auto &p:rhs) {
                auto iter = find(p.first);
                if(iter==end() || p.second!=(*iter).second) return false;
        }
        return true;
}

template <class K, class V>
bool AVLMap<K,V>::operator!=(const AVLMap<K,V>& rhs) const {
        return !(*this==rhs);
}

template<typename K,typename V>
typename AVLMap<K,V>::iterator AVLMap<K,V>::find(const K& key) {
        Node *rover = root;
        while(rover!=nullptr) {
                if(rover->data.first==key) return iterator(rover);
                if(key<rover->data.first) rover = rover->left;
                else rover = rover->right;
        }
        return end();
}

template<typename K,typename V>
typename AVLMap<K,V>::const_iterator AVLMap<K,V>::find(const K& key) const {
        Node *rover = root;
        while(rover!=nullptr) {
                if(rover->data.first==key) return const_iterator(rover);
                if(key<rover->data.first) rover = rover->left;
                else rover = rover->right;
        }
        return end();
}

template<typename K,typename V>
unsigned int AVLMap<K,V>::count(const key_type& key) const {
        if(find(key)==end()) return 0;
        else return 1;
}

template<typename K,typename V>
std::pair<typename AVLMap<K,V>::iterator,bool> AVLMap<K,V>::insert(const value_type& val) {
        Node *rover = root;
        Node *prev = nullptr;
        while(rover!=nullptr) {
                if(rover->data.first==val.first) return make_pair(iterator(rover),false);
                prev = rover;
                if(val.first<rover->data.first) rover = rover->left;
                else rover = rover->right;
        }
        ++numElems;
        Node *n = new Node(prev);
        n->data = val;
        if(prev==nullptr) {
                root = n;
        } else {
                if(val.first<prev->data.first) prev->left = n;
                else prev->right = n;
        }
        rebalanceUp(n);
        return make_pair(iterator(n),true);
}

template<typename K,typename V>
typename AVLMap<K,V>::iterator AVLMap<K,V>::erase(const_iterator position) {
        const_iterator tmp = position;
        ++tmp;
        removeNode(position.n);
        numElems--;
        return iterator(tmp.n);
}

template<typename K,typename V>
unsigned int AVLMap<K,V>::erase(const K& key) {
        Node *rover = root;
        while(rover!=nullptr) {
                if(rover->data.first==key) {
                        removeNode(rover);
                        --numElems;
                        return 1;
                }
                if(key<rover->data.first) rover = rover->left;
                else rover = rover->right;
        }
        return 0;
}

template<typename K,typename V>
void AVLMap<K,V>::clear() {
        numElems = 0;
        deleteAll(root);
        root = nullptr;
}

template<typename K,typename V>
typename AVLMap<K,V>::mapped_type &AVLMap<K,V>::operator[](const K &key) {
        Node *rover = root;
        Node *prev = nullptr;
        while(rover!=nullptr) {
                if(rover->data.first==key) return rover->data.second;
                prev = rover;
                if(key<rover->data.first) rover = rover->left;
                else rover = rover->right;
        }
        ++numElems;
        Node *n = new Node(prev);
        n->data.first = key;
        if(prev==nullptr) {
                root = n;
        } else {
                if(key<prev->data.first) prev->left = n;
                else prev->right = n;
        }
        rebalanceUp(n);
        return n->data.second;
}
