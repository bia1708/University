#include "OffersRepository.h"
#include <stdlib.h>
#include <string.h>
#include <assert.h>

OffersRepo* createRepo() {
    OffersRepo* v = malloc(sizeof(OffersRepo));
    if (v == NULL)
        return NULL;
    v->length = 0;

    return v;
}

void destroyRepo(OffersRepo* v) {
    if (v == NULL)
        return;

    for (int i = 0; i < v->length; i++)
        destroyOffer(v->offers[i]);
    free(v);
}

Offer* find(OffersRepo* v, char destination[], Date date) {
    if (v == NULL)
        return NULL;
    // if we find the destination, we return the position in the vector
    for (int i = 0; i < v->length; i++)
        if (strcmp(v->offers[i]->destination, destination) == 0 && v->offers[i]->date.day == date.day && \
            v->offers[i]->date.month == date.month && v->offers[i]->date.year == date.year)
            return v->offers[i];

    return NULL;
}

int add(OffersRepo* v, Offer* o) {
    // if it's already in the vector, we don't add it again
    if (find(v, o->destination, o->date) != NULL)
        return NULL;

    v->offers[v->length] = o;
    v->length++;
    return 1;
}

int update(OffersRepo* v, Offer* o, Offer* new_offer) {
    // if we can't find the offer, we can't update it
    int pos = getPos(v, o->destination, o->date);
    destroyOffer(v->offers[pos]);
    v->offers[pos] = new_offer;
    return 1;
}

int delete(OffersRepo* v, Offer* o) {
    int pos = getPos(v, o->destination, o->date);
    destroyOffer(v->offers[pos]);
    for (int i = pos; i < v->length - 1; i++) {
        //Offer* new_offer = copyOffer(v->offers[i + 1]);
        //Offer* new_offer = createOffer(v->offers[i + 1]->type, v->offers[i + 1]->destination, v->offers[i + 1]->date, v->offers[i + 1]->price);
        v->offers[i] = v->offers[i + 1];
    }
    v->length--;
    
    return 1;
}

int getLength(OffersRepo* v) {
    return v->length;
}

int getPos(OffersRepo* v, char* destination, Date date) {
    if (v == NULL)
        return NULL;

    for (int i = 0; i < v->length; i++)
        if (strcmp(v->offers[i]->destination, destination) == 0 && v->offers[i]->date.day == date.day && \
            v->offers[i]->date.month == date.month && v->offers[i]->date.year == date.year)
            return i;

    return NULL;
}

Offer* getOfferOnPos(OffersRepo* v, int pos) {
    if (v == NULL)
        return NULL;

    if (pos < 0 || pos >= v->length)
        return NULL;
    return v->offers[pos];
}

// ======== TESTS ==========

void initOffersRepoTest(OffersRepo* v) {
    Date date;
    date.day = 17;
    date.month = 8;
    date.year = 2022;
    Offer* o = createOffer("seaside", "Greece", date, 1000);
    add(v, o);
}

void testAdd() {
    OffersRepo* v = createRepo();
    initOffersRepoTest(v);
    assert(getLength(v) == 1);

    Date date;
    date.day = 12;
    date.month = 7;
    date.year = 2022;
    Offer* o = createOffer("seaside", "Turkey", date, 2000);
    assert(add(v, o) == 1);
    assert(getLength(v) == 2);

    assert(add(v, o) == 0);

    destroyRepo(v);
}

void testDelete() {
    OffersRepo* v = createRepo();
    initOffersRepoTest(v);
    assert(getLength(v) == 1);

    Date date;
    date.day = 12;
    date.month = 7;
    date.year = 2022;
    Offer* o = createOffer("seaside", "Turkey", date, 2000);
    assert(add(v, o) == 1);
    assert(delete(v, o) == 1);
    assert(getLength(v) == 1);

    destroyRepo(v);
}

void testUpdate() {
    OffersRepo* v = createRepo();
    initOffersRepoTest(v);
    Date date;
    date.day = 17;
    date.month = 8;
    date.year = 2022;
    Offer* o = createOffer("mountain", "Greece", date, 2500);
    assert(update(v, v->offers[0], o));

    destroyRepo(v);
}

void testsOfferRepo() {
    testAdd();
    testDelete();
    testUpdate();
}


