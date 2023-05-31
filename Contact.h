//This is the header file for the Contact class, containing its class, data member, and member function declarations

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;


#ifndef CONTACT_H
#define CONTACT_H

struct PhoneNumbers{
   char phoneType;
   string phone_number;
};

class Contact{
   public:
      Contact();
      Contact(char contact_type, string first_name, string last_name);
      Contact(string phone, string cell, char contact_type);

      string getFirstName() const {return firstName;}
      void setFirstName(string first_name){firstName = first_name;}
      string getLastName() const {return lastName;}
      void setLastName(string last_name){lastName = last_name;}
      string getName() const;

      char getContactType() const {return contactType;}
      void setContactType(char contact_type){contactType = contact_type;}
      
      string getState() const {return state;}
      
      void setEmail(string emailAddr);
      string getEmail() const {return email;}

      void setDateOfBirth(string dateOB){dateOfBirth = dateOB;}
      string getDateOfBirth() const {return dateOfBirth;}

      void setAddress(int streetNum, string street_name, string city, string state_name, int postal_code);
      string getAddress() const;

      void setPhoneNumbers(string phone, string cell);
      string addPhone(char type, string new_number);
      string deletePhone(int phoneIdx);
      string getAsString() const;
      vector<string> getPhoneNumbers();

      friend bool operator<(const Contact& lhs, const Contact& rhs);
      friend bool operator==(const Contact& lhs, const Contact& rhs);

   private:
      char contactType;
      string firstName, lastName, streetName, city, state, email, dateOfBirth;
      int streetNumber, postalCode;
      vector<PhoneNumbers> phoneNumbers;

      string getLabelForType (char type);
    
};

#endif