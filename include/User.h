#ifndef USER_H
#define USER_H
#include <iostream>

using namespace std;

class User
{
    int id;
    string login;
    string password;

    public:
        User();
        virtual ~User();

       int getID();
       string getLogin();
       string getPassword();

       void setID(int identificator);
       void setLogin(string name);
       void setPassword(string pswrd);
};

#endif // USER_H
