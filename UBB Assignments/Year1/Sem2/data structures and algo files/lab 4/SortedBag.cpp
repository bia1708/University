#include "SortedBag.h"
#include "SortedBagIterator.h"
#include <cmath>
#include <iostream>

SortedBag::SortedBag(Relation r) {
    this->relation = r;
    this->capacity = 20;
    this->hashTable = new Node[this->capacity];
    for (int i = 0; i < this->capacity; i++) {
        this->hashTable[i].value = NULL_TELEM;
        this->hashTable[i].next = -1;
    }
    this->elemCount = 0;
}
// BC: theta(capacity)
// WC: theta(capacity)
// BC: theta(1)
// WC: theta(capacity + elemCount)
// BC: theta(1)
// WC: theta(elemCount)
// BC: theta(1)
// WC: theta(elemCount)
// BC: theta(1)
// WC: theta(elemCount)


// TC: O(n)
void SortedBag::resize() {
    Node *newHashTable = new Node[this->capacity + 20];

    for (int i = 0; i < this->capacity + 20; i++) {
            newHashTable[i].value = NULL_TELEM;
            newHashTable[i].next = -1;
    }

    for (int i = 0; i < this->capacity; i++) {
        int key = abs(this->hashTable[i].value) % (this->capacity + 20); // rehashing the table

        if (newHashTable[key].value == NULL_TELEM) {
            newHashTable[key].value = this->hashTable[i].value;
        } else {
            Node head = newHashTable[key];
            int pos = key;
            while (head.next != -1) {
                head = newHashTable[head.next];
                pos = head.next;
            }

            int endPos = -1;
            for (int j = this->capacity - 1; j > 0; j--) {
                if (newHashTable[j].value == NULL_TELEM) {
                    endPos = j;
                    break;
                }
            }
            newHashTable[pos].next = endPos;
            newHashTable[endPos].value = this->hashTable[i].value;
            newHashTable[endPos].next = -1;
        }
    }

    this->hashTable = newHashTable;
    this->capacity += 20;
}

// AC: theta(capacity)
void SortedBag::add(TComp e) {
    double load = (double) this->elemCount / this->capacity;
    if (load >= LOAD_FACTOR)
        this->resize();

    // we get the position on which we want to insert the new elem in the hash table
    int key = this->hashFunc(e);
    if (this->hashTable[key].value == NULL_TELEM) {
        // first case is when the element is not already in the hash table and the position is empty
        this->hashTable[key].value = e;
    } else {
        // second case is when the position isn't empty

        // we check to see if the element fits inside the chain by parsing it starting from the key position
        Node head = this->hashTable[key];
        int pos = key;
        while (head.next != -1) {
            head = this->hashTable[head.next];
            pos = head.next;
        }

        // if the element fits inside the chain we need to find an empty position starting from the end of the table
        // and move every element one position to the right
        // otherwise, we just add it at the end

        int endPos = -1;
        for (int i = this->capacity - 1; i > 0; i--) {
            if (this->hashTable[i].value == NULL_TELEM) {
                endPos = i;
                break;
            }
        }
        this->hashTable[pos].next = endPos;
        this->hashTable[endPos].value = e;
        this->hashTable[endPos].next = -1;
//        TElem nextElem = this->hashTable[pos].value;
//        // we insert the new element
//        this->hashTable[pos].value = e;
//        if(this->hashTable[pos].next == -1)
//            this->hashTable[pos].next = endPos;
//        pos = this->hashTable[pos].next;
//
//        // we move all the remaining elements
//        while(pos != -1){
//            this->hashTable[pos].value = nextElem;
//            nextElem = this->hashTable[pos].value;
//            pos = this->hashTable[pos].next;
//            if(this->hashTable[pos].next == -1)
//                this->hashTable[pos].next = endPos;
//        }
//        this->hashTable[endPos].next = -1;
    }
    this->elemCount++;

//    int var = key;
//    if(var == 99) {
//        while (this->hashTable[var].next != -1){
//            auto elem = this->hashTable[key].value;
//            std::cout << " elem: " << elem << " pos: " << var << "next: " << this->hashTable[var].next << '\n';
//            var = this->hashTable[var].next;
//        }
//    std::cout << "---------------------------------------------------\n";
//    }

}

// AC: theta(capacity + elemCount)
bool SortedBag::remove(TComp e) {
    int key = this->hashFunc(e);
    if (this->hashTable[key].value == NULL_TELEM) {
        return false;
    }
    // if the element isn't linked to any other elements
    if (this->hashTable[key].next == -1) {
        this->hashTable[key].value = NULL_TELEM;
        this->elemCount--;
        return true;
    } else {
        // if the element is linked to other elements
        int previous = -1;
        while (key != -1 && this->hashTable[key].value != e) {
            previous = key;
            key = this->hashTable[key].next;
        }

        // if we don't find the element in the chain
        if (key == -1)
            return false;


        int nextPos = this->hashTable[key].next;
        while (this->hashTable[nextPos].next != -1) {
            int copyNextPos = nextPos;
            nextPos = this->hashTable[key].next;
            this->hashTable[key] = this->hashTable[nextPos];
            key = copyNextPos;
        }
        this->hashTable[key] = this->hashTable[nextPos];
        this->hashTable[nextPos].value = NULL_TELEM;
        this->hashTable[nextPos].next = -1;
        this->elemCount--;
        return true;
    }
}

// AC: theta(elemCount)
bool SortedBag::search(TComp elem) const {
    int key = this->hashFunc(elem);
    while (key != -1) {
        if (this->hashTable[key].value == elem) {
            return true;
        }
        key = this->hashTable[key].next;
    }
    return false;
}


// AC: theta(elemCount)
int SortedBag::nrOccurrences(TComp elem) const {
    int count = 0;
    int key = this->hashFunc(elem);
    while (key != -1) {
        if (this->hashTable[key].value == elem) {
            count++;
        }
        key = this->hashTable[key].next;
    }
    return count;
}


// AC: theta(elemCount)
int SortedBag::size() const {
    return this->elemCount;
}

// TC: theta(1)
bool SortedBag::isEmpty() const {
    return this->elemCount == 0;
}


// TC: theta(1)
SortedBagIterator SortedBag::iterator() const {
    return SortedBagIterator(*this);
}


// TC: theta(1)
SortedBag::~SortedBag() {
    delete[] this->hashTable;
}


// TC: theta(1)

void SortedBag::filter(Condition cond) {
    while(!this->iterator().valid()) {
        if (!cond(this->iterator().getCurrent()))
            this->remove(this->iterator().getCurrent());
        this->iterator().next();
    }
}

// BC: theta(1)
// WC: theta(elemCount)
// AC: theta(elemCount)

