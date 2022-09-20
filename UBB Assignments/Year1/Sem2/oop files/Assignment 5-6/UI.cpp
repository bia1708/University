#include "UI.h"
#include <iostream>
UI::UI(AdminService& adminService, UserService& userService) : adminService{ adminService }, userService{ userService }{}

void UI::runApp()
{
    std::string aplicationMode = "";
    while (1) {
        std::cout << "Choose mode (one of admin/user/x): ";
        std::cin >> aplicationMode;
        if (aplicationMode == "admin")
            runAdmin();
        else if (aplicationMode == "user")
                runUser();
        else if (aplicationMode == "x")
            break;
        else
            std::cout << "Invalid option!\n";
    }
}

void UI::printMenuAdmin() {
    std::cout << "\nMenu:\n";
    std::cout << "1. Add an event.\n";
    std::cout << "2. Update an event.\n";
    std::cout << "3. Delete an event.\n";
    std::cout << "4. List all events.\n";
    std::cout << "5. Change usage rights.\n";
    std::cout << "Press x to exit...\n";
}

void UI::runAdmin() {
    std::cout << "Welcome ADMIN!\n";
    char consoleInput;
    int changeMode = 0;

    printMenuAdmin();

    while (!changeMode) {
        std::cout << "\nInput: ";
        std::cin >> consoleInput;
        if (consoleInput == '1')
            uiAdminAdd();
        else if (consoleInput == '2')
            uiAdminUpdate();
        else if (consoleInput == '3')
            uiAdminDelete();
        else if (consoleInput == '4')
            uiAdminList();
        else if (consoleInput == '5') {
            std::string modeToChange;
            std::cin >> modeToChange;
            if (modeToChange == "user") {
                changeMode = 1;
                runUser();
            }
        }
        else if (consoleInput == 'x')
            break;
        else
            std::cout << "Invalid input! \n";
    }

}

void UI::uiAdminAdd() {
    std::string title, description, link, consoleInput;
    int numberOfPeople;
    Date date{};

    std::cout << "Title: ";
    std::cin.ignore();
    getline(std::cin, consoleInput);
    title = consoleInput.substr(0, consoleInput.size());

    std::cout << "Description: ";
    getline(std::cin, consoleInput);
    description = consoleInput.substr(0, consoleInput.size());

    std::cout << "Day: ";
    getline(std::cin, consoleInput);
    if (!isNumber(consoleInput)) {
        std::cout << "Please enter a number!";
        return;
    }
    date.day = stoi(consoleInput.substr(0));

    std::cout << "Month: ";
    getline(std::cin, consoleInput);
    if (!isNumber(consoleInput)) {
        std::cout << "Please enter a number!";
        return;
    }
    date.month = stoi(consoleInput.substr(0));

    std::cout << "Year: ";
    getline(std::cin, consoleInput);
    if (!isNumber(consoleInput)) {
        std::cout << "Please enter a number!";
        return;
    }
    date.year = stoi(consoleInput.substr(0));

    std::cout << "Hour: ";
    getline(std::cin, consoleInput);
    if (!isNumber(consoleInput)) {
        std::cout << "Please enter a number!";
        return;
    }
    date.hour = stoi(consoleInput.substr(0));

    std::cout << "Minute: ";
    getline(std::cin, consoleInput);
    if (!isNumber(consoleInput)) {
        std::cout << "Please enter a number!";
        return;
    }
    date.minute = stoi(consoleInput.substr(0));

    std::cout << "Number of people: ";
    std::cin >> consoleInput;
    if (!isNumber(consoleInput)) {
        std::cout << "Please enter a number!";
        return;
    }
    numberOfPeople = stoi(consoleInput.substr(0));

    std::cout << "Link: ";
    std::cin >> consoleInput;
    link = consoleInput;

    int isFunctionSuccessful = adminService.adminAddEvent(title, description, date, numberOfPeople, link);
    
    if (isFunctionSuccessful == -1) {
        std::cout << "Event already in the list!\n";
    }
}

void UI::uiAdminDelete()
{
    std::string title, consoleInput;
    std::cout << "Title: ";
    std::cin.ignore();
    std::getline(std::cin, consoleInput);
    title = consoleInput;
    int isFunctionSuccessful = adminService.adminDeleteEvent(title);
    if (isFunctionSuccessful == -1) {
        std::cout << "Event is not in the list!\n";
    }
}

void UI::uiAdminUpdate()
{
    std::string title, description, link, consoleInput;
    int numberOfPeople;
    Date date{};

    std::cout << "Title: ";
    std::cin.ignore();
    getline(std::cin, consoleInput);
    title = consoleInput.substr(0, consoleInput.size());

    std::cout << "Description: ";
    getline(std::cin, consoleInput);
    description = consoleInput.substr(0, consoleInput.size());

    std::cout << "Day: ";
    getline(std::cin, consoleInput);
    if (!isNumber(consoleInput)) {
        std::cout << "Please enter a number!";
        return;
    }
    date.day = stoi(consoleInput.substr(0));

    std::cout << "Month: ";
    getline(std::cin, consoleInput);
    if (!isNumber(consoleInput)) {
        std::cout << "Please enter a number!";
        return;
    }
    date.month = stoi(consoleInput.substr(0));

    std::cout << "Year: ";
    getline(std::cin, consoleInput);
    if (!isNumber(consoleInput)) {
        std::cout << "Please enter a number!";
        return;
    }
    date.year = stoi(consoleInput.substr(0));

    std::cout << "Hour: ";
    getline(std::cin, consoleInput);
    if (!isNumber(consoleInput)) {
        std::cout << "Please enter a number!";
        return;
    }
    date.hour = stoi(consoleInput.substr(0));

    std::cout << "Minute: ";
    getline(std::cin, consoleInput);
    if (!isNumber(consoleInput)) {
        std::cout << "Please enter a number!";
        return;
    }
    date.minute = stoi(consoleInput.substr(0));

    std::cout << "Number of people: ";
    std::cin >> consoleInput;
    if (!isNumber(consoleInput)) {
        std::cout << "Please enter a number!";
        return;
    }
    numberOfPeople = stoi(consoleInput.substr(0));

    std::cout << "Link: ";
    std::cin >> consoleInput;
    link = consoleInput;

    int isFunctionSuccessful = adminService.adminUpdateEvent(title, description, date, numberOfPeople, link);

    if (isFunctionSuccessful == -1) {
        std::cout << "Event is not in the list!\n";
    }
}

void UI::uiAdminList()
{
    DynamicVector<Event> listOfEvents = adminService.adminGetEventList();
    for (int i = 0; i < listOfEvents.getSize(); i++)
        std::cout << listOfEvents[i].getOutputFormat() << '\n';
}

void userPrintMenu() {
    std::cout << "\nMenu:\n";
    std::cout << "1. See events in a certain month.\n";
    std::cout << "2. See interest list..\n";
    std::cout << "3. Delete an event from the interests list.\n";
    std::cout << "4. Change usage rights.\n";
    std::cout << "Press x to exit...\n";
}

void UI::runUser() {
    std::cout << "Mode changed!\n";
    userPrintMenu();
    std::string consoleInput;
    int changeMode = 0;
    int listLoop = 0;
    while (!changeMode && !listLoop) {
        std::cout << "Input: ";
        std::cin >> consoleInput;
        if (consoleInput == "1") {
            uiUserFilter();
            listLoop = 1;
        }
        else if (consoleInput == "4") {
            std::string modeToChange;
            std::cout << "Choose mode (one of admin/user/x): ";
            std::cin >> modeToChange;
            if (modeToChange == "admin") {
                changeMode = 1;
                runAdmin();
            }
        }
        else if (consoleInput == "3") {
            std::string title;
            std::cout << "Please enter the title: ";
            std::cin >> title;
            if (userService.deleteInterest(title) == 1)
                std::cout << "Event deleted successfully!\n";
            else std::cout << "Event not in your interest list!\n";
        }
//        else if (consoleInput == "next") {
//            Event currentEvent = userService.getCurrentEvent();
//            std::cout << currentEvent.getOutputFormat();
//            uiUserNext();
//        }
        else if (consoleInput == "2")
            uiUserInterestList();
        else if (consoleInput == "save")
            uiUserSave();
        else if (consoleInput == "x")
            break;
        else
            std::cout << "Invalid input! \n";
    }
}

void UI::uiUserInterestList()
{
    for (int i = 0; i < userService.getInterests().getSize(); i++)
        std::cout << userService.getInterests()[i].getOutputFormat() << '\n';
}

void UI::uiUserNext() {
    userService.goToNextEvent();
}

void UI::uiUserSave(){
    int isFunctionSuccessful = userService.addInterest(userService.getCurrentEvent());
    if (isFunctionSuccessful == -1)
        std::cout << "Invalid event!\n";
}

void UI::uiUserFilter() {
    std::string consoleInput;
    int month;
    Event currentEvent;
    std::cout << "Please enter the month(press enter to get all events): ";
    std::cin >> consoleInput;
    if (consoleInput.length() == 0)
        month = 0;
    else {
        month = std::stoi(consoleInput);
        if (month > 12)
            month = 0;
    }

    int isFunctionSuccessful = userService.filterByMonth(month);
    if (isFunctionSuccessful == -1)
        std::cout << "No events held this month!\n";

    while (isFunctionSuccessful != -1) {
        try {
            currentEvent = userService.getCurrentEvent();
        }
        catch (std::exception &Exception) {
            std::cout << Exception.what() << '\n';
        }
        std::cout << currentEvent.getOutputFormat() << '\n';

        /// ============
//        std::string op = std::string("start ").append(currentEvent.getLink());
//        system(op.c_str());
        /// ============

        std::cout << "Input (add / next / x): ";
        std::cin >> consoleInput;
        if (consoleInput == "add") {
            uiUserSave();
            uiUserNext();
        }
        else if (consoleInput == "next")
            uiUserNext();
        else if (consoleInput == "x")
            break;
        else
            std::cout << "Invalid option\n";
    }
}

void testAll() {
    testDomain();
    testRepository();
    testAdminService();
    testUserService();
}

bool isNumber(const std::string& str)
{
    for (char const& c : str) {
        if (std::isdigit(c) == 0) return false;
    }
    return true;
}