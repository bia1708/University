#include "ListIterator.h"
#include "SortedIndexedList.h"
#include <exception>
using namespace std;


SortedIndexedList::SortedIndexedList(Relation r) {
    this->r = r;
    this->list = new DLLANode[1];
    this->list[0].info = NULL_TCOMP;
    this->list[0].prev = this->list[0].next = -1;
    this->emptyPos = 0;
    this->head = this->tail = -1;
    this->capacity = 1;
    this->listSize = 0;
}
/// theta(1)

// this function prepares the arrray for the addition of a new element
int SortedIndexedList::allocate() {
    // first, we check for the need to resize the array
    if(this->listSize + 1 > this->capacity)
        this->resize();

    // when we add a new element, we need to remove it from the empty elements SLL
    int currentPos = this->emptyPos;
    this->emptyPos = this->list[emptyPos].next;

    // we initialise the element we want to add
    this->list[currentPos].info = NULL_TCOMP;
    this->list[currentPos].prev = this->list[currentPos].next = -1;

    this->listSize++;
    return currentPos;
}
/// BC: theta(1)
/// WC: theta(capacity)
/// TC: O(capacity)

// this function deals with the removal of an element from the list
void SortedIndexedList::deallocate(int position) {
    // we put the removed element in the empty elements SLL
    this->list[position].next = this->emptyPos;
    this->emptyPos = position;
    this->listSize--;
}
/// theta(1)

void SortedIndexedList::resize(){
    // we make the capacity bigger
    this->capacity *= 2;
    DLLANode* newList = new DLLANode[this->capacity];

    // we put all the elements from our list into the new list
    for(int i = 0; i < this->capacity / 2; i++)
        newList[i] = this->list[i];

    // we put all the unoccupied elements in the empty elements SLLA
    for(int i = this->capacity / 2; i < this->capacity; i++) {
        newList[i].info = NULL_TCOMP;
        newList[i].next = emptyPos;
        newList[i].prev = -1;
        emptyPos = i;
    }
    delete[] this->list;
    this->list = newList;
}
/// theta(capacity)

int SortedIndexedList::size() const {
    return this->listSize;
}
/// theta(1)

bool SortedIndexedList::isEmpty() const {
    return this->listSize == 0;
}
/// theta(1)

TComp SortedIndexedList::getElement(int i) const{
    if(i < 0 || i >= this->listSize)
        throw exception();
    int j = 0, node = this->head;
    while(j < i){
        node = this->list[node].next;
        j++;
    }
    return this->list[node].info;
}
/// BC: theta(1)
/// WC: theta(capacity)
/// TC: O(capacity)

TComp SortedIndexedList::remove(int i) {
    if(i < 0 || i >= this->listSize)
        throw exception();

    // here we check to see if the node is the only one in the list
    if(this->head == this->tail){
        TComp removedElem = this->list[this->head].info;

        deallocate(this->head);
        this->head = this->tail = -1;

        return removedElem;
    }

    // here we get to the wanted node
    int j = 0, node = this->head;
    while(j < i){
        node = this->list[node].next;
        j++;
    }

    TComp removedElem = this->list[node].info;

    // if the node is the first one in the list
    if(node == this->head){
        int nextPos = this->list[head].next;
        this->list[nextPos].prev = -1;
        this->head = nextPos;
    } else if (node == this->tail) {
        int prevPos = this->list[tail].prev;
        this->list[prevPos].next = -1;
        this->tail = prevPos;
    } else {
        int prevPos = this->list[node].prev;
        int nextPos = this->list[node].next;
        this->list[prevPos].next = nextPos;
        this->list[nextPos].prev = prevPos;
    }

    deallocate(node);
    return removedElem;
}
/// BC: theta(1)
/// WC: theta(capacity)
/// TC: O(capacity)

int SortedIndexedList::search(TComp e) const {
    int j = 0, node = this->head;
    // we search for the desired element in the DLLA
    while(j < this->listSize && this->list[node].info != e){
        node = this->list[node].next;
        j++;
    }
    // if it doesn't exist we return -1
    if(j == this->listSize)
        return -1;
    return j;
}
/// BC: theta(1)
/// WC: theta(capacity)
/// TC: O(capacity)

void SortedIndexedList::add(TComp e) {
    int elemPos = allocate();
    this->list[elemPos].info = e;
    int node = this->head;

    // case when the list is empty
    if(this->head == -1){
        this->head = elemPos;
        this->list[elemPos].prev = -1;
        this->list[elemPos].next = -1;
        this->tail = elemPos;
        return;
    }

    // here we find the right position to insert the element in the DLLA
    while(node != -1 && !this->r(e, this->list[node].info))
        node = this->list[node].next;

    // if the node we want to add is on the last position in the DLLA
    if(node == -1){
        this->list[elemPos].prev = this->tail;
        this->list[elemPos].next = -1;
        this->list[this->tail].next = elemPos;
        this->tail = elemPos;

    } else if(node == this->head) {
        // if the node we want to insert is on the first position in the DLLA
        this->list[elemPos].prev = -1;
        this->list[elemPos].next = this->head;
        this->list[this->head].prev = elemPos;
        head = elemPos;
    } else {
        // we connect the previous node
        int prevPos = this->list[node].prev;
        this->list[prevPos].next = elemPos;

        // we connect the current node
        this->list[elemPos].prev = prevPos;
        this->list[elemPos].next = node;

        // we connect the next node
        this->list[node].prev = elemPos;
    }
}
/// BC: theta(1)
/// WC: theta(capacity)
/// TC: O(capacity)

ListIterator SortedIndexedList::iterator(){
    return ListIterator(*this);
}
/// theta(1)

//destructor
SortedIndexedList::~SortedIndexedList() {
    delete[] this->list;
}
/// theta(1)

SortedIndexedList &SortedIndexedList::operator=(const SortedIndexedList &myList) {
    delete[] this->list;
    this->r = myList.r;
    this->emptyPos = myList.emptyPos;
    this->head = myList.head;
    this->tail = myList.tail;
    this->capacity = myList.capacity;
    this->listSize = myList.listSize;

    this->list = new DLLANode[myList.capacity];
    for(int i = 0; i < myList.capacity; i++)
        this->list[i] = myList.list[i];

    return *this;
}
/// theta(capacity)

SortedIndexedList::SortedIndexedList(const SortedIndexedList &myList) {
    this->r = myList.r;
    this->emptyPos = myList.emptyPos;
    this->head = myList.head;
    this->tail = myList.tail;
    this->capacity = myList.capacity;
    this->listSize = myList.listSize;

    this->list = new DLLANode[myList.capacity];
    for(int i = 0; i < myList.capacity; i++)
        this->list[i] = myList.list[i];
}
/// theta(capacity)
