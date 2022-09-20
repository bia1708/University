#include "Service.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>


Service* createService(OffersRepo* r, Undo* undo, Undo* redo)
{
	Service* s = malloc(sizeof(Service));
	if (s == NULL)
		return NULL;
	s->repo = r;
	s->undo = undo;
	s->redo = redo;

	return s;
}

void destroyService(Service* s)
{
	if (s == NULL)
		return;

	// first we destroy the repository inside
	destroyUndo(s->redo);
	destroyUndo(s->undo);
	destroyRepo(s->repo);
	// then free the memory
	free(s);
}

int addOffer(Service* s, char type[], char destination[], Date date, int price, int make_undo)
{	
	Offer* o = createOffer(type, destination, date, price);

	int res = add(s->repo, o);
	// if the offer was not added - destroy it 
	if (res == 0)
		destroyOffer(o);
	if(make_undo)
		deleteOfferUndo(s->undo, copyOffer(o));
	return res;
}

int updateOffer(Service* s, char destination[], Date date, char new_type[], int new_price, int make_undo) {
	Offer* o = createOffer(new_type, destination, date, new_price);
	Offer* old_offer = find(s->repo, destination, date);
	int res;
	if (old_offer == NULL)
		res = 0;
	else {
		if(make_undo)
			updateOfferUndo(s->undo, copyOffer(old_offer));
		res = update(s->repo, old_offer, o);
	}
	return res;
}

int deleteOffer(Service* s, char destination[], Date date, int make_undo) {
	int res;
	Offer* o = find(s->repo, destination, date);
	if (o == NULL)
		res = 0;
	else {
		if (make_undo) {
			Offer* copy_o = copyOffer(o);
			addOfferUndo(s->undo, copy_o);
		}
		res = delete(s->repo, o);
	}
	return res;
}

OffersRepo* getRepo(Service* s)
{
	return s->repo;
}

OffersRepo* sortByPrice(OffersRepo* res) {
	for(int i = 0; i < res->length - 1; i++)
		for(int j = i + 1; j < res->length; j++)
			if (res->offers[i] < res->offers[j]) {
				Offer* aux = res->offers[i];
				res->offers[i] = res->offers[j];
				res->offers[j] = aux;
			}
	return res;
}

OffersRepo* filterByDestination(Service* s, char destination[])
{
	OffersRepo* res = createRepo();

	// if a destination is not provided, we copy all of the elements from s->repo to res
	// otherwise, we add all matching elements
	if (strcmp(destination, "none") == 0)
	{
		res->length = s->repo->length;
		for (int i = 0; i < s->repo->length; i++) {
			Offer* new_offer = createOffer(s->repo->offers[i]->type, s->repo->offers[i]->destination, \
				s->repo->offers[i]->date, s->repo->offers[i]->price);
			res->offers[i] = new_offer;
		}
	}
	else for (int i = 0; i < s->repo->length; i++)
		if (strcmp(destination, s->repo->offers[i]->destination) == 0) {
			Offer* new_offer = createOffer(s->repo->offers[i]->type, s->repo->offers[i]->destination, \
				s->repo->offers[i]->date, s->repo->offers[i]->price);
			res->offers[res->length] = new_offer;
			res->length++;
		}

	// we sort the results in ascending order of the prices
	res = sortByPrice(res);
	return res;
}

OffersRepo* filterByTypeAndDate(Service* s, char type[], Date date) {
	OffersRepo* res = createRepo();
	for (int i = 0; i < s->repo->length; i++)
		if (strcmp(type, s->repo->offers[i]->type) == 0 && compareDates(date, s->repo->offers[i]->date) == 1) {
			Offer* new_offer = createOffer(s->repo->offers[i]->type, s->repo->offers[i]->destination, \
				s->repo->offers[i]->date, s->repo->offers[i]->price);
			res->offers[res->length] = new_offer;
			res->length++;
		}
	return res;
}

int compareDates(Date date1, Date date2) {
	if (date1.year < date2.year || (date1.year == date2.year && date1.month < date2.month) || \
		(date1.year == date2.year && date1.month == date2.month && date1.day < date2.day))
		return 1;
	return 0;
}

int undo(Service* s) {
	if (s->undo->length == 0)
		return 0;
	if (s->undo->offers[s->undo->length - 1]->id == 1) {
		Offer* o = copyOffer(s->undo->offers[s->undo->length - 1]);
		deleteOfferUndo(s->redo, o);
		addOffer(s, o->type, o->destination, o->date, o->price, 0);
		destroyOffer(s->undo->offers[s->undo->length - 1]);
		s->undo->length--;
		return 1;
	}
	if (s->undo->offers[s->undo->length - 1]->id == 2) {
		Offer* o = copyOffer(s->undo->offers[s->undo->length - 1]);
		addOfferUndo(s->redo, o);
		deleteOffer(s, s->undo->offers[s->undo->length - 1]->destination, s->undo->offers[s->undo->length - 1]->date, 0);
		destroyOffer(s->undo->offers[s->undo->length - 1]);
		s->undo->length--;
		return 1;
	}
	if (s->undo->offers[s->undo->length - 1]->id == 3) {
		Offer* o = find(s->repo, s->undo->offers[s->undo->length - 1]->destination, s->undo->offers[s->undo->length - 1]->date);
		Offer* new_offer1 = copyOffer(s->undo->offers[s->undo->length - 1]);
		Offer* new_offer2 = copyOffer(o);
		updateOfferUndo(s->redo, new_offer2);
		updateOffer(s, s->undo->offers[s->undo->length - 1]->destination, s->undo->offers[s->undo->length - 1]->date, \
			new_offer1->type, new_offer1->price, 0);
		destroyOffer(new_offer1);
		destroyOffer(s->undo->offers[s->undo->length - 1]);
		s->undo->length--;
		return 1;
	}
}

int redo(Service* s) {

	if (s->redo->length == 0)
		return 0;

	if (s->redo->offers[s->redo->length - 1]->id == 1) {
		deleteOfferUndo(s->undo, copyOffer(s->redo->offers[s->redo->length - 1]));
		addOffer(s, s->redo->offers[s->redo->length - 1]->type, s->redo->offers[s->redo->length - 1]->destination, s->redo->offers[s->redo->length - 1]->date, s->redo->offers[s->redo->length - 1]->price, 0);
		destroyOffer(s->redo->offers[s->redo->length - 1]);
		s->redo->length--;
		return 1;
	}
	if (s->redo->offers[s->redo->length - 1]->id == 2) {
		addOfferUndo(s->undo, copyOffer(s->redo->offers[s->redo->length - 1]));
		deleteOffer(s, s->redo->offers[s->redo->length - 1]->destination, s->redo->offers[s->redo->length - 1]->date, 0);
		destroyOffer(s->redo->offers[s->redo->length - 1]);
		s->redo->length--;
		return 1;
	}
	if (s->redo->offers[s->redo->length - 1]->id == 3) {
		Offer* o = find(s->repo, s->redo->offers[s->redo->length - 1]->destination, s->redo->offers[s->redo->length - 1]->date);
		Offer* new_offer1 = copyOffer(s->redo->offers[s->redo->length - 1]);
		Offer* new_offer2 = copyOffer(o);
		updateOffer(s, new_offer1->destination, new_offer1->date, new_offer1->type, new_offer1->price, 0);
		destroyOffer(new_offer1);
		updateOfferUndo(s->undo, new_offer2);
		destroyOffer(s->redo->offers[s->redo->length - 1]);
		s->redo->length--;
		return 1;
	}
}

// =========== TESTS ===========

void initOffersServiceTest(OffersRepo* v) {
	Date date;
	date.day = 17;
	date.month = 8;
	date.year = 2022;
	Offer* o = createOffer("seaside", "Greece", date, 1000);
	add(v, o);
}

void testAddOffer() {
	OffersRepo* v = createRepo();
	OffersRepo* undo = createRepo();
	OffersRepo* redo = createRepo();
	//Service* s = createService(v, undo, redo);

	initOffersServiceTest(v);

	Date date;
	date.day = 12;
	date.month = 7;
	date.year = 2022;
	Offer* o = createOffer("mountain", "Albania", date, 1400);
	assert(add(v, o));

	assert(getLength(v) == 2);

	destroyRepo(v);
	destroyRepo(undo);
	destroyRepo(redo);
}

void testDeleteOffer(){
	OffersRepo* v = createRepo();
	OffersRepo* undo = createRepo();
	OffersRepo* redo = createRepo();
	//Service* s = createService(v, undo, redo);

	initOffersServiceTest(v);

	Date date;
	date.day = 17;
	date.month = 8;
	date.year = 2022;
	Offer* o = createOffer("seaside", "Turkey", date, 2000);
	assert(add(v, o) == 1);
	assert(delete(v, o) == 1);
	assert(getLength(v) == 1);
	destroyRepo(v);
	destroyRepo(undo);
	destroyRepo(redo);
}

void testUpdateOffer() {
	OffersRepo* v = createRepo();
	OffersRepo* undo = createRepo();
	OffersRepo* redo = createRepo();
	//Service* s = createService(v, undo, redo);

	initOffersServiceTest(v);

	Date date;
	date.day = 17;
	date.month = 8;
	date.year = 2022;
	Offer* o = createOffer("mountain", "Greece", date, 2500);
	assert(update(v, v->offers[0], o));
	destroyRepo(v);
	destroyRepo(undo);
	destroyRepo(redo);
}

void testsService() {
	testAddOffer();
	testDeleteOffer();
	testUpdateOffer();
}