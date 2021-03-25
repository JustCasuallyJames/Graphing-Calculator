//
// Created by james on 4/9/2020.
//

#ifndef LINKED_LISTS_LINKED_LIST_H
#define LINKED_LISTS_LINKED_LIST_H

#include <iostream>
#include <cassert>
#include "node.h"

template<typename T>
class List {
public:
    class Iterator {
    public:
        friend class List;

        Iterator(node<T> *p = nullptr) : _ptr(p) {}     //constructor

        T &operator*() {//dereference operator
            assert(_ptr);
            return _ptr->_item;
        }
        const T &operator*() const {        //dereference oprator
            assert(_ptr);
            return _ptr->_item;
        }
        operator bool() const{
            return _ptr != nullptr;
        }
        T* operator ->(){
            assert(_ptr);
            return &_ptr->_item; //returns the reference of the item within the node
        }
        const T* operator ->()const{
            assert(_ptr);
            return &_ptr->_item; //returns the reference of the item within the node
        }
        friend Iterator operator++(Iterator &it, int unused) {//it++
            Iterator hold;
            hold = it;
            it = it._ptr->_next;
            return hold;
        }

        Iterator &operator++() {//++it
            _ptr = _ptr->_next;
            return *this;
        }
        friend bool operator!=(const Iterator &left, const Iterator &right) {//it != it
            return left._ptr != right._ptr;
        }
        friend bool operator==(const Iterator &left, const Iterator &right) {//it != it
            return left._ptr == right._ptr;
        }
    private:
        node<T> *_ptr;//pointer being encapsulated
    };

    List();

    ~List();

    List(const List<T> &copyThis);

    List &operator=(const List &RHS);

    Iterator InsertHead(T i);           //inset i at the head of list
    //insert i after iMarker
    Iterator InsertAfter(T i, Iterator iMarker);
    //insert i before iMarker
    Iterator InsertBefore(T i, List<T>::Iterator iMarker);

    Iterator InsertSorted(T i);         //insert i. Assume sorted list


    T Delete(List<T>::Iterator iMarker);         //delete node pointed to by iMarker

    void Print() const;                                 //print the list

    Iterator Search(const T &key);      //return pointer to node containing
    //  key. NULL if not there

    Iterator Prev(List<T>::Iterator iMarker);    //get the previous node to iMarker


    T &operator[](int index);                   //return the item at index

    Iterator Begin() const;                     //return the head of the list

    Iterator End() const;                       //return the tail of the list
    Iterator LastNode();
    T RemoveHead();
    //insertion operator for list
    friend ostream &operator<<(ostream &outs, const List<T> &list) {
        for (List<T>::Iterator it = list.Begin(); it != list.End(); it++) {
            outs << *it ;
        }
        return outs;
    }
private:
    node<T> *head;
};

template<typename T>
List<T>::List() {
    head = nullptr;
}

template<typename T>
List<T>::~List() {
    _ClearList(head);
}

template<typename T>
List<T>::List(const List<T> &copyThis) {
    head = _CopyList(copyThis.head);
}

template<typename T>
List<T> &List<T>::operator=(const List &RHS) {
    if (this == &RHS) {
        return *this;
    }
    _ClearList(head);
    head = _CopyList<T>(RHS.head);
    return *this;
}

template<typename T>
//inset i at the head of list
typename List<T>::Iterator List<T>::InsertHead(T i) {
    return Iterator(_insert_head(head, i));
}
//insert i after iMarker

//iMarker hides a pointer that holds the actual address of the node.
//but, _insertAfter needs this pointer,n ot the iterator.
//you must grab the pointer from the iterator and pass it to the function
//  _insertAfter

template<typename T>
typename List<T>::Iterator List<T>::InsertAfter(T i, List<T>::Iterator iMarker) {
    return Iterator(_InsertAfter(head, iMarker._ptr, i));
}

//insert i before iMarker
template<typename T>
typename List<T>::Iterator List<T>::InsertBefore(T i, List<T>::Iterator iMarker) {
    return Iterator(_InsertBefore(head, iMarker._ptr, i));
}

template<typename T>
//insert i. Assume sorted list
//the sortedlist insert function calls the _insertedsorted function
typename List<T>::Iterator List<T>::InsertSorted(T i) {
    //if the begin is bigger than end, descending, otherwise ascending
    if (head == nullptr) {
        return Iterator(_InsertSorted(head, i, true));
    } else {
        return Iterator(_InsertSorted(head, i, false));
    }
}

//delete node pointed to by iMarker
template<typename T>
T List<T>::Delete(List<T>::Iterator iMarker) {
    return _DeleteNode(head, iMarker._ptr);
}

template<typename T>
void List<T>::Print() const {
    _print_list(head);
}                                 //print the list
template<typename T>
//return pointer to node containing
typename List<T>::Iterator List<T>::Search(const T &key) {
    return Iterator(_SearchList(head, key));
}

//  key. NULL if not there
template<typename T>
//get the previous node to iMarker
typename List<T>::Iterator List<T>::Prev(List<T>::Iterator iMarker) {
    return Iterator(_PreviousNode(head, iMarker._ptr));
}

template<typename T>
//return the item at index
T &List<T>::operator[](int index) {
    return _At(head, index);
}

template<typename T>
//return the head of the list
typename List<T>::Iterator List<T>::Begin() const{
    return Iterator(head);
}

template<typename T>
//return the tail of the list
typename List<T>::Iterator List<T>::End() const{
    return Iterator(nullptr);
}
template<typename T>
typename List<T>::Iterator List<T>::LastNode(){
    return Iterator(_LastNode(head));
}
template <typename T>
T List<T>::RemoveHead(){
    return _remove_head(head);
}
#endif //LINKED_LISTS_LINKED_LIST_H
