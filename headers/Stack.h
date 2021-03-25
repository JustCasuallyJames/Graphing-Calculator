

#ifndef STACK_QUEUE_STACK_H
#define STACK_QUEUE_STACK_H
#include "node.h"
template <typename T>
class Stack {
public:
    class Iterator{
    public:
        friend class Stack;

        Iterator(node<T>* p = nullptr) : _ptr(p) {}     //constructor

        const T &operator*() const {        //dereference oprator
            assert(_ptr);
            return _ptr->_item;
        }
        operator bool(){
            return _ptr != nullptr;
        }
        const T* operator ->()const{
            assert(_ptr);
            return &_ptr->_item; //returns the reference of the item within the node
        }
        friend Iterator operator++(Iterator &it, int unused) {//it++
            Iterator hold(it);
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

    Stack();

    ~Stack();
    Stack(const Stack<T>& copyThis);
    Stack &operator=(const Stack &RHS);
    void push(const T& insert);
    T pop();
    bool isEmpty() const;
    int size() const;
    typename Stack<T>::Iterator  begin() const;
    typename Stack<T>::Iterator end() const;
    friend ostream& operator<<(ostream& outs, const Stack<T>& list) {
        for (Stack<T>::Iterator it = list.begin(); it != list.end(); it++) {
            outs << *it << " | ";
        }
        return outs;
    }
private:
    node<T>* _head;
    int _size;
};
template<typename T>
Stack<T>::Stack(){
    _head = nullptr;
    _size = 0;
}
template <typename T>
Stack<T>::~Stack(){}
template <typename T>
Stack<T>::Stack(const Stack<T>& copyThis){
    _head = _CopyList(copyThis);
}
template <typename T>
Stack<T> &Stack<T>::operator=(const Stack<T> &RHS){
    if(this == &RHS){
        return *this;
    }
    ~Stack();
    _head = RHS._head;
    _size = RHS._size;
    return *this;
}
template<typename T>
void Stack<T>::push(const T& insert){ //inserts at the top
    _insert_head(_head,insert); //inserts head pretty much
    _size++; //increase the size of how many nodes there are
}
template <typename T>
T Stack<T>::pop(){
    assert(!isEmpty()); //checks if the list is not empty
    T value = _remove_head(_head); //saves the value from remove head | this removes the top value
    _size--; //decrements the size of the list
    return value; //returns the popped value
}
template <typename T>
bool Stack<T>::isEmpty() const{
    return _size==0; //checks if the list is empty
}
template <typename T>
int Stack<T>::size() const{
    return _size; //number of nodes in the list
}
template <typename T>
typename Stack<T>::Iterator  Stack<T>::begin() const{
    return Iterator(_head); //returns beginning
}
template <typename T>
typename Stack<T>::Iterator Stack<T>::end() const{
    return Iterator(nullptr); //returns the end of list
}

#endif //STACK_QUEUE_STACK_H
