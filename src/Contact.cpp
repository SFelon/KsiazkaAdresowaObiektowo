#include "Contact.h"
#include <iostream>

using namespace std;

Contact::Contact() {;}

Contact::~Contact() {;}

int Contact::getIDNumber() {
    return idNumber;
}
string Contact::getName() {
    return name;
}
string Contact::getSurname(){
    return surname;
}
string Contact::getTelNumber(){
    return telephoneNumber;
}
string Contact::getEmail(){
    return email;
}
string Contact::getAddress(){
    return address;
}

void Contact::setIDNumber(int idn) {
idNumber = idn;
}
void Contact::setName(string n) {
name = n;
}
void Contact::setSurname(string s) {
surname = s;
}
void Contact::setTelNumber(string tn) {
telephoneNumber = tn;
}
void Contact::setEmail(string e) {
email = e;
}
void Contact::setAddress(string a) {
address = a;
}
