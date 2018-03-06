#ifndef ADDRESSBOOK_H
#define ADDRESSBOOK_H

#include <iostream>
#include <vector>
#include "Contact.h"

class AddressBook
{
    private:

        string addressBookFileName = "Adresaci.txt";
        vector <Contact> contacts;
        int idLoggedUser;
        int lastIdNumber = 0;

        string intToStringConversion(int number);
        int getlastIdNumber();
        void setlastIdNumber(int idn);
        void showContactData(Contact contact);
        string changeUserDataToLineFormat(Contact contact);

    public:
        AddressBook(int idNumber);
        virtual ~AddressBook();

        void loadAddressBook();
        void addNewContact();
        void findContact();
        void showContacts();
        void changeContactData();
        void eraseContact();

};

#endif // ADDRESSBOOK_H
