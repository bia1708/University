#pragma once
#include "AdministratorService.h"
#include "UserService.h"
#include <string>
#include <cstring>

class UI{
private:
    AdminService& adminService;
    UserService& userService;
public:
    UI(AdminService& adminService, UserService& userService);
    void runAdmin();
    void runUser();
    void runApp();
    void uiAdminAdd();
    void uiAdminDelete();
    void uiAdminUpdate();
    void uiAdminList();
    static void printMenuAdmin();
    void uiUserNext();
    void uiUserSave();
    void uiUserInterestList();
    void uiUserFilter();
};

bool isNumber(const std::string& str);
void testAll();