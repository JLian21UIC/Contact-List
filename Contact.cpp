//This file contains the function definitions for the Contact class

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;


#include "Contact.h"

//default contructor for the Contact class
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

/*Constructor for the Contact class
Constructs the object with the value of contactType, firstName, and lastName initialized*/
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

/*Third constructor for the Contact class
Initializes the data member contactType and adds 2 phone numbers*/
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

//Sets the email for the contact
void Contact::setEmail(string emailAddr){
   email = emailAddr;
}

//sets the address for the contact
void Contact::setAddress(int streetNum, string street_name, string city_name, string state_name, int postal_code){
   streetNumber = streetNum;
   streetName = street_name;
   city = city_name;
   state = state_name;
   postalCode = postal_code;
}

//returns the address as a string
string Contact::getAddress() const {
   string address = "";
   address += to_string(streetNumber) + " ";
   address += streetName + ", ";
   address += city + ", ";
   address += state + " ";
   address += to_string(postalCode);
   
   return address;
}

//returns the name of the contact as a string
string Contact::getName() const {
   return getLastName() + ", " + getFirstName();
}

//This function adds a new phone number to the contact
string Contact::addPhone(char type, string new_number){
   string message;

   if (type == 'W' || type == 'H' || type == 'C'){ //checks if the phone type is valid
      
      struct PhoneNumbers newPhoneNumber; //declares a new PhoneNumbers object
      
      //sets the phone number and type
      newPhoneNumber.phoneType = type;
      newPhoneNumber.phone_number = new_number;
      phoneNumbers.push_back(newPhoneNumber); //adds the phone number to the vector
      
      string new_type;
      
      //switch case statements to help construct the return message
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
      return message; //return message
   }
   else{ //returns error message if invalid phone type
      message = "failure: invalid phone type - ";
      message.push_back(type);
      return message;
   }

}

/*This function deletes a PhoneNumbers object from the phoneNumbers vector
Takes in one parameter: an integer indicating index to delete*/
string Contact::deletePhone(int phoneIdx){
   int size =  phoneNumbers.size();
   
   if (phoneIdx < 0 || phoneIdx >= size){ //checks if the index is invalid
      return  "failure: unable to delete phone " + to_string(phoneIdx); //error message
   }
   else{ //deletes the element from phoneNumbers and returns a success message
      phoneNumbers.erase(phoneNumbers.begin() + phoneIdx);
      return "success: deleted phone " + to_string(phoneIdx);
   }
}

//this functions returns a contact's information as a string
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

//this function returns a vector of all phone numbers associated with the contact
vector<string> Contact::getPhoneNumbers() {
  vector<string> numbers;

  for (PhoneNumbers pn: phoneNumbers) {
    numbers.push_back(getLabelForType(pn.phoneType) + " " + pn.phone_number);
  }

  return numbers;
  
}

//This is a helper function that returns the phone type's full label
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

//overload of the < operator for two Contact objects
bool operator<(const Contact& lhs, const Contact& rhs){
   return lhs.getName() < rhs.getName(); 
}

//overload of the == operator for two Contact objects
bool operator==(const Contact& lhs, const Contact& rhs){
   return lhs.getName() == rhs.getName();
}
