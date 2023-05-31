//This file contains the function definitions for the Contact class

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;


#include "Contact.h"

Contact::Contact(){
   contactType = 'U';
   firstName = "Unset";
   lastName = "Unset";
   streetName = "Unset";
   city = "Unset";
   state = "Unset";
   email = "Unset";
   dateOfBirth = "Unset";
   streetNumber = -1;
   postalCode = -1;
}

Contact::Contact(char contact_type, string first_name, string last_name){
   contactType = contact_type;
   firstName = first_name;
   lastName = last_name;
   streetName = "Unset";
   city = "Unset";
   state = "Unset";
   email = "Unset";
   dateOfBirth = "Unset";
   streetNumber = -1;
   postalCode = -1;
}

Contact::Contact(string phone, string cell, char contact_type){

   contactType = contact_type;
   firstName = "Unset";
   lastName = "Unset";
   streetName = "Unset";
   city = "Unset";
   state = "Unset";
   email = "Unset";
   dateOfBirth = "Unset";
   streetNumber = -1;
   postalCode = -1;

   struct PhoneNumbers currPhone;
   struct PhoneNumbers currCell;

   currPhone.phoneType = 'H';
   currPhone.phone_number = phone;

   phoneNumbers.push_back(currPhone);

   currCell.phoneType = 'C';
   currCell.phone_number = cell;

   phoneNumbers.push_back(currCell);

}

void Contact::setEmail(string emailAddr){
   email = emailAddr;
}

void Contact::setAddress(int streetNum, string street_name, string city_name, string state_name, int postal_code){
   streetNumber = streetNum;
   streetName = street_name;
   city = city_name;
   state = state_name;
   postalCode = postal_code;
}

string Contact::getAddress() const {
   string address = "";
   address += to_string(streetNumber) + " ";
   address += streetName + ", ";
   address += city + ", ";
   address += state + " ";
   address += to_string(postalCode);
   
   return address;
}

string Contact::getName() const {
   return getLastName() + ", " + getFirstName();
}

string Contact::addPhone(char type, string new_number){
   string message;

   if (type == 'W' || type == 'H' || type == 'C'){
      struct PhoneNumbers newPhoneNumber;
      newPhoneNumber.phoneType = type;
      newPhoneNumber.phone_number = new_number;
      phoneNumbers.push_back(newPhoneNumber);
      string new_type;
      switch(type){
         case 'W':
            new_type = "Work";
            break;
         case 'H':
            new_type = "Home";
            break;
         case 'C':
            new_type = "Cell";
            break;
      }

      message = "success: added number " + new_number + " " + new_type;
      return message;
   }
   else{
      message = "failure: invalid phone type - ";
      message.push_back(type);
      return message;
   }

}

string Contact::deletePhone(int phoneIdx){
   int size =  phoneNumbers.size();
   if (phoneIdx < 0 || phoneIdx >= size){
      return  "failure: unable to delete phone " + to_string(phoneIdx);
   }
   else{
      phoneNumbers.erase(phoneNumbers.begin() + phoneIdx);
      return "success: deleted phone " + to_string(phoneIdx);
   }
}

string Contact::getAsString() const{
   string full_contact = "";

   full_contact += getName() + "\n";
   full_contact += (getContactType() == 'W') ? "Work\n" : "Personal\n";
   full_contact += getAddress() + "\n";
   full_contact += getDateOfBirth() + "\n";
   full_contact += getEmail() + "\n";
   string type;
   for (PhoneNumbers phone: phoneNumbers){
      switch(phone.phoneType){
         case 'W':
            type = "Work";
            break;
         case 'H':
            type = "Home";
            break;
         case 'C':
            type = "Cell";
            break;
      }
      full_contact += type;
      full_contact += ": " + phone.phone_number + "\n";
   }

   return full_contact;
}

vector<string> Contact::getPhoneNumbers() {
  vector<string> numbers;

  for (PhoneNumbers pn: phoneNumbers) {
    numbers.push_back(getLabelForType(pn.phoneType) + " " + pn.phone_number);
  }

  return numbers;
  
}

string Contact::getLabelForType (char type) {
  string result;
  
  switch (type){
    case 'P':
      result = "Personal";
      break;
    case 'W':
      result = "Work";
      break;
    case 'C':
      result = "Cell";
      break;
    case 'H':
      result = "Home";
      break;  
    default:
      result = "Unknown type"; 
  }

  return result;
  
}

bool operator<(const Contact& lhs, const Contact& rhs){
   return lhs.getName() < rhs.getName(); 
}

bool operator==(const Contact& lhs, const Contact& rhs){
   return lhs.getName() == rhs.getName();
}