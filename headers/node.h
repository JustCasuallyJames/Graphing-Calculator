//
// Created by james on 4/9/2020.
//

#ifndef NODE_NODE_H
#define NODE_NODE_H
#include <iostream>
#include <cassert>
using namespace std;
template <typename T>
struct node{
public:
    T _item;
    node* _next;
    node();
    node(T item);
    friend std::ostream& operator <<(std::ostream& outs, const node<T> &printMe){
        outs<<"["<<printMe._item<<"]->";
        return outs;
    }

};
//declarations
template<typename T>
node<T>* _insert_head(node<T>*& head_ptr, const T& item);
template<typename T>
ostream& _print_list(node<T>* head_ptr, ostream& outs = cout);
template<typename T>
node<T>* _InsertAfter(node<T>*& head, node<T>* afterThis, const T& insertThis);//insert after ptr
//return ptr to key or NULL
template<typename T>
node<T>* _SearchList(node<T>* head,const T& key);
template <typename T>
//delete, return item
T _DeleteNode(node<T>*&head, node<T>* deleteThis);
template <typename T> //insert before ptr
node<T>* _InsertBefore(node<T>*& head, node<T>* beforeThis, const T& insertThis);
template <typename T> //ptr to previous node
node<T>* _PreviousNode(node<T>* head, node<T>* prevToThis);
template <typename T>//duplicate the list...
node<T>* _CopyList(node<T>* head);
template <typename T>//delete all the nodes
void _ClearList(node<T>*& head);
template <typename T>//_item at this position
T& _At(node<T>* head, int pos);
template <typename T>
T _remove_head(node<T>*& headptr);
template <typename T> //insert
node<T>* _InsertSorted(node<T>* &head,const T& item, bool ascending = true);
template <typename T> //(node after which this, item , order: 0 ascending)
node<T>* _WhereThisGoes(node<T>* head, const T& item, bool ascending = true);
template <typename T>
node<T>* _LastNode(node<T>* head);            //Last Node in the list
template <typename T>
node<T>* _Insert_Sorted_and_Add(node<T>* &head, const T& item, bool ascending); //inserts the item and adds it.
//======================
//Definitions
template<typename T>
node<T>::node(){
    _item = T();
    _next = nullptr;
}
template<typename T>
node<T>::node(T item){
    _item = item;
    _next = nullptr;
}
template<typename T>
//this is a form of insert_before
node<T>* _insert_head(node<T>*& head_ptr, const T& item){
    //insert the item at the head(beginning) of the list: make it the first
    //link in the chain.
    //1: create a new node:
    node<T>* temp = new node<T>(item);
    //2. point (the next field of) this new node to where head is pointing to
    //temp->_next is pointing to wherever headptr is pointing to
    temp->_next = head_ptr;
    //3. point head to this new node:
    head_ptr = temp;

    return head_ptr;
}
template<typename T>
//insert after ptr
//if list is empty (head == nullptr), insert head
//else, do it normally
node<T>* _InsertAfter(node<T>*& head, node<T>* afterThis, const T& insertThis){
    if(head == nullptr){
        return _insert_head(head,insertThis);
    }else{
        node<T>* temp = new node<T>(insertThis);
        temp->_next = afterThis->_next; //Want the next value to be pointing to afterThis next value
        afterThis->_next = temp; //afterThis next will be pointing to the temp node
        return temp;
    }
}
template<typename T>
ostream& _print_list(node<T>* head_ptr, ostream& outs){
    outs<<"H->";
    if(head_ptr != nullptr){
        for (node<T>* w = head_ptr; w!=nullptr; w = w->_next){
            outs<<*w;
        }
    }
    outs<<"|||";
    return outs;
}
template <typename T>
//return ptr to key or NULL
node<T>* _SearchList(node<T>* head,const T& key){
    node<T>* walker = head; //sets a walker at the head
    while(walker != nullptr){ //checks if it's not a nullptr (end)
        if(key == walker->_item){ //checks if the key matches the walker
            return walker; //return the address of the walker
        }else{
            walker = walker->_next; //increment walker through the list
        }
    }
    return nullptr; //return nullptr if the key hasn't been found
}
template <typename T> //insert before ptr
node<T>* _InsertBefore(node<T>*& head, node<T>* beforeThis, const T& insertThis){
    //assert(head != nullptr);
    node<T>* previous = _PreviousNode(head,beforeThis);
    if(beforeThis == head){//if the thing you want to insert before is at the head
        return _insert_head(head,insertThis); //run the insert head
    }else{
        return _InsertAfter(head,previous,insertThis); //insert after any other value otherwise
    }
}
template <typename T>
//delete, return item
T _DeleteNode(node<T>*&head, node<T>* deleteThis){
    T item = deleteThis->_item;//save the delete this value
    if(head == deleteThis){
        _remove_head(head);
        return item;
    }else{
        _PreviousNode(head,deleteThis)->_next = deleteThis->_next;
        delete deleteThis;
    }
    return item;
}
template <typename T> //ptr to previous node
node<T>* _PreviousNode(node<T>* head, node<T>* prevToThis){
    if(head == prevToThis){return nullptr;}//return if there's no previous value
    node<T>* walker = head;
    while(walker != nullptr){ //as long as it doesn't reach the end
        if(walker->_next == prevToThis){ //if the next value is the value that you want to find the prev value of
            return walker; //return the node at that state.
        }
        walker = walker->_next; //increment
    }
//    assert(false); //if the mark isn't found
}
template<typename T>
node<T>* _CopyList(node<T>* head){
    node<T>* walker = head; //points to the headptr
    if(head!= nullptr){
        node<T>* newHead = new node<T>(head->_item);
        node<T>* temp = newHead;
//        node<T>* newNode = new node<T>(newHead->_item);
        while(walker->_next!=nullptr){
            walker = walker->_next;
//            newNode = new node<T>(walker->_item);
            _InsertAfter(newHead, temp, walker->_item);
            temp = temp->_next;
        }
        return newHead;
    }else{
        return walker; //this returns nullptr
    }

    /*
     template <typename T>
    node<T>* _copy_list(node<T>* head)
    {
    node<T>* wMain = head;
    node<T>* Hptr = new node<T>;
    _remove_head(Hptr);
    wMain = _last_node(head);

    while(wMain != head)
    {
        _insert_head(Hptr,wMain->_item);
        wMain = _previous_node(head,wMain);
    }
    _insert_head(Hptr,wMain->_item);

    return Hptr;
}
     */
//    if(head != nullptr){
//        node<T>* copiedList = new node<T>(walker->_item);
//        //have a new copiedlist with new node with the head
//        node<T>* afterThis = copiedList;
//        walker = walker->_next; //gets the next value
//        while(walker != nullptr){
//            _InsertAfter(copiedList,afterThis,walker->_item); //insert after the head
//            afterThis = afterThis->_next; //gets the next value
//            walker = walker->_next; //
//        }
//        return copiedList;
//    }else{
//        return walker;
//    }

}
template <typename T>//delete all the nodes
void _ClearList(node<T>*& head){
    node<T>* temp = head;
    node<T>* temp1;
    while(temp != nullptr){
        temp1 = temp->_next;
        delete temp;
        temp = temp1;
    }
//    delete head;
//    head = nullptr;
}
template <typename T>//_item at this position
T& _At(node<T>* head, int pos){
    node<T>* walker = head;
    for(int i=0;i<pos;i++){
        walker = walker->_next;
        assert(walker!=nullptr);
    }
    return walker->_item;
}
template <typename T>
T _remove_head(node<T>*& headptr){
    assert(headptr!=nullptr);
    node<T>* temp = headptr; //saves the headptr in a temp value
    headptr = headptr->_next; //headptr now points to the things next to headptr
    T item = temp->_item; //gives the item of the initial headptr
    delete temp; //deleting this node
    return item;
}
template <typename T>
node<T>* _InsertSorted(node<T>* &head, const T& item, bool ascending){
    node<T>* afterThis = _WhereThisGoes(head,item,ascending);
//    cout << "AfterThis: " << afterThis->_item << endl;

    if(afterThis == nullptr){
        return _insert_head(head,item);
    }else if(afterThis == head){  //if you're trying to insert before/after head
        if(head->_item >= item){//if the head->item is GREATER than item
            if(ascending){ //ascending
                return _insert_head(head,item);
            }else{
                return _InsertAfter(head,afterThis,item);
            }
        }else{ // if the head->item is LESS than item
            if(ascending){
                return _InsertAfter(head,afterThis,item); //insert greater item after
            }else{
                return _insert_head(head,item); //insert the greater item before
            }
        }
    }else{
        return _InsertAfter(head,afterThis,item);
    }
}
template <typename T> //(node after which this, item , order: 0 ascending)
//assume a sorted list
node<T>* _WhereThisGoes(node<T>* head, const T& item, bool ascending){
    if(head == nullptr){
        return head;
    }
    node<T>* walker = head;
    node<T>* leaderWalker = head->_next;
    if(ascending){ //ascending
        while((leaderWalker != nullptr) && (leaderWalker->_item <= item)){
            //1,2,3,4,5 item:3 | return the 3
            if(leaderWalker->_item == item){
                return leaderWalker;
            }
            walker = walker->_next;
            leaderWalker = leaderWalker->_next;
        }
        return walker;
    }else{ //DESCENDING
        while((leaderWalker != nullptr) && (leaderWalker->_item >= item)){
            //10,9,8,6 | insert: 8
            if(leaderWalker->_item == item){
                return leaderWalker;
            }
            walker = walker->_next;
            leaderWalker = leaderWalker->_next;

        }
        return walker;
    }
}
template <typename T>//Last Node in the list
node<T>* _LastNode(node<T>* head){
    node<T>* walker = head;
    while(walker != nullptr){
        if(walker->_next == nullptr){ //if it's at the end, it returns the last element
            return walker;
        }
        walker = walker->_next; //increment
    }
    return nullptr;
}
template <typename T>
node<T>* _Insert_Sorted_and_Add(node<T>* &head, const T& item, bool ascending){
    node<T>* afterThis = _WhereThisGoes(head,item,ascending); //what happens when it's null?
    if(afterThis == nullptr){
        return _insert_head(head,item);
    }else if(afterThis->_item == item){//checks if the whereThisGoes Item is the same as the item you're adding in
        afterThis->_item += item;
        //ex: 3x^3 + 2x^2 + x + 3 || insert: 3
        // 3x^3 + 2x^2 + 3x + 6
    }else{
        return _InsertSorted(head,item,ascending);
    }
    return afterThis;
}
#endif //NODE_NODE_H
