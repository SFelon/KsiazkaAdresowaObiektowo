#include <iostream>
#include <cstdlib>
#include "Users.h"
#include "AddressBook.h"

using namespace std;

int main()
{
    Users users;
    users.loadUserData();
    char mainMenuOperation;

    while(true) {
    if(users.getidLoggedUser() == 0 ) {
        system("cls");
        cout<<"------------------"<<endl;
        cout<<" KSIAZKA ADRESOWA:"<<endl;
        cout<<"------------------"<<endl;
        cout<<"1. Rejestracja"<<endl;
        cout<<"2. Logowanie"<<endl;
        cout<<"9. Zakoncz Program"<<endl;
        cin >> mainMenuOperation;
        switch(mainMenuOperation) {
        case '1':
            users.registerNewUser();
            system("cls");
            break;
        case '2':
            users.loginUser();
            system("cls");
            break;
        case '9':
            exit(0);
            break;
        }
    } else if (users.getidLoggedUser() > 0) {

    AddressBook contacts(users.getidLoggedUser());
    contacts.loadAddressBook();
    char menuOperation;

        system("cls");
        cout<<"------------------"<<endl;
        cout<<" KSIAZKA ADRESOWA:"<<endl;
        cout<<"------------------"<<endl;
        cout<<"1. Dodaj nowy kontakt"<<endl;
        cout<<"2. Znajdz kontakt"<<endl;
        cout<<"3. Wyswietl kontakty"<<endl;
        cout<<"4. Zmien dane kontaktu"<<endl;
        cout<<"5. Usun kontakt"<<endl;
        cout<<"6. Zmien haslo"<<endl;
        cout<<"7. Wyloguj"<<endl;
        cout<<"8. Zakoncz program"<<endl;
        cin >> menuOperation;
        switch (menuOperation) {
        case '1':
            contacts.addNewContact();
            system("cls");
            break;
        case '2':
            contacts.findContact();
            system("cls");
            break;
        case '3':
            contacts.showContacts();
            system("cls");
            break;
        case '4':
            contacts.changeContactData();
            system("cls");
            break;
        case '5':
            contacts.eraseContact();
            system("cls");
            break;
        case '6':
            users.changePassword();
            system("cls");
            break;
        case '7':
            users.setidLoggedUser(0);
            break;
        case '8':
            exit(0);
        }
    }
    }
    return 0;
}
