#pragma once
#include "Domain.h"

typedef struct {
	Offer* offers[100];
	int length;
} OffersRepo;

OffersRepo* createRepo();

void destroyRepo(OffersRepo* v);

Offer* find(OffersRepo* v, char destination[], Date date);

// adds an offer to the repo
int add(OffersRepo* v, Offer* o);

// updates an offer from the repo
int update(OffersRepo* v, Offer* o, Offer* new_offer);

// deletes an existing offer
int delete(OffersRepo* v, Offer* o);

int getLength(OffersRepo* v);

int getPos(OffersRepo* v, char* destination, Date date);

Offer* getOfferOnPos(OffersRepo* v, int pos);

void testsOfferRepo();

