#include <assert.h>
#include <iostream>
#include "ListIterator.h"
#include "SortedIndexedList.h"

using namespace std;

bool relation1(TComp e1, TComp e2) {
	if (e1 <= e2) {
		return true;
	}
	else {
		return false;
	}
}

void testAll(){
	SortedIndexedList list = SortedIndexedList(relation1);
	assert(list.size() == 0);
	assert(list.isEmpty());
    list.add(1);
    assert(list.size() == 1);
    assert(!list.isEmpty());
    ListIterator iterator = list.iterator();
    assert(iterator.valid());
    iterator.first();
    assert(iterator.getCurrent() == 1);
    iterator.next();
    assert(!iterator.valid());
    iterator.first();
    assert(iterator.valid());
    assert(list.search(1) == 0);
    assert(list.remove(0) == 1);
    assert(list.size() == 0);
    assert(list.isEmpty());
}

void testExtra(){
    SortedIndexedList list = SortedIndexedList(relation1);
    list.add(1);
    list.add(2);
    ListIterator iterator = list.iterator();
    iterator.remove();
    assert(list.search(1) == -1);
    assert(iterator.getCurrent() == 2);
    iterator.remove();
    assert(!iterator.valid());
    cout << "MY TEST PASSED";
}