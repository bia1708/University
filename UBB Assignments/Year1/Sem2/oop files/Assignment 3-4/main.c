#include "OffersRepository.h"
#include "UI.h"
#include <crtdbg.h>

int main() {
	OffersRepo* repo = createRepo();
	Undo* undo = createUndo();
	Undo* redo = createUndo();
	Service* serv = createService(repo, undo, redo);

	testsOfferRepo();
	testsService();

	Date date;
	date.day = 12;
	date.month = 7;
	date.year = 2022;
	addOffer(serv, "seaside", "Turkey", date, 2000, 0);

	date.day = 17;
	date.month = 8;
	date.year = 2022;
	addOffer(serv, "seaside", "Greece", date, 1000, 0);

	date.day = 15;
	date.month = 4;
	date.year = 2023;
	addOffer(serv, "mountain", "Switzerland", date, 3000, 0);

	date.day = 23;
	date.month = 9;
	date.year = 2022;
	addOffer(serv, "city break", "France", date, 2400, 0);

	date.day = 15;
	date.month = 3;
	date.year = 2023;
	addOffer(serv, "city break", "England", date, 3000, 0);

	date.day = 26;
	date.month = 10;
	date.year = 2022;
	addOffer(serv, "seaside", "Italy", date, 1400, 0);

	date.day = 19;
	date.month = 7;
	date.year = 2023;
	addOffer(serv, "seaside", "Bulgary", date, 500, 0);

	date.day = 24;
	date.month = 11;
	date.year = 2024;
	addOffer(serv, "mountain", "Germany", date, 2800, 0);

	date.day = 16;
	date.month = 12;
	date.year = 2022;
	addOffer(serv, "city break", "The Netherlands", date, 4000, 0);

	date.day = 10;
	date.month = 1;
	date.year = 2024;
	addOffer(serv, "mountain", "Austria", date, 5000, 0);


	UI* ui = createUI(serv);

	startUI(ui);

	destroyUI(ui);

	_CrtDumpMemoryLeaks();

	return 0;
}
