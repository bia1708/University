#include "Domain.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

Offer* createOffer(char* type, char* destination, Date date, int price) {
    Offer* o = malloc(sizeof(Offer));
    if (o == NULL)
        return NULL;

    o->type = malloc(sizeof(char) * (strlen(type) + 1));
    if (o->type != NULL)
        strcpy(o->type, type);

    o->destination = malloc(sizeof(char) * (strlen(destination) + 1));
    if (o->destination != NULL)
        strcpy(o->destination, destination);

    o->date = date;

    o->price = price;

    return o;
}

void destroyOffer(Offer* o) {
    if (o == NULL)
        return;

    // free the memory which was allocated for the component fields
    free(o->type);
    free(o->destination);

    // free the memory which was allocated for the offer structure
    free(o);
}

Offer* copyOffer(Offer* o) {
    return createOffer(o->type, o->destination, o->date, o->price);
}


char* getType(Offer* o) {
    if (o == NULL)
        return NULL;
    return o->type;
}

char* getDestination(Offer* o) {
    if (o == NULL)
        return NULL;
    return o->destination;
}

int getPrice(Offer* o) {
    if (o == NULL)
        return 0;
    return o->price;
}

Date getDate(Offer* o) {
    return o->date;
}

Date stringToDate(char str[]) {
    Date date = {NULL, NULL, NULL};
    char* token;
    token = strtok(str, "-");
    while (token != NULL) {
        if (date.day == NULL)
            date.day = atoi(token);
        else if (date.month == NULL)
            date.month = atoi(token);
        else date.year = atoi(token);
        token = strtok(NULL, "-");
    }
    return date;
}


void toString(Offer* o, char str[]) {
    if (o == NULL)
        return;
    sprintf(str, "Offer Type: %s || Destination: %s || Date: %i-%i-%i || Price: %i\n", o->type, o->destination, o->date.day, o->date.month, o->date.year, o->price);
}
