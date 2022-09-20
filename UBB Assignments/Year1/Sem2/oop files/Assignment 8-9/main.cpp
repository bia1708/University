#include <iostream>
#include "UI.h"
#include "FileRepository.h"

using namespace std;

int main()
{
//	auto* repository = new FileRepository {"events.txt"};
//    auto* interestList = new FileRepository {"wishlist.txt"};
    void test_sort();
    FileRepository* repository = new FileRepository{R"(C:\Users\PC\Documents\GitHub\a8-9-bia1708\events.txt)"};
    FileRepository* interestList = new FileRepository{R"(C:\Users\PC\Documents\GitHub\a8-9-bia1708\wishlist.txt)"};

	AdminService adminService{ *repository };
//	adminService.adminPopulateList();

    UserService userService{ *repository, interestList};
	UI ui{ adminService , userService};


	ui.runApp();
	
	return 0;
}
