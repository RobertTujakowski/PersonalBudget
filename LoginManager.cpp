#include "LoginManager.h"
#include "UsersFile.h"

bool LoginManager::isUserLogged()
{
    if (loggedUserId > 0)
        return true;
    else
        return false;
}

void LoginManager::userRegistration()
{
    User user = getNewUserData();

    users.push_back(user);
    usersFile.saveUserToFile(user);

    cout << endl << "Account successfully created" << endl << endl;
    system("pause");
}

User LoginManager::getNewUserData()
{
    User user;

    user.setId( getNewUserId() );

    string login;
    do
    {
        cout << "Write login: ";
        cin >> login;
        user.setLogin(login);
    }
    while ( isLoginExists(login) == true );

    string password;
    cout << "Write password: ";
    cin >> password;
    user.setPassword(password);

    string name;
    cout << "Write name: ";
    cin >> name;
    user.setName(name);

    string surname;
    cout << "Write surname: ";
    cin >> surname;
    user.setSurname(surname);

    return user;
}

int LoginManager::getNewUserId()
{
    if (users.empty() == true)
        return 1;
    else
        return users.back().getId() + 1;
}

bool LoginManager::isLoginExists(string login)
{
    for (unsigned int i = 0; i < users.size(); i++)
    {
        if (users[i].getLogin() == login)
        {
            cout << endl << "Login already exists." << endl;
            return true;
        }
    }
    return false;
}

void LoginManager::userLogin()
{
    string login = "", password = "";

    cout << endl << "Write login: ";
    login = HelpMethods::readLine();
    vector <User>::iterator itr = users.begin();
    while (itr != users.end())
    {
        if (itr -> getLogin() == login)
        {
            for (int tryNr = 3; tryNr > 0; tryNr--)
            {
                loggedUserId = itr -> getId();
                cout << "Type password. Try left: " << tryNr << ": ";
                password = HelpMethods::readLine();

                if (itr -> getPassword() == password)
                {
                    cout << endl << "You've been logged in." << endl << endl;
                    system("pause");
                    return;
                }
            }
            cout << "You entered wrong password 3 times." << endl;
            loggedUserId = 0;
            system("pause");
            return;
        }
        itr++;
    }
    cout << "There is no user with this password." << endl << endl;
    system("pause");
}

void LoginManager::logout()
{
    loggedUserId = 0;
}

void LoginManager::changePassword()
{
    string newPassword = "";
    cout << "Type a new password: ";
    newPassword = HelpMethods::readLine();

    for (vector <User>::iterator itr = users.begin(); itr != users.end(); itr++)
    {
        if (itr -> getId() == loggedUserId)
        {
            itr -> setPassword(newPassword) ;
            cout << "Password has changed." << endl << endl;
            system("pause");
        }
    }

    usersFile.changePassword( loggedUserId, newPassword, users[loggedUserId-1] );
}

int LoginManager::getLoggedUserId()
{
    return loggedUserId;
}
