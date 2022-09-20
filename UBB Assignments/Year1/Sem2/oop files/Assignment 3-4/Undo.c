#include "Undo.h"
#include "Domain.h"
#include <stdlib.h>
#include <string.h>

Undo* createUndo() {
	Undo* undo = malloc(sizeof(Undo));
    if (undo == NULL)
        return NULL;
    undo->length = 0;
    return undo;
}

void destroyUndo(Undo* undo) {
    if (undo == NULL)
        return;
    for (int i = 0; i < undo->length; i++)
        destroyOffer(undo->offers[i]);
    free(undo);
}

void addOfferUndo(Undo* undo, Offer* o) {

    undo->offers[undo->length] = o;
    undo->offers[undo->length]->id = 1;
    undo->length++;
}

void deleteOfferUndo(Undo* undo, Offer* o) {

    undo->offers[undo->length] = o;
    undo->offers[undo->length]->id = 2;
    undo->length++;

}

void updateOfferUndo(Undo* undo, Offer* o) {

    undo->offers[undo->length] = o;
    undo->offers[undo->length]->id = 3;
    undo->length++;
}
