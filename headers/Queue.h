

#ifndef STACK_QUEUE_QUEUE_H
#define STACK_QUEUE_QUEUE_H
#include "linked_list.h"
template <typename T>
class Queue {
public:
    class Iterator{
    public:

        Iterator(const typename List<T>::Iterator &it) : listit(it) {}

        T &operator*(){
            return *listit;
        }
        const T &operator*() const{
            return *listit;
        }
        T *operator->(){ //returns the list's -> operator
            return listit.operator->();
        }
        const T *operator->() const{ //returns the lists -> operator const
            return listit.operator->();
        }
        operator bool() const{
            return listit;
        }
        bool operator!=(const Iterator &rhs) const{
            return listit != rhs.listit;
        }
        bool operator==(const Iterator &rhs) const{
            return listit == rhs.listit;
        }
        Iterator &operator++(){ // ++i
            ++listit;
            return *this;
        }
        Iterator operator++(int){ // i++
            Iterator temp(listit);
            operator++();
            return temp;
        }

    private:
        typename List<T>::Iterator listit;
    };

    Queue();

//    ~Queue();
    Queue(const Queue<T> &copyThis);
    Queue &operator=(const Queue &RHS);

    void push(const T& insert);
    T pop();
    bool isEmpty() const;
    int size() const;
    typename Queue<T>::Iterator  begin() const;
    typename Queue<T>::Iterator end() const;
    friend ostream &operator<<(ostream &outs, const Queue<T> &list) {
        for(Queue<T>::Iterator it=list.begin(); it!=list.end();it++){
            outs << *it << " | ";
        }
        return outs;
    }
private:
    List<T> _list;
    typename List<T>::Iterator _rear;
    int _size;

};
template<typename T>
Queue<T>::Queue(): _size(0){
    _rear = _list.End();
}
//template<typename T>
//Queue<T>::~Queue(){}
template<typename T>
Queue<T>::Queue(const Queue<T> &copyThis){
    _list = copyThis._list;
    _size = copyThis._size;
    _rear = _list.LastNode();
}
template<typename T>
Queue<T> &Queue<T>::operator=(const Queue<T> &RHS){
    if(this == &RHS){
        return *this;
    }
//    ~Queue();
    _list = RHS._list;
    _size = RHS._size;
    _rear = _list.LastNode();
    return *this;
}

template <typename T>
void Queue<T>::push(const T& insert){
    _rear = _list.InsertAfter(insert,_rear);
    _size++;
}
template <typename T>
T Queue<T>::pop(){
    assert(!isEmpty());
    T value = _list.Delete(_list.Begin());
    _size--;
    return value;
}
template<typename T>
bool Queue<T>::isEmpty() const{
    return (_size == 0);
}
template<typename T>
int Queue<T>::size() const{
    return _size; //returns how many nodes are in the list
}
template <typename T>
typename Queue<T>::Iterator Queue<T>::begin() const{
    return Iterator(_list.Begin());
}
template <typename T>
typename Queue<T>::Iterator Queue<T>::end() const {
    return Iterator(_list.End());
}

#endif //STACK_QUEUE_QUEUE_H
