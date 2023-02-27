#ifndef USERSFILE_H
#define USERSFILE_H

#include <iostream>
#include <vector>
#include <fstream>
#include "Markup.h"

#include "User.h"
#include "HelpMethods.h"

using namespace std;

class UsersFile
{
    const string USERS_FILE_NAME;
    CMarkup xml;

    User getUserData();

public:
    UsersFile(string usersFileName) : USERS_FILE_NAME(usersFileName){};

    void   saveUserToFile(User user);
    vector <User> readUsersFromFile();

    void changePassword(int loggedUserId, string newPassword, User user );
};

#endif
