//This is the header file for the ContactList class, containing its class, data member, and member function declarations

#ifndef CONTACTLIST_H
#define CONTACTLIST_H


#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

#include "Contact.h"

using namespace std;

class ContactList{
   public:
      string loadContactsFromFile(string filename);
      int getCount(){return contacts.size();}
      string deleteContact(int contactIdx); 
      string addContact(Contact& new_contact); 
      string sortContacts();

      vector<int> findContactsByName(string target_contact) const;

      void printContacts() const;

      void printContacts(const vector<int>& positions) const;

      Contact* getContact(int idx);
      
   private:
      vector<Contact> contacts;
};

#endif
