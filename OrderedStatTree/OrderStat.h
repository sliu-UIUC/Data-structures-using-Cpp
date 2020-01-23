#include <utility>
#include <algorithm>
#include <stdexcept>
#include <iostream>

template<typename T>
class OrderStat {
        struct Node {
                Node(Node *p):left(nullptr),right(nullptr),parent(p),height(0),size(1) {}
                T data;
                Node *left;
                Node *right;
                Node *parent;
                int height;
                int size;
        };

        Node *root;

public:
        typedef T value_type;

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
                T &operator*() { return n->data; }
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
                friend class OrderStat<T>;
                const_iterator(Node *node):n(node),end(n==nullptr) {}
                const_iterator(Node *node,bool isEnd):n(node),end(isEnd) {}
                const_iterator(const iterator &iter):n(iter.n),end(iter.end) {}

                bool operator==(const const_iterator &i) const { return end==i.end && n==i.n; }
                bool operator!=(const const_iterator &i) const { return !(*this==i); }
                const T &operator*() { return n->data; }
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
        OrderStat():root(nullptr) {}
        OrderStat(const OrderStat<T> &that) {
                root = copyTree(that.root,nullptr);
        }
        ~OrderStat() {
                deleteAll(root);
        }

        OrderStat &operator=(const OrderStat<T> &that) {
                if(&that == this) return this;
                deleteAll(root);
                root = recurCopy(that.root,nullptr);
        }

        bool empty() const { return root == nullptr; }

        unsigned size() const { return root ? root->size : 0; }

        value_type &front() {
                Node *rover = root;
                while(rover->left) rover = rover->left;
                return rover->data;
        }
        const value_type &front() const {
                Node *rover = root;
                while(rover->left) rover = rover->left;
                return rover->data;
        }
        value_type &back() {
                Node *rover = root;
                while(rover->right) rover = rover->right;
                return rover->data;
        }
        const value_type &back() const {
                Node *rover = root;
                while(rover->right) rover = rover->right;
                return rover->data;
        }
        iterator insert(const_iterator position,const value_type& val);

        template <class InputIterator>
    void insert(const_iterator position,InputIterator first, InputIterator last);

        iterator erase(const_iterator position);

        void clear();

        value_type &operator[](int index);

        void push_front(const value_type& val);
        void pop_front();
        void push_back(const value_type& val);
        void pop_back();

        bool operator==(const OrderStat<T>& rhs) const;

        bool operator!=(const OrderStat<T>& rhs) const;

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
private:
        void deleteAll(Node *n) {
                if(n!=nullptr) {
                        deleteAll(n->left);
                        deleteAll(n->right);
                        delete(n);
                }
        }

        Node *copyTree(Node *n,Node *p) {
                if(n==nullptr) return nullptr;
                Node *n2 = new Node(p);
                n2->data = n->data;
                n2->height = n->height;
                n2->size = n->size;
                n2->left = copyTree(n->left,n2);
                n2->right = copyTree(n->right,n2);
                return n2;
        }

        void transfer (Node *m,Node *n) {
                if(m->parent==nullptr) {
                        root = n;
                } else if(m==m->parent->left) {
                        m->parent->left = n;
                } else m->parent->right = n;
                if(n!=nullptr) n->parent = m->parent;
        }
        void eraseNode(Node *n) {
                if(n->left==nullptr) {
                        Node *r = n->right;
                        transfer(n,n->right);
                        if(r) {
                                balanceTree(r);
                        } else {
                                balanceTree(n->parent);
                        }
                } else if(n->right==nullptr) {
                        Node *l = n->left;
                        transfer(n,n->left);
                        balanceTree(l);
                } else {
                        Node *m = n->right;
                        while(m->left!=nullptr) m = m->left;
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
                                m->right = n->right;
                                m->right->parent = m;
                        }
                        transfer(n,m);
                        m->left = n->left;
                        m->left->parent = m;
                        balanceTree(tmp);
                }
                delete n;
        }

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

        int geth(Node *n) {
                if(n==nullptr) return -1;
                else return n->height;
        }

        void seth(Node *n) {
                n->height = std::max(geth(n->left),geth(n->right))+1;
                n->size = gets(n->left)+gets(n->right)+1;
        }

        int gets(Node *n) {
                if(n==nullptr) return 0;
                else return n->size;
        }

        void balanceTree(Node *n) {
                while(n!=nullptr) {
                        if(geth(n->left)-geth(n->right)>1) {
                                if(geth(n->left->right)>geth(n->left->left)) {
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
                        n = n->parent;
                }
        }
};

template <typename T>
bool OrderStat<T>::operator==(const OrderStat<T>& rhs) const {
        if(size()!=rhs.size()) return false;
        auto iter1 = begin();
        auto iter2 = rhs.begin();
        auto end1 = end();
        while(iter1!=end1) {
                if(*iter1 != *iter2) return false;
                ++iter1;
                ++iter2;
        }
        return true;
}

template <typename T>
bool OrderStat<T>::operator!=(const OrderStat<T>& rhs) const {
        return !(*this==rhs);
}

template<typename T>
typename OrderStat<T>::iterator OrderStat<T>::insert(const_iterator position,const value_type& val) {
        if(!root) {
                root = new Node(nullptr);
                root->data = val;
                seth(root);
                return iterator(root);
        } else if(position.end) {
                push_back(val);
                return --end();
        } else if(position.n->left) {
                Node *mover = position.n->left;
                while(mover && mover->right) mover = mover->right;
                Node *n = new Node(mover ? mover : position.n);
                n->data = val;
                mover->right = n;
                balanceTree(n);
                return iterator(n);
        } else {
                Node *n = new Node(position.n);
                position.n->left = n;
                n->data = val;
                balanceTree(n);
                return iterator(n);
        }
}

template<typename T>
typename OrderStat<T>::iterator OrderStat<T>::erase(const_iterator position) {
        const_iterator tmp = position;
        ++tmp;
        eraseNode(position.n);
        return iterator(tmp.n);
}

template<typename T>
void OrderStat<T>::clear() {
        deleteAll(root);
        root = nullptr;
}

template<typename T>
typename OrderStat<T>::value_type &OrderStat<T>::operator[](int index) {
        Node *mover = root;
        while(mover!=nullptr) {
                int lsize = gets(mover->left);
                if(index==lsize) return mover->data;
                if(index<lsize) mover = mover->left;
                else {
                        mover = mover->right;
                        index -= lsize+1;
                }
        }
        //throw std::out_of_range("Out of range on [].");
}

template<typename T>
void OrderStat<T>::push_front(const value_type& val) {
        if(!root) {
                root = new Node(nullptr);
                root->data = val;
                seth(root);
                return;
        }
        Node *mover = root;
        while(mover->left) mover = mover->left;
        Node *n = new Node(mover);
        n->data = val;
        mover->left = n;
        seth(n);
        balanceTree(n);
}

template<typename T>
void OrderStat<T>::pop_front() {
        Node *mover = root;
        while(mover->left) mover = mover->left;
        eraseNode(mover);
}

template<typename T>
void OrderStat<T>::push_back(const value_type& val) {
        if(!root) {
                root = new Node(nullptr);
                root->data = val;
                seth(root);
                return;
        }
        Node *mover = root;
        while(mover->right) mover = mover->right;
        Node *n = new Node(mover);
        n->data = val;
        mover->right = n;
        seth(n);
        balanceTree(n);
}

template<typename T>
void OrderStat<T>::pop_back() {
        Node *mover = root;
        while(mover->right) mover = mover->right;
        eraseNode(mover);
}
