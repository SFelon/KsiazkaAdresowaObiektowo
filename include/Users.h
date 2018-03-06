#ifndef USERS_H
#define USERS_H
#include "User.h"
#include <iostream>
#include <vector>

using namespace std;

class Users
{
    string userFileName = "Uzytkownicy.txt";
    vector <User> users;
    int idLoggedUser = 0;

    int getNewUserID();
    void saveUserData(User& UserData);

    public:
        Users();
        virtual ~Users();

    int getidLoggedUser();
    void setidLoggedUser(int id);

    void loadUserData();
    void registerNewUser();
    void loginUser();
    void changePassword();
};

#endif // USERS_H
