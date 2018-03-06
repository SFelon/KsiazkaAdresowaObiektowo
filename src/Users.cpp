#include "Users.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <windows.h>
#include <vector>


Users::Users() {;}

Users::~Users() {;}

int Users::getidLoggedUser() {
    return idLoggedUser;
}

void Users::setidLoggedUser(int id) {
    idLoggedUser = id;
}

////////////////////////////////////////////
int Users::getNewUserID()
{
    if (users.empty() == true)
        return 1;
    else
        return users.back().getID() + 1;
}

////////////////////////////////////////////
void Users::saveUserData(User& UserData)
{
    fstream plik;
    plik.open(userFileName.c_str(), ios::out | ios::app);
       if(plik.good()==true) {
       plik << UserData.getID()  << "|";
       plik << UserData.getLogin() << "|";
       plik << UserData.getPassword() << "|" << endl;
       plik.close();
       } else {
        cout << "Nie udalo sie otworzyc pliku i zapisac do niego danych.";
        system("pause");
       }
}

////////////////////////////////////////////

void Users::loadUserData()
{
    User userToLoad;
    int lastUserIdNumber = 0;
    string lineToLoad="";
    fstream plik;
    plik.open(userFileName.c_str(), ios::in);
    if(plik.good()==true) {
        while(getline(plik, lineToLoad)) {
            stringstream linestream(lineToLoad);
            string dataToLoad;
            cin.clear(); cin.sync();
                getline(linestream, dataToLoad, '|');
                userToLoad.setID(atoi(dataToLoad.c_str()));
                getline(linestream, dataToLoad, '|');
                userToLoad.setLogin(dataToLoad);
                getline(linestream, dataToLoad, '|');
                userToLoad.setPassword(dataToLoad);
                lastUserIdNumber = userToLoad.getID();
                users.push_back(userToLoad);
                }
        plik.close();
    }
}

////////////////////////////////////////////
void Users::registerNewUser()
{
User newUser;
string login, password;
cout << "Podaj nowy login uzytkownika: ";
cin >> login;

vector <User> ::iterator it;
    for (it = users.begin(); it != users.end(); it++) {
        if (it->getLogin() == login) {
            cout << "Podany login jest juz wykorzystany. Wybierz inny: ";
            cin >> login;
        }
    }
cout << "Podaj haslo: ";
cin >> password;

newUser.setID(getNewUserID());
newUser.setLogin(login);
newUser.setPassword(password);
users.push_back(newUser);
saveUserData(newUser);

cout<<"Konto zalozone"<<endl;
Sleep(1000);
}

////////////////////////////////////////////
void Users::loginUser()
{
    string login, password;
    cout << "Podaj login: ";
    cin >> login;
    vector <User> ::iterator it;
    for (it = users.begin(); it != users.end(); it++) {
        if (it->getLogin() == login) {
            for(int j=0; j<3; j++) {
                cout<<"Podaj haslo. Pozostalo prob: "<<3-j<<endl;
                cin >> password;
                if ( users[(it - users.begin())].getPassword() == password ) {
                    cout<<"Zalogowales sie."<<endl;
                    Sleep(1000);
                    idLoggedUser = users[(it - users.begin())].getID();
                    return;
                }
            }
            cout<<"Podales 3 razy bledne haslo. Poczekaj";
            Sleep(3000);
            idLoggedUser = 0;
            return;
        }
    }
    cout<<"Uzytkownik o podanym loginie nie istnieje"<<endl;
    Sleep(1500);
    idLoggedUser = 0;
    return;
}
////////////////////////////////////////////

void Users::changePassword()
{
    string password;
    cout<<"Podaj nowe haslo: ";
    cin >> password;
    vector <User> ::iterator it;
    for (it = users.begin(); it != users.end(); it++) {
        if (it->getID() == idLoggedUser) {

            int idFromFile;
            string lineToLoad = "";

            ifstream plik;
            ofstream temporary;
            plik.open(userFileName.c_str());
            temporary.open("temporary.txt");

            if(plik.good() == true) {
                while(getline(plik, lineToLoad)) {
                    stringstream linestream(lineToLoad);
                    string dataToLoad;
                    cin.clear();
                    cin.sync();
                    getline(linestream, dataToLoad, '|');
                    idFromFile = atoi(dataToLoad.c_str());
                    if (idLoggedUser != idFromFile)
                        temporary << lineToLoad << endl;
                    else if (idLoggedUser == idFromFile) {
                        users[(it - users.begin())].setPassword(password);
                        temporary << (users[(it - users.begin())].getID()) << "|";
                        temporary << (users[(it - users.begin())].getLogin()) << "|";
                        temporary << (users[(it - users.begin())].getPassword()) << "|" << endl;
                    }
                }
                plik.close();
                temporary.close();
                remove(userFileName.c_str());
                rename("temporary.txt", userFileName.c_str());
                cout<<"Haslo zostalo zmienione";
                Sleep(1000);
            } else {
                cout << "Nie udalo sie otworzyc pliku i zapisac do niego danych.";
                system("pause");
            }
        }
    }
}
