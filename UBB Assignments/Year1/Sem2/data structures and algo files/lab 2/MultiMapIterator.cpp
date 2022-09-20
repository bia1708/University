#include "MultiMapIterator.h"
#include "MultiMap.h"
#include <iostream>

MultiMapIterator::MultiMapIterator(const MultiMap& c): col(c) {
    currentNode = this->col.head;
    if (currentNode != NULL)
        currentVal = currentNode->first;
    else
        currentVal = NULL;
}
/// theta(1)

TElem MultiMapIterator::getCurrent() const{
    if (!valid()){
        exception ex;
        throw ex;
    } else {
        TKey c = currentNode->key;
        TValue v = currentVal->value;
        return make_pair(c, v);
    }
    return NULL_TELEM;
}
/// theta(1)

bool MultiMapIterator::valid() const {
    if(this->col.isEmpty())
        return false;
    if(currentVal!=NULL)
        return true;
//    if(this->currentVal->next == NULL && this->currentNode->next == NULL)
//        return false;
    return false;
}
/// theta(1)

void MultiMapIterator::next() {
    if (!valid()) {
        exception ex;
        throw ex;
    } else if (this->currentVal->next)
        this->currentVal = this->currentVal->next;
    else if(this->currentNode->next) {
        this->currentNode = this->currentNode->next;
        this->currentVal = this->currentNode->first;
    }
    else this->currentVal = NULL;
}
/// theta(1)

void MultiMapIterator::first() {
    currentNode = this->col.head;
    if (currentNode != NULL)
    {
        currentVal = currentNode->first;
    } else
        currentVal = NULL;
}
/// theta(1)

