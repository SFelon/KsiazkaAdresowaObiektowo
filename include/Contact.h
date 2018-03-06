#ifndef CONTACT_H
#define CONTACT_H

#include <iostream>

using namespace std;

class Contact
{
    int idNumber;
    string name;
    string surname;
    string telephoneNumber;
    string email;
    string address;

    public:
       Contact();
       virtual ~Contact();

       int getIDNumber();
       string getName();
       string getSurname();
       string getTelNumber();
       string getEmail();
       string getAddress();

       void setIDNumber(int idn);
       void setName(string n);
       void setSurname(string s);
       void setTelNumber(string tn);
       void setEmail(string e);
       void setAddress(string a);
};

#endif // CONTACT_H
