#include "MultiMap.h"
#include "MultiMapIterator.h"
#include <exception>
#include <iostream>

using namespace std;


MultiMap::MultiMap(): head(NULL) {}


void MultiMap::add(TKey c, TValue v) {
    // if the map is empty, we don't have to search for the key
	if (isEmpty()){
        // we create the first node for the first key
        MapNode* newNode = new MapNode();
        newNode->next = NULL;
        newNode->key = c;

        // we create a values SLL for the first key
        ValuesNode* newValue = new ValuesNode();
        newNode->first = newValue; // we map the values SLL to the key
        newValue->next = NULL;
        newValue->value = v;

        head = newNode;
    } else {
        // first we have to search for the key in the map SLL
        MapNode* node = head;
        bool existingKey = false;
        while(node != NULL)
            if (node->key == c){
                existingKey = true;
                ValuesNode* vNode = new ValuesNode(); // create a new value node
                ValuesNode* current = node->first;
                while(current->next != NULL)
                    current = current->next;
                current->next = vNode; // we add it to the values SLL
                vNode->value = v;
                vNode->next = NULL;
                break;
            } else node = node->next;
        node = head;
        if (!existingKey){
            // if the key doesn't exist, we add it to the end of the map SLL
            while(node->next != NULL)
                node = node->next;
            MapNode* newNode = new MapNode();
            node->next = newNode;
            newNode->next = NULL;
            newNode->key = c;
            ValuesNode* vNode = new ValuesNode();
            vNode->value = v;
            vNode->next = NULL;
            newNode->first = vNode;
        }
    }
    this->length++;
}
/// BC: the list is empty => theta(1)
/// WC: the key and value are the last in the SLL => theta(len(MapNode) + len(ValuesNode))
/// AC: theta(len(MapNode) + len(ValuesNode))


bool MultiMap::remove(TKey c, TValue v) {
	MapNode* node = head;
    bool found = false;
    while(node != NULL){
        // we search for the key
        if(node->key == c){
            // if we find the key, next we search for the value
            ValuesNode* vNode = node->first;
            if(vNode->next == NULL) {
                if (vNode->value == v) {
                    // if it's the only value in the list, we have to delete the key as well
                    if (head == node) {
                        delete vNode;
                        head = head->next;
                        delete node;
                        this->length--;
                        return true;
                    }
                    // we need to link the previous node to the one after the deleted node
                    MapNode *prevNode = head;
                    while (prevNode->next != node)
                        prevNode = prevNode->next;
                    prevNode->next = node->next;
                    delete vNode;
                    delete node;
                    this->length--;
                    return true;
                } else return false;
            } else {
                if (vNode->value == v){
                    // if it's the first node we don't need the previous ones
                    node->first = vNode->next;
                    delete vNode;
                    this->length--;
                    return true;
                } else {
                    ValuesNode* prevNode = vNode;
                    vNode = vNode->next;
                    while(vNode != NULL){
                        if(vNode->value == v){
                            prevNode->next = vNode->next;
                            delete vNode;
                            this->length--;
                            return true;
                        } else {
                            prevNode = vNode;
                            vNode = vNode->next;
                        }
                    }
                    break;
                }
            }
        } else node = node->next;
    }
	return  false;
}
/// BC: the key-value pair is the first one in the SLL => theta(1)
/// WC: the key-value pair is the last one in the SLL => theta(len(MapNode) * len(ValuesNode))
/// AC: theta(len(MapNode) * len(ValuesNode))


vector<TValue> MultiMap::search(TKey c) const {
	std::vector<TValue> values;
    MapNode* node = head;
    while(node != NULL){
        if(node->key == c){
            // if we found the key, we populate the vector with the values corresponding to the key
            ValuesNode* vNode = node->first;
            while(vNode != NULL){
                values.push_back(vNode->value);
                vNode = vNode->next;
            }
            break;
        } else node = node->next;
    }

    // if the key isn't found, the vector will be empty
    return values;
}
/// BC: the key is the first one in the list => theta(numberOfValues)
/// WC: the key is the last one in the list => theta(numberOfKeys + numberOfValues)
/// AC: theta(numberOfValues)

int MultiMap::size() const {
    return this->length;
	return 0;
}
/// theta(!)


bool MultiMap::isEmpty() const {
	if (this->head == NULL)
        return true;
	return false;
}
/// theta(1)

MultiMapIterator MultiMap::iterator() const {
	return MultiMapIterator(*this);
}
/// theta(1)

MultiMap::~MultiMap() {
    if(!isEmpty()){
        MapNode* currentNode = this->head;
        ValuesNode* currentValue = NULL;
        while (currentNode != NULL){
            currentValue = currentNode->first;
            while (currentValue != NULL)
            {
                currentNode->first = currentValue->next;
                delete currentValue;
                currentValue = currentNode->first;
            }
            currentNode = currentNode->next;
        }
        currentNode = this->head;
        while (currentNode != NULL)
        {
            this->head = currentNode->next;
            delete currentNode;
            currentNode = this->head;
        }
    }
}
/// BC: the map is empty => theta(1)
/// WC: theta(len(MapNode) + len(ValuesNode))
/// AC: theta(len(MapNode) + len(ValuesNode))

