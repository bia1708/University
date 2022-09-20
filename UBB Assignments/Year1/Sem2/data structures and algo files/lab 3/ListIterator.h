#pragma once
#include "SortedIndexedList.h"


//DO NOT CHANGE THIS PART
class ListIterator{
    friend class SortedIndexedList;
private:
    SortedIndexedList& list;
    ListIterator(SortedIndexedList& list);
    int currentElement;

public:
    void first();
    void next();
    bool valid() const;
    TComp getCurrent() const;
    TComp remove();
};


