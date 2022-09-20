#pragma once
#include "Domain.h"

typedef struct {
    int length;
    Offer* offers[100];
}Undo;

Undo* createUndo();

void destroyUndo(Undo* undo);

void addOfferUndo(Undo* undo, Offer* o);

void deleteOfferUndo(Undo* undo, Offer* o);

void updateOfferUndo(Undo* undo, Offer* o);