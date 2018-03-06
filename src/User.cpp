#include "User.h"
#include <iostream>

using namespace std;

User::User() {;}

User::~User() {;}

int User::getID() {
    return id;
}
string User::getLogin() {
    return login;
}
string User::getPassword() {
    return password;
}

void User::setID(int identificator) {
    id = identificator;
}
void User::setLogin(string name) {
    login = name;
}
void User::setPassword(string pswrd) {
    password = pswrd;
}
