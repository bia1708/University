#pragma once

#include "OffersRepository.h"
#include "Undo.h"

typedef struct
{
	OffersRepo* repo;
	Undo* undo;
	Undo* redo;
} Service;

Service* createService(OffersRepo* r, Undo* undo, Undo* redo);

void destroyService(Service* s);

// adds an offer to the repo, throws exception if not possible
int addOffer(Service* s, char type[], char destination[], Date date, int price, int make_undo);

// updates an offer from the repo, throws exception if not possible
int updateOffer(Service* s, char destination[], Date date, char new_type[], int new_price, int make_undo);

// deletes an offer from the repo, throws exception if not possible
int deleteOffer(Service* s, char destination[], Date date, int make_undo);

OffersRepo* getRepo(Service* s);

// filters the offers by destination and returns a repo containing these offers
OffersRepo* filterByDestination(Service* s, char type[]);

// filters the offers by type and date and returns a repo containing these offers
OffersRepo* filterByTypeAndDate(Service* s, char type[], Date date);

int compareDates(Date date1, Date date2);

int undo(Service* s);

void testsService();
