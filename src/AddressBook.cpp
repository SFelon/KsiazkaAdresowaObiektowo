#include "AddressBook.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <windows.h>

using namespace std;

AddressBook::AddressBook(int idNumber)
{
idLoggedUser = idNumber;
}

AddressBook::~AddressBook() {;}

int AddressBook::getlastIdNumber(){
    return lastIdNumber;
}

void  AddressBook::setlastIdNumber(int idn) {
lastIdNumber = idn;
}

string AddressBook::intToStringConversion(int number) {
    ostringstream ss;
    ss << number;
    string str = ss.str();
    return str;
}

void AddressBook::showContactData(Contact contact)
{
    cout << "ID: "      << contact.getIDNumber()  << endl;
    cout << "Imie: "    << contact.getName()      << endl;
    cout << "Nazwisko: "<< contact.getSurname()   << endl;
    cout << "Nr tel: "  << contact.getTelNumber() << endl;
    cout << "Email: "   << contact.getEmail()     << endl;
    cout << "Adres: "   << contact.getAddress()   << endl << endl;
}

string AddressBook::changeUserDataToLineFormat(Contact contact){
    string dataLine = "";

    dataLine += intToStringConversion(contact.getIDNumber()) + '|';
    dataLine += intToStringConversion(idLoggedUser) + '|';
    dataLine += contact.getName() + '|';
    dataLine += contact.getSurname() + '|';
    dataLine += contact.getTelNumber() + '|';
    dataLine += contact.getEmail() + '|';
    dataLine += contact.getAddress() + '|';

    return dataLine;
}

void AddressBook::loadAddressBook() {
    Contact personToLoad;
    int userIdFromFile;
    string lineToLoad="";
    fstream plik;
    plik.open(addressBookFileName.c_str(), ios::in);

    if(plik.good()==true) {
        while(getline(plik, lineToLoad)) {
            stringstream linestream(lineToLoad);
            string dataToLoad;
            cin.clear(); cin.sync();
                getline(linestream, dataToLoad, '|');
                    personToLoad.setIDNumber(atoi(dataToLoad.c_str()));
                     AddressBook::setlastIdNumber(personToLoad.getIDNumber());
                getline(linestream, dataToLoad, '|');
                    userIdFromFile = atoi(dataToLoad.c_str());
                if (userIdFromFile == idLoggedUser) {
                    getline(linestream, dataToLoad, '|');
                        personToLoad.setName(dataToLoad);
                    getline(linestream, dataToLoad, '|');
                        personToLoad.setSurname(dataToLoad);
                    getline(linestream, dataToLoad, '|');
                        personToLoad.setTelNumber(dataToLoad);
                    getline(linestream, dataToLoad, '|');
                        personToLoad.setEmail(dataToLoad);
                    getline(linestream, dataToLoad, '|');
                        personToLoad.setAddress(dataToLoad);
                    contacts.push_back( personToLoad );
                }
                }
        plik.close();
        return;
    }
}

void AddressBook::addNewContact() {

    Contact newPerson;
    string name, surname, email, telephoneNumber, address;
    cout<<"Podaj imie: "; cin >> name; cin.clear(); cin.sync();
    cout<<"Podaj nazwisko: "; cin >> surname; cin.clear(); cin.sync();
    int i=0;
    while(i < contacts.size()) {
        if(contacts[i].getName() == name && contacts[i].getSurname() == surname) {
            cout << "Kontakt o imieniu "<< name << " i nazwisku " << surname << " juz istnieje." << endl;
            cout << "Podaj nowe dane" << endl;
            cout << "Podaj imie: "; cin >> name; cin.clear();  cin.sync();
            cout << "Podaj nazwisko: "; cin >> surname; cin.clear(); cin.sync();
            i = 0;
        } else
            i++;
    }
    cout<< "Podaj nr telefonu: "; cin >> telephoneNumber; cin.clear(); cin.sync();
    cout<< "Podaj email: "; cin >> email; cin.clear(); cin.sync();
    cout<< "Podaj adres: "; getline(cin,address); cin.clear(); cin.sync();

    newPerson.setIDNumber(getlastIdNumber()+1);
    newPerson.setName(name);
    newPerson.setSurname(surname);
    newPerson.setTelNumber(telephoneNumber);
    newPerson.setEmail(email);
    newPerson.setAddress(address);

    fstream plik;
    plik.open( addressBookFileName.c_str(), ios::out | ios::app );

    if (plik.good() == true) {
    plik << changeUserDataToLineFormat(newPerson) << endl;
    plik.close();
    contacts.push_back(newPerson);
    } else {
        cout << "Nie udalo sie otworzyc pliku i zapisac do niego danych.";
        system("pause");
    }

    cout<<"Dodano nowy kontakt"<<endl;
    Sleep(1000);
}

void AddressBook::findContact() {
    char menuOperation = 0;
    do {
        int numberOfPersonFound = 0;
        string personToFind;
        cout << "Podaj imie lub nazwisko szukanej osoby: ";
        cin >> personToFind; cin.clear(); cin.sync(); cout<<endl;

        vector <Contact> ::iterator it;
        for (it = contacts.begin(); it != contacts.end(); it++) {
        if (it -> getName() == personToFind || it -> getSurname() == personToFind) {
                showContactData(*it);
                numberOfPersonFound++;
            }
        } if(numberOfPersonFound == 0) {
            cout<<"Nie odnaleziono zadnych kontaktow!"<<endl<<endl;
        }
        cout<<"1. Ponow wyszukiwanie"      << endl;
        cout<<"2. Powrot do menu glownego" << endl;
        cout<<"3. Zakoncz program"         << endl;
        cin >> menuOperation; cin.clear(); cin.sync();
        if (menuOperation == '3')
            exit(0);
    } while(menuOperation == '1');
}

void AddressBook::showContacts() {
    if(contacts.empty())
        cout<<"Ksiazka adresowa jest pusta!"<<endl;

    vector <Contact> ::iterator it;
    for (it = contacts.begin(); it != contacts.end(); ++it) {
        showContactData(*it);
    }
    char menuOperation;
    cout << "1. Powrot do menu glownego" << endl;
    cout << "2. Zakoncz program" << endl;
    cin >> menuOperation; cin.clear(); cin.sync();
    if (menuOperation == '2')
        exit(0);
}

void AddressBook::changeContactData() {
char menuOperation = 0;
int idToChange;
int numberOfPersonFound = 0;
string name, surname, email, telephoneNumber, address;

    if(contacts.empty()) {
        cout<<"Ksiazka adresowa jest pusta!"<<endl;
        Sleep(1500);
    } else {
    do {
        cout << "Podaj nr ID osoby, ktorej dane chcesz zmienic: ";
        cin >> idToChange;
        cout << endl;
        vector <Contact> ::iterator it;
        for (it = contacts.begin(); it != contacts.end(); ++it) {
            if (it -> getIDNumber() == idToChange) {
                numberOfPersonFound++;
                showContactData(*it);

                name = contacts[(it - contacts.begin())].getName();
                surname = contacts[(it - contacts.begin())].getSurname();
                telephoneNumber = contacts[(it - contacts.begin())].getTelNumber();
                email = contacts[(it - contacts.begin())].getEmail();
                address = contacts[(it - contacts.begin())].getAddress();

                cout << "Wybierz dane do edycji: "  << endl;
                cout << "1. Imie"                   << endl;
                cout << "2. Nazwisko"               << endl;
                cout << "3. Numer telefonu"         << endl;
                cout << "4. Email"                  << endl;
                cout << "5. Adres"                  << endl;
                cout << "6. Powrot do menu"         << endl;

                char innerMenuOperation = 0;
                cin >> innerMenuOperation; cin.clear(); cin.sync();

                switch (innerMenuOperation) {
                case '1':
                    cout << "Podaj imie: "; cin>>name; cin.clear();  cin.sync(); cout<<endl;
                    break;
                case '2':
                    cout << "Podaj nazwisko: "; cin>>surname; cin.clear(); cin.sync(); cout<<endl;
                    break;
                case '3':
                    cout << "Podaj nr telefonu: "; cin>>telephoneNumber; cin.clear(); cin.sync(); cout<<endl;
                    break;
                case '4':
                    cout << "Podaj email: "; cin>>email; cin.clear(); cin.sync(); cout<<endl;
                    break;
                case '5':
                    cout << "Podaj adres: "; getline(cin,address); cin.clear(); cin.sync(); cout<<endl;
                    break;
                case '6':
                    return;
                    break;
                }

                int idFromFile;
                string lineToLoad = "";

                ifstream plik;
                ofstream temp;
                plik.open(addressBookFileName.c_str());
                temp.open("temp.txt");

                if(plik.good() == true) {
                    while(getline(plik, lineToLoad)) {
                        stringstream linestream(lineToLoad);
                        string dataToLoad;
                        cin.clear();
                        cin.sync();
                        getline(linestream, dataToLoad, '|');
                        idFromFile = atoi(dataToLoad.c_str());
                        if (idToChange != idFromFile)
                            temp << lineToLoad << endl;
                        else if (idToChange == idFromFile) {
                            contacts[(it - contacts.begin())].setIDNumber(idToChange);
                            contacts[(it - contacts.begin())].setName(name);
                            contacts[(it - contacts.begin())].setSurname(surname);
                            contacts[(it - contacts.begin())].setTelNumber(telephoneNumber);
                            contacts[(it - contacts.begin())].setEmail(email);
                            contacts[(it - contacts.begin())].setAddress(address);

                            temp << changeUserDataToLineFormat(contacts[(it - contacts.begin())]) << endl;
                        }
                    }
                    plik.close();
                    temp.close();
                    remove(addressBookFileName.c_str());
                    rename("temp.txt", addressBookFileName.c_str());
                }
               cout<<"Dane zostaly zmienione!" << endl;
               Sleep(1000);
               return;
            }
        } if(numberOfPersonFound == 0) {
            cout<<"Nie odnaleziono kontaktu o wskazanym ID!" << endl << endl;
            cout<<"1. Ponow polecenie"                       << endl;
            cout<<"2. Powrot do menu glownego"               << endl;
            cout<<"3. Zakoncz program"                       << endl;
        }
        cin >> menuOperation; cin.clear(); cin.sync();
        if (menuOperation == '3')
            exit(0);
    }while(menuOperation == '1');
}
}

void AddressBook::eraseContact() {
    int idToErase;
    char menuOperation = 0;
    int numberOfPersonFound = 0;
    vector <Contact> ::iterator it;
    if(contacts.empty()) {
        cout<<"Ksiazka adresowa jest pusta!"<<endl;
        Sleep(1500);
    } else {
    do {
        cout << "Podaj nr ID osoby, ktorej dane chcesz wykasowac: ";
        cin >> idToErase;
        cout << endl;
        for (it = contacts.begin(); it != contacts.end(); ++it) {
        if (it -> getIDNumber() == idToErase) {
                showContactData(*it);
                numberOfPersonFound++;
                break;
        }
        } if (numberOfPersonFound == 0) {
        cout << "Nie odnaleziono kontaktu o wskazanym ID!" << endl << endl;
        Sleep(1000);
        return;
        }
    }while (numberOfPersonFound == 0);

    cout << "Czy na pewno chcesz wykasowac kontakt (t/n): ";
    cin >> menuOperation; cin.clear(); cin.sync();

    if (menuOperation == 't' || menuOperation == 'T') {
        int idFromFile = 0;
        string lineToLoad = "";

        ifstream plik;
        ofstream temp;
        plik.open(addressBookFileName.c_str());
        temp.open("temp.txt");

        if(plik.good() == true) {
        while(getline(plik, lineToLoad)) {
            stringstream linestream(lineToLoad);
            string dataToLoad;
            cin.clear(); cin.sync();
                getline(linestream, dataToLoad, '|');
                idFromFile = atoi(dataToLoad.c_str());
                if (idToErase != idFromFile)
                temp << lineToLoad << endl;
            }
        plik.close();
        temp.close();
        remove(addressBookFileName.c_str());
        rename("temp.txt", addressBookFileName.c_str());

        contacts.erase(contacts.begin()+(it - contacts.begin()));
        cout << "Usunieto kontakt!" << endl;
        Sleep(1000);
        }
    }
}
}
