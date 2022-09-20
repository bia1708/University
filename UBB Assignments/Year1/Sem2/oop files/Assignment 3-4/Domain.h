#pragma once

typedef struct {
	int day;
	int month;
	int year;
} Date;

typedef struct {
	char* type;
	char* destination;
	Date date;
	int price;
	int id;
} Offer;

Offer* createOffer(char* type, char* destination, Date date, int price);
void destroyOffer(Offer* o);
Offer* copyOffer(Offer* o);

// getters
char* getType(Offer* o);
char* getDestination(Offer* o);
int getPrice(Offer* o);
Date getDate(Offer* o);

// additional date function
Date stringToDate(char str[]);

// tostr
void toString(Offer* o, char str[]);
