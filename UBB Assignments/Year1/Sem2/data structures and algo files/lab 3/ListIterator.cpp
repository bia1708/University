#include "ListIterator.h"
#include "SortedIndexedList.h"
#include <iostream>

using namespace std;

ListIterator::ListIterator(SortedIndexedList& list) : list(list) {
    this->currentElement = this->list.head;

}
/// theta(1)


void ListIterator::first(){
    this->currentElement = this->list.head;
}
/// theta(1)


void ListIterator::next(){
    if (this->currentElement == -1)
        throw exception();

    this->currentElement = this->list.list[this->currentElement].next;
}
/// theta(1)


bool ListIterator::valid() const{
    if (this->currentElement == -1)
        return false;
    return true;
}
/// theta(1)


TComp ListIterator::getCurrent() const{
    if (this->currentElement == -1)
        throw exception();
    return this->list.list[this->currentElement].info;
}
/// theta(1)

TComp ListIterator::remove(){
    if(!this->valid())
        throw exception();

    TComp removedElem = this->getCurrent();

    if(this->list.head == this->list.tail){
        TComp removedElem = this->list.list[this->list.head].info;

        this->list.deallocate(this->list.head);
        this->list.head = this->list.tail = -1;

        this->currentElement = -1;
        return removedElem;
    }

    if(this->currentElement == this->list.head){
        int nextPos = this->list.list[this->list.head].next;
        this->list.list[nextPos].prev = -1;
        this->list.head = nextPos;
    } else if (this->currentElement == this->list.tail) {
        int prevPos = this->list.list[this->list.tail].prev;
        this->list.list[prevPos].next = -1;
        this->list.tail = prevPos;
    } else {
        int prevPos = this->list.list[this->currentElement].prev;
        int nextPos = this->list.list[this->currentElement].next;
        this->list.list[prevPos].next = nextPos;
        this->list.list[nextPos].prev = prevPos;
    }
    int nextElem = this->list.list[this->currentElement].next;
    this->list.deallocate(this->currentElement);
    this->currentElement = nextElem;
    return removedElem;
}
/// theta(1)

