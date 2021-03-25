//
// Created by james on 3/26/2020.
//

#ifndef VECTOR_VECTOR_H
#define VECTOR_VECTOR_H

#include <iostream>
#include <cassert>
#include "1dlibrary.h"

using namespace std;

template<typename T>
class Vector {
public:
    Vector(unsigned int capacity = 6);
    // big three:
    Vector(const Vector &other);
    Vector &operator=(const Vector &other);
    ~Vector();

    //member access functions:
    const T operator[](const unsigned int index) const;
    T &operator[](const unsigned int index);

    template <typename U>
    friend const bool operator==(const Vector<U> &v1, const Vector<U> &v2);
    template <typename U>
    friend const bool operator!=(const Vector<U> &v1, const Vector<U> &v2);

    T &at(int index);             //return reference to item at position index
    const T at(int index) const;  //return a const item at position index
    T &front() const;             //return item at position 0.
    T &back() const;              //return item at the last position

    //Push and Pop functions:
    Vector &operator+=(const T &item); //push_back
    void push_back(const T &item);      //append to the end
    T pop_back();                       //remove last item and return it

    //Insert and Erase:
    void insert(int insert_here, const T &insert_this); //insert at pos
    void erase(int erase_index);        //erase item at position
    int index_of(const T &item);        //search for item. retur index.

    //size and capacity:
    void set_size(int size);            //enlarge the vector to this size
    void set_capacity(int capacity);    //allocate this space
    int get_size() const { return _size; } //return _size
    int get_capacity() const { return _capacity; } //return _capacity
    T* get_v()const {return _v;}


    //errors
    bool error_handling();                 //returns true if theres no errors
    bool empty() const;                 //return true if vector is empty


    //testing function
    void vector_test_1();

    //OUTPUT:
    template<class U>
    friend ostream &operator<<(ostream &outs, const Vector<U> &_a);

private:
    int _capacity;
    int _size;
    T *_v;
    int _error; // size > capacity || asserting is needed if the person tries to look for a number at a certain index.
};

//Constructors
template<typename T>
Vector<T>::Vector(unsigned int capacity) {
    _capacity = capacity;
    _size = 0;
    _v = allocate1d<T>(capacity);
}

template<typename T>
Vector<T>::Vector(const Vector &other) {
    //1. copy all the variables:
    this->_size = other._size;
    this->_capacity = other._capacity;
    //2. allocate space
    _v = allocate1d<T>(_capacity);
    //3. copy all elements from other to me.
    copy_list(_v,other._v,_size);
}

template<typename T>
Vector<T> &Vector<T>::operator=(const Vector &other) {
    //1. check for self reference
    if (this == &other) {
        //v1 = v1;
        return *this; //return this object (me!)
    }
    //2. release existing dynamic space
    delete[] _v;
    //3. copy all the variables:
    _size = other._size;
    //4. allocate space
    _v = allocate1d<T>(_size);
    //5. copy all elements from other to me.
    copy_list(_v, other._v, _size);
}

template<typename T>
//destructor
Vector<T>::~Vector() {
    //release space allocated to this object.
    delete[] _v;
}

template<typename T>
//return reference to item at position index
T &Vector<T>::at(int index) {
    return get(_v,index);
}

template<typename T>
//return a const item at position index
const T Vector<T>::at(int index) const {
    return get(_v,index);
}

template<typename T>
//return item at position 0.
T &Vector<T>::front() const {
    return *_v;
}

template<typename T>
//return item at the last position
T &Vector<T>::back() const {
    T* temp = _v +_size-1;
    return *temp;
}

template<typename T>
//append to the end
void Vector<T>::push_back(const T &item) {
//    shiftright(_v,_v+_size,_capacity); //increases the capacity
    _capacity++;
    _v = reallocate(_v,_size,_capacity);
    write(_v,_size,item);
    _size++;
}

template<typename T>
//remove last item and return it
T Vector<T>::pop_back() {
    T temp = get(_v,_size-1);
    shiftleft(_v, _v + _size-1, _size); //decreases the capacity
    _capacity--;
    _v = reallocate(_v, _size, _capacity);
    return temp;
}

//Insert and Erase:
//insert at pos
template<typename T>
void Vector<T>::insert(int insert_here, const T &insert_this) {
    _size++;
    shiftright(_v, _v + insert_here,_capacity);
    _v = reallocate(_v,_size,_capacity); //did a capacity +1
    write(_v,insert_here, insert_this);
}

template<typename T>
//erase item at position
void Vector<T>::erase(int erase_index) {
    shiftleft(_v, _v + erase_index, _capacity);
    _v = reallocate(_v,_size,_capacity); // did a capacity -1
}

template<typename T>
//search for item. return index.
int Vector<T>::index_of(const T &item) {
//    cout << "Value: " << *search_entry(_v, item, _capacity) << endl;
    return *search_entry(_v, item, _capacity);
}


//size and capacity:
//enlarge the vector to this size
template<typename T>
void Vector<T>::set_size(int size) {
//    if(size > _capacity){
//        _v = reallocate(_v,_capacity,_size*2);
//        _capacity = _size * 2;
//    }
    this->_size = size;
}

template<typename T>
//allocate this space
void Vector<T>::set_capacity(int capacity) {
    this->_capacity = capacity;
}

//Operators:
template<typename U>
const U Vector<U>::operator[](const unsigned int index) const {
    return get(_v, index);
}

template<typename U>
//gets the value at the index
U &Vector<U>::operator[](const unsigned int index) {
    return get(_v,index);
}

template<typename U>
//checks if it's EQUAL
const bool operator==(const Vector<U> &v1, const Vector<U> &v2) {
    return v1._size == v2._size && v1._capacity == v2._capacity && v1._size == v2._size;
}

template<typename U>
//checks if it's NOT equal
const bool operator!=(const Vector<U> &v1, const Vector<U> &v2) {
    return v1._size != v2._size && v1._capacity != v2._capacity && v1._size != v2._size;
}

template<typename U>
Vector<U> &Vector<U>::operator+=(const U &item) {
    //something = something + item
    write(_v,_size,item);
    _size++;
    return *this;
}



template<typename U>
//prints out the whole array
ostream &operator<<(ostream &outs, const Vector<U> &print_me) {
    print1d(print_me._v, print_me._size);
    return outs;
}

//error handling
template<typename T>
bool Vector<T>::empty() const {
    return _size == 0;
}

template<typename T>
bool Vector<T>::error_handling() {
    assert(_size > _capacity);
    return true;
}

template<typename T>
void Vector<T>::vector_test_1(){
    Vector<int> v(15);
    v.set_size(10);
    init(v.get_v(),v.get_capacity());
    //=====this is where all the testing begins=====
    cout << "This is the initialized vector: ";
    print1d(v.get_v(),v.get_size());
    //testing all the functions at,front,back
    v.insert(4,32);
    cout << "This is the vector after the insert function: ";
    print1d(v.get_v(),v.get_size());
    cout << "Testing the [at()]... Number at index 4 is: "<< v.at(4) << endl;
    cout << "Testing the [front()]... the first number at position 0: " << v.front() << endl;
    cout << "Testing the [back()]... the last number at the last position: " << v.back() << endl;
    cout << "Testing the [push_back(item)]... Array after appended the number 57 : ";
    v.push_back(57);
    print1d(v.get_v(),v.get_size());
    cout << "Testing the [pop_back()]... Deleting the number " << v.pop_back() <<": ";
    print1d(v.get_v(),v.get_size());
    cout << "Testing the [erase()]... Erasing the first index: ";
    v.erase(0);
    print1d(v.get_v(),v.get_size());
    cout << "Testing the [index_of()]... The index of 32 is at index: " << v.index_of(32) << endl;
    Vector<int> v1(20);
    v1.set_size(15);
    cout << "Is v and v1 equal? : ";
    if(v1==v){
        cout << "True" << endl;
    }else{
        cout << "False" << endl;
    }
    Vector<int> v2(v);
    cout << "is v and v2 equal? : ";
    if(v2==v){
        cout << "True" << endl;
    }else{
        cout << "False" << endl;
    }
    //Testing the += operator
    v+=172;
    cout << "Testing the += operator and <<. This is the vector after appending 172: ";
    cout << v << endl;
}
#endif //VECTOR_VECTOR_H
