#pragma once
//DO NOT INCLUDE SORTEDBAGITERATOR
#include <stdlib.h>
#include <iostream>
//DO NOT CHANGE THIS PART
typedef int TComp;
typedef TComp TElem;
typedef bool(*Relation)(TComp, TComp);
#define NULL_TCOMP -11111;
const double LOAD_FACTOR = 0.7;
#define NULL_TELEM -842150451
typedef bool(*Condition)(TComp);

class SortedBagIterator;

struct Node{
    TComp value;
    int next;
};

class SortedBag {
    friend class SortedBagIterator;

private:
    Relation relation;
    Node *hashTable;
    int capacity;
    int elemCount;
    int hashFunc(int elem) const { return abs(elem) % this->capacity; }

public:
    //constructor
    SortedBag(Relation r);

    //adds an element to the sorted bag
    void add(TComp e);

    void rehash();

    //removes one occurence of an element from a sorted bag
    //returns true if an eleent was removed, false otherwise (if e was not part of the sorted bag)
    bool remove(TComp e);

    //checks if an element appearch is the sorted bag
    bool search(TComp e) const;

    //returns the number of occurrences for an element in the sorted bag
    int nrOccurrences(TComp e) const;

    //returns the number of elements from the sorted bag
    int size() const;

    //returns an iterator for this sorted bag
    SortedBagIterator iterator() const;

    //checks if the sorted bag is empty
    bool isEmpty() const;

    //destructor
    ~SortedBag();

    void resize();

    void filter(Condition cond);
};