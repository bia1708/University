#include "UI.h"
#include <stdio.h>
#include <stdlib.h>

UI* createUI(Service* s)
{
	UI* ui = malloc(sizeof(UI));
	if (ui == NULL)
		return NULL;
	ui->serv = s;

	return ui;
}

void destroyUI(UI* ui)
{
	if (ui == NULL)
		return;

	// first destroy the Service
	destroyService(ui->serv);
	// free the UI memory
	free(ui);
}

void printMenu()
{
	printf("\n**********************************************************\n");
	printf("1 - Add an offer.\n");
	printf("2 - List all offers.\n");
	printf("3 - List offers with a given destination.\n");
	printf("4 - Update an existing offer.\n");
	printf("5 - Delete an existing offer.\n");
	printf("6 - List offers of a given type after a given date.\n");
	printf("7- Undo.\n");
	printf("8- Redo.\n");
	printf("0 - to exit.\n");
	printf("**********************************************************\n");
}

int validCommand(int command)
{
	if (command >= 0 && command <= 8)
		return 1;
	return 0;
}

/*
	Reads an integer number from the keyboard. Asks for number while read errors encoutered.
	Input: the message to be displayed when asking the user for input.
	Returns the number.
*/
int readIntegerNumber(const char* message)
{
	char s[16] = { 0 };
	int res = 0;
	int flag = 0;
	int r = 0;

	while (flag == 0)
	{
		printf(message);
		int scanf_result = scanf("%15s", s);

		r = sscanf(s, "%d", &res);	// reads data from s and stores them as integer, if possible; returns 1 if successful
		flag = (r == 1);
		if (flag == 0)
			printf("Error reading number!\n");
	}
	return res;
}

int addOfferUI(UI* ui)
{
	// read the offer's data
	char destination[50], type[50], date_string[50];
	Date date;
	int price = 0;

	printf("Please input the type(one of seaside, mountain or city break): ");
	int scanf_result = scanf(" %[^\n]", type);
	if (strcmp(type, "seaside") != 0 && strcmp(type, "mountain") != 0 && strcmp(type, "city break") != 0)
		return 2;
	printf("Please input the destination: ");
	scanf_result = scanf("%49s", destination);
	printf("Please input the date(format: DD-MM-YYYY): ");
	scanf_result = scanf("%49s", date_string);
	date = stringToDate(date_string);
	printf("Please input the price(in euro): ");
	scanf_result = scanf("%i", &price);

	return addOffer(ui->serv, type, destination, date, price, 1);
}

int updateOfferUI(UI* ui) {
	char destination[50], date_string[50], type[50];
	Date date;
	int price = 0;

	printf("Which offer would you like to update?\nDestination: ");
	int scanf_result = scanf("%49s", destination);
	printf("Date: ");
	scanf_result = scanf("%49s", date_string);
	date = stringToDate(date_string);

	printf("Updated type: ");
	scanf_result = scanf(" %[^\n]", type);
	if (strcmp(type, "seaside") != 0 && strcmp(type, "mountain") != 0 && strcmp(type, "city break") != 0)
		return 2;
	printf("Updated price: ");
	scanf_result = scanf("%i", &price);

	return updateOffer(ui->serv, destination, date, type, price, 1);
}

int deleteOfferUI(UI* ui) {
	char destination[50], date_string[50];
	Date date;

	printf("Which offer would you like to delete?\nDestination: ");
	int scanf_result = scanf("%49s", destination);
	printf("Date: ");
	scanf_result = scanf("%49s", date_string);
	date = stringToDate(date_string);

	return deleteOffer(ui->serv, destination, date, 1);
}

void listAllOffers(UI* ui)
{
	if (ui == NULL)
		return;
	OffersRepo* repo = getRepo(ui->serv);
	if (repo == NULL)
		return;

	for (int i = 0; i < getLength(repo); i++)
	{
		Offer* offer = getOfferOnPos(repo, i);
		char offerString[200];
		toString(offer, offerString);
		printf("%s\n", offerString);
	}
}

void listOffersByDestination(UI* ui)
{
	char symbols[50];
	printf("Please input the destination; input 'none' for all destinations: ");
	int scanf_result = scanf("%49s", symbols);

	OffersRepo* res = filterByDestination(ui->serv, symbols);

	for (int i = 0; i < getLength(res); i++)
	{
		Offer* offer = getOfferOnPos(res, i);
		char offerString[200];
		toString(offer, offerString);
		printf("%s\n", offerString);
	}

	// now we must destroy the repository that was created for this operation
	destroyRepo(res);
}

void listOffersByTypeAndDate(UI* ui) {
	char symbols[50], date_string[50];
	printf("Please input the type: ");
	int scanf_result = scanf("%49s", symbols);

	Date date;
	printf("Date: ");
	scanf_result = scanf("%49s", date_string);
	date = stringToDate(date_string);

	OffersRepo* res = filterByTypeAndDate(ui->serv, symbols, date);

	printf("\n");
	for (int i = 0; i < getLength(res); i++)
	{
		Offer* offer = getOfferOnPos(res, i);
		char offerString[200];
		toString(offer, offerString);
		printf("%s\n", offerString);
	}

	destroyRepo(res);
}

void undo_ui(UI* ui) {
	if (undo(ui->serv) == 0)
		printf("You can't undo anymore! \n");
	else printf("\nUndo successful!\n");
}

void redo_ui(UI* ui) {
	if (redo(ui->serv) == 0)
		printf("You can't redo anymore! \n");
	else printf("\nRedo successful!\n");
}


void startUI(UI* ui)
{
	while (1)
	{
		printMenu();
		int command = readIntegerNumber("Input command: ");
		while (validCommand(command) == 0)
		{
			printf("Please input a valid command!\n");
			command = readIntegerNumber("Input command: ");
		}
		if (command == 0)
			break;
		switch (command)
		{
		case 1:
		{
			int res = addOfferUI(ui);
			if (res == 1)
				printf("Offer successfully added.\n");
			else if (res == 2)
				printf("Please use one of the specified types!\n");
			else
				printf("Error! Offer could not be added, as there is another offer with the same destination and date!\n");
			break;
		}
		case 2:
		{
			printf("\n");
			listAllOffers(ui);
			break;
		}
		case 3:
		{
			listOffersByDestination(ui);
			break;
		}
		case 4:
		{
			int res = updateOfferUI(ui);
			if (res == 1)
				printf("Offer updated successfully.\n");
			else if (res == 2)
				printf("Please use one of the specified types!\n");
			else
				printf("Error! Offer does not exist!\n");
			break;
		}
		case 5:
		{
			int res = deleteOfferUI(ui);
			if (res == 1)
				printf("Offer deleted successfully.\n");
			else
				printf("Error! Offer does not exist!\n");
			break;
		}
		case 6:
		{
			listOffersByTypeAndDate(ui);
			break;
		}
		case 7:
		{
			undo_ui(ui);
			break;
		}
		case 8:
		{
			redo_ui(ui);
			break;
		}
		}
	}
}