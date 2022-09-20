#include <iostream>
#include "UI.h"
using namespace std;

int main()
{
	Repository repository{}, interestList{};

	AdminService adminService{ repository };
	adminService.adminPopulateList();

    UserService userService{ repository, interestList};
	UI ui{ adminService , userService};

	testAll();

	ui.runApp();
	
	return 0;
}

/*
	TODO: clickable links using this code:

	std::string op = std::string("start ").append(link);
	system(op.c_str());
*/