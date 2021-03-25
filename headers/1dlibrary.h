#pragma once
//
// Created by james on 3/26/2020.
//
#ifndef INC_1DLIBRARY_1DLIBRARY_H
#define INC_1DLIBRARY_1DLIBRARY_H
#include <iostream>
#include <cassert>
using namespace std;
//declarations
template <typename T>
void init_value(T* arr1d, int size, T value);
template <typename T>
void init(T* arr1d, int size);
template<typename T>
void print1d(T* arr, int size);
template<typename T>
T* allocate1d(int capacity);
template <typename T>
T* reallocate(T* arr, int currentcap, int newcap);
template <typename T>
T* deallocate(T* arr);
template <typename T>
T& get(T* arr1d, int col);
template <typename T>
void write(T* arr1d, int col, const T& data);
template <typename T>
void read(T* arr1d, int col);
template<typename T>
void shiftleft(T* ptr, T* currentpos, int& size);
template<typename T>
void shiftright(T* ptr, T* currentpos, int& size);
template <typename T>
T* search_entry(T* list, const T& find_me, int size);
template <typename T>
void copy_list(T* dest, T* src, const int size);

//initialization
template <typename T>
void init_value(T* arr1d, int size, T value) {
    for (int i = 0; i < size; i++, arr1d++) {
        *arr1d = value;
    }
}
template <typename T>
void init(T* arr1d, int size) {
    for (int i = 1; i <= size; i++, arr1d++) {
        *arr1d = i;
    }
}
template<typename T>
void print1d(T* arr, int size) {
    for (int i = 0; i < size; i++, arr++) {
        cout << *arr << " ";
    }
    cout << endl;
}
template <typename T>
T* deallocate(T* arr) {
    delete[] arr;
}
template<typename T>
T* allocate1d(int capacity) {
    return new T[capacity];
}
template <typename T>
T& get(T* arr1d, int col) {
    T* temp = arr1d + col;
    return *temp;
}
template <typename T>
void write(T* arr1d, int col, const T& data) {
    get(arr1d, col) = data; //saves the value into the location
}
template <typename T>
T read(T* arr1d, int col) {
    return get(arr1d, col);
}
template <typename T>
void shiftleft(T* ptr, T* currentpos, int& size) {
    T* temp = currentpos + 1; //the next value of currentpos
    T* end = ptr + size;
    //run as long as the currentpos doesn't reach the end
    while (currentpos < end) {
        *currentpos = *temp; //saves the temp value into the current position
        //increment the temp and currentpos
        temp++;
        currentpos++;
    }
    //decrement size to get rid of necessary values
    size--;
}
template<typename T>
void shiftright(T* ptr, T* currentpos, int& size) {
    T* temp1 = ptr + size - 1;
    T* end = ptr + size;
    while (currentpos < end) {
        *end = *temp1;
        temp1--;
        end--;

    }
    size++;
}
/*
 search_entry searches for the first instance of the find_me value
 list represents the pointer you're searching through
 find_me is the key you are trying to find
 size is the size of the pointer
 */
template <typename T>
T* search_entry(T* list, const T& find_me, int size) {
    //Find the location of the key
    T* end = list + size;
    //run as long as list is less than the size
    while (list < end) {
        //check if the pointer the pointer is pointing to is the find_me value
        if (*list == find_me) {
            return list;
        }
        else {
            list++;
        }
    }
    //returns the nullptr if the key isn't found in the array
    return nullptr;
}
template <typename T>
void copy_list(T* dest, T* src, const int size) {
    for (int i = 0; i < size; i++, src++, dest++) {
        *dest = *src;
    }
}
template <typename T>
T* reallocate(T* arr, int currentcap, int newcap) {
    T* newarr = allocate1d<T>(newcap); //allocates a pointer with the newcap
    copy_list(newarr, arr, currentcap);
    delete[] arr; //deletes the previous arr
    return newarr;
}
#endif //INC_1DLIBRARY_1DLIBRARY_H
