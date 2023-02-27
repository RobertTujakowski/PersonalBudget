#include "UsersFile.h"

vector <User> UsersFile::readUsersFromFile()
{
    User user;
    vector <User> users;

    bool fileExists = xml.Load(USERS_FILE_NAME);

    if (!fileExists)
    {
        xml.SetDoc("<?xml version=\"1.0\" encoding=\"UTF-8\"?>\r\n");
        xml.AddElem("USERS");           // tworzy element glowny (ang. root element)
    }
    else
    {
        xml.FindElem();                 // przechodzi do el "users"
        xml.IntoElem();                 // czyni "users" jako el bierzacy

        while ( xml.FindElem("user") )  // przechodzi do kolejnego elementu "user"
        {
            xml.IntoElem();             // czyni bierzacy element "user" jako glowny

            xml.FindElem("userId");
            user.setId( HelpMethods::convertStringToInt( xml.GetData() ) );

            xml.FindElem("login");
            user.setLogin( xml.GetData() );

            xml.FindElem("password");
            user.setPassword( xml.GetData() );

            xml.FindElem("name");
            user.setName( xml.GetData() );

            xml.FindElem("surname");
            user.setSurname( xml.GetData() );

            xml.OutOfElem();
            users.push_back(user);
        }
    }
    xml.Save(USERS_FILE_NAME);
    return users;
}

void UsersFile::saveUserToFile(User user)
{
    xml.Load(USERS_FILE_NAME);

    xml.FindElem();                 // przechodzi do galezi glownej "USERS"
    xml.IntoElem();                 // czyni galaz glowna jako el bierzacy
    xml.AddElem("user");            // dodaje element na koncu

    xml.IntoElem();
    xml.AddElem("userId"    , user.getId() );
    xml.AddElem("login"     , user.getLogin() );
    xml.AddElem("password"  , user.getPassword() );
    xml.AddElem("name"      , user.getName() );
    xml.AddElem("surname"   , user.getSurname() );
    xml.OutOfElem();

    xml.Save(USERS_FILE_NAME);
}

void UsersFile::changePassword(int loggedUserId, string newPassword, User user )
{
    xml.Load(USERS_FILE_NAME);

    xml.FindElem();                 // przechodzi do galezi glownej "USERS"
    xml.IntoElem();                 // czyni galaz glowna jako el bierzacy

    for (int idNr=1; idNr<=loggedUserId; idNr++) xml.FindElem();
    xml.RemoveElem();

    xml.AddElem("user");
    xml.IntoElem();
    xml.AddElem("userId"    , user.getId() );
    xml.AddElem("login"     , user.getLogin() );
    xml.AddElem("password"  , user.getPassword() );
    xml.AddElem("name"      , user.getName() );
    xml.AddElem("surname"   , user.getSurname() );
    xml.OutOfElem();

    xml.Save(USERS_FILE_NAME);
}
