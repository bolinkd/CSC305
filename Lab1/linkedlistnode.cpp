#include "linkedlistnode.h"

template<class T>
LinkedListNode<T>::LinkedListNode(){

}

template<class T>
LinkedListNode<T>::LinkedListNode(T const& newData){
    this->setData(newData);
}

template<class T>
T LinkedListNode<T>::getData(){
    return this->data_;
}

template<class T>
void LinkedListNode<T>::setData(T& newData){
    this->data_ = newData;
}
