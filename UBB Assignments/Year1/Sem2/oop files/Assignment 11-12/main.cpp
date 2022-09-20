#include <iostream>
#include <QApplication>
#include "UI.h"
#include "FileRepository.h"
#include "GUI.h"

using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//	auto* repository = new FileRepository {"events.txt"};
//    auto* interestList = new FileRepository {"wishlist.txt"};
//    void test_sort();
    FileRepository* repository = new FileRepository{R"(C:\Users\PC\Documents\GitHub\a8-9-bia1708\events.txt)"};
    FileRepository* interestList = new FileRepository{R"(C:\Users\PC\Documents\GitHub\a8-9-bia1708\wishlist.txt)"};

	AdminService adminService{ *repository };
//	adminService.adminPopulateList();

    UserService userService{ *repository, interestList};
//	UI ui{ adminService , userService};


//	ui.runApp();
    GUI *gui = new GUI(adminService, userService);
    while (true) {
        std::cout << "1. Administrator mode\n2. User mode\n" << std::endl;
        int login_type;
        std::cin >> login_type;
        if (login_type == 1) {
            gui->init_admin();
        } else if (login_type == 2) {
            std::string output_file_type;
            while (true) {
                std::cout << "Enter the output file type you want (CSV or HTML): ";
                std::cin >> output_file_type;
                try {
                    userService.repositoryType(output_file_type);
                    break;
                } catch (ServiceError &se) {
                    std::cout << se.what() << '\n';
                }
            }
            gui->init_user();
        } else {
            std::cout << "Invalid option\n";
            continue;
        }
        break;
    }
    gui->show();
    return QApplication::exec();
}
