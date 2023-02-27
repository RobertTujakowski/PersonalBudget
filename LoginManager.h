#ifndef LOGINMANAGER_H
#define LOGINMANAGER_H

#include <iostream>
#include <vector>
#include <windows.h>
#include <fstream>
#include <sstream>

#include "User.h"
#include "UsersFile.h"

using namespace std;

class LoginManager
{
    vector <User> users;
    User getNewUserData();
    int  loggedUserId;
    int  getNewUserId();
    bool isLoginExists(string login);
    UsersFile usersFile;

public:
    LoginManager(string usersFileName) : usersFile(usersFileName)
    {
        loggedUserId = 0;
        users = usersFile.readUsersFromFile();
    }
    bool isUserLogged();
    void userRegistration();
    void userLogin();
    int  getLoggedUserId();
    void logout();
    void changePassword();
};

#endif
