#ifndef BTREE_H_INCLUDED
#define BTREE_H_INCLUDED

#include <exception>
#include <string>
#include <iostream>

///definicion
template <class T>
class BTree{
private:
    class Node{
    private:
        T* dataPtr;
        Node* left;
        Node* right;
    public:
        class Exception : public std::exception{
        private:
            std::string msg;
        public:
            explicit Exception(const char* message) : msg(message) {}
            explicit Exception(const std::string& message) : msg(message) {}
            virtual ~Exception() throw() {}

            virtual const char* what() const throw() {
                return msg.c_str();
            }
        };

    Node();
    Node(const T&);

    ~Node();

    T* getDataPtr() const;
    T getData() const;
    Node*& getLeft();
    Node*& getRight();

    void setDataPtr(T*);
    void setData(const T&);
    void setLeft(Node*&);
    void setRight(Node*&);

    };

public:
    typedef Node* Position;

private:
    Position root;

    void copyAll(const BTree<T>&);

    void insertData(Position&, const T&);

    Position& findData(Position&, const T&);

    Position& getLowest(Position&);
    Position& getHighest(Position&);

    void parsePreOrder(Position&);
    void parseInOrder(Position&);
    void parsePostOrder(Position&);

    public:
        class Exception : public std::exception{
        private:
            std::string msg;
        public:
            explicit Exception(const char* message) : msg(message){}
            explicit Exception(const std::string& message) : msg(message) {}
            virtual ~Exception() throw() {}

            virtual const char* what() const throw() {
                return msg.c_str();
            }
        };

    BTree();
    BTree(const BTree&);

    bool isEmpty() const;

    void insertData(const T&);

    void deleteData(Position&);

    T retrieve(Position&) const;

    int getHeight(Position&);

    Position& findData(const T&);

    Position& getLowest();
    Position& getHighest();

    bool isLeaf(Position&) const;

    int getHeight();

    void parsePreOrder();
    void parseInOrder();
    void parsePostOrder();

    void deleteAll();

    BTree& operator = (const BTree&);

};

template <class T>
BTree<T>::Node::Node() : dataPtr(nullptr), left(nullptr), right(nullptr) {}

template <class T>
BTree<T>::Node::Node(const T& e) : dataPtr(new T(e)), left(nullptr), right(nullptr){
    if(dataPtr == nullptr){
        throw Exception("memoria insuficiente, creando nodo");
    }
}

template <class T>
BTree<T>::Node::~Node(){
    delete dataPtr;
}

template <class T>
T* BTree<T>::Node::getDataPtr() const{
    return dataPtr;
}

template <class T>
T BTree<T>::Node::getData() const{
    if(dataPtr == nullptr){
        throw Exception("dato inexistente, getData");
    }

    return *dataPtr;
}

template <class T>
typename BTree<T>::Position& BTree<T>::Node::getLeft(){
    return left;
}

template <class T>
typename BTree<T>::Position& BTree<T>::Node::getRight(){
    return right;
}

template <class T>
void BTree<T>::Node::setDataPtr(T* p){
    dataPtr = p;
}

template <class T>
void BTree<T>::Node::setData(const T& e){
    if(dataPtr == nullptr){
        if((dataPtr = new T(e)) == nullptr){
            throw Exception("Memproa no disponible, setData");
        }
    }
    else{
        *dataPtr = e;
    }
}

template <class T>
void BTree<T>::Node::setLeft(Position& p){
    left = p;
}

template <class T>
void BTree<T>::Node::setRight(Position& p){
    right = p;
}

///BTree
template <class T>
void BTree<T>::copyAll(const BTree<T>&){
///pendiente
}

template <class T>
BTree<T>::BTree() : root(nullptr) {}

template <class T>
BTree<T>::BTree(const BTree& t) : root(nullptr){
    copyAll(t);
}

template <class T>
bool BTree<T>::isEmpty() const{
    return root == nullptr;
}

template <class T>
void BTree<T>::insertData(const T& e){
    insertData(root, e);
}

template <class T>
void BTree<T>::insertData(Position& r, const T& e){
    if(r == nullptr){
        try{
            if((r = new Node(e)) == nullptr){
                throw Exception("memoria no disponible, insertData");
            }
        }
        catch(typename Node::Exception ex){
            throw Exception(ex.what());
        }
    }
    else{
        if(e< r->getData()){
            insertData(r->getLeft(), e);
        }
        else{
            insertData(r->getRight(), e);
        }
    }
}

template <class T>
void BTree<T>::deleteData(Position&){

}

template <class T>
T BTree<T>::retrieve(Position& r) const{
    return r->getData();
}

template <class T>
typename BTree<T>::Position& BTree<T>::findData(const T& e){
    return findData(root, e);
}

template <class T>
typename BTree<T>::Position& BTree<T>::findData(Position& r, const T& e){
    if(r==nullptr or r->getData() == e){
        return r;
    }

    if(e < r->getData()){
        return findData(r->getLeft(), e);
    }
    return findData(r->getRight(), e);
}

template <class T>
typename BTree<T>::Position& BTree<T>::getLowest(){
    return getLowest(root);
}

template <class T>
typename BTree<T>::Position& BTree<T>::getLowest(Position& r){
    if(r == nullptr or r->getLeft() == nullptr){
        return r;
    }

    return getLowest(r->getLeft());
}

template <class T>
typename BTree<T>::Position& BTree<T>::getHighest(){
    getHighest(root);
}

template <class T>
typename BTree<T>::Position& BTree<T>::getHighest(Position& r){
    if(r==nullptr or r->getRight() == nullptr){
        return r;
    }

    return getHighest(r->getRight());
}

template <class T>
bool BTree<T>::isLeaf(Position& r) const{
    return r != nullptr and r->getLeft() == r->getRight();
}

template <class T>
int BTree<T>::getHeight(){
    return getHeight(root);
}

template <class T>
int BTree<T>::getHeight(Position& r){
    if(r == nullptr){
        return 0;
    }

    int lH(getHeight(r->getLeft()));
    int rH(getHeight(r->getRight()));

    return(lH > rH ? lH : rH) + 1;
}

template <class T>
void BTree<T>::parsePreOrder(){
    parsePreOrder(root);
}

template <class T>
void BTree<T>::parsePreOrder(Position& r){
    if(r == nullptr){
        return;
    }

    std::cout << r->getData() << ",";
    parsePreOrder(r->getLeft());
    parsePreOrder(r->getRight());
}

template <class T>
void BTree<T>::parseInOrder(){
    parseInOrder(root);
}

template <class T>
void BTree<T>::parseInOrder(Position& r){
    if(r == nullptr){
        return;
    }

    parseInOrder(r->getLeft());
    std::cout << r->getData() << ",";
    parseInOrder(r->getRight());
}

template <class T>
void BTree<T>::parsePostOrder(){
    parsePostOrder(root);
}

template <class T>
void BTree<T>::parsePostOrder(Position& r){
    if(r == nullptr){
        return;
    }

    parsePostOrder(r->getLeft());
    parsePostOrder(r->getRight());
    std::cout << r->getData() << ",";
}

template <class T>
void BTree<T>::deleteAll(){
    ///pendiente
}

template <class T>
BTree<T>& BTree<T>::operator=(const BTree& t){
    deleteAll();

    copyAll(t);

    return *this;
}




#endif // BTREE_H_INCLUDED
