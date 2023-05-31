//This file contains the function definitions for the ContactList class

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>

#include "ContactList.h"
#include "Contact.h"

using namespace std;

/*This function loads in contacts from a csv file
Takes in one parameter:
A string constant parameter indicating the file name*/
string ContactList::loadContactsFromFile(const string filename){

   ifstream contact_file{filename}; //creates a input file stream using filename

   if (!contact_file.is_open()){ //checks if the file is opened
    return "failure: " + filename + " not found"; //returns error message if unopened
   }
   else{
    
    //declarations char and string variables to represent each part of an address
    char CurrContactType;
    string CurrFirstName, CurrLastName, CurrStreetName, CurrCity, CurrState, 
    CurrEmail, CurrDateOfBirth, CurrStreetNumber, CurrPostalCode,
    CurrPhone, CurrCell;
    
    string junk; //junk is used to skip over unnecessary text in the file
    getline(contact_file, junk);
    junk = "";

   //for loop that iterates over contact_file, reading each line using getline()
    for (string line; getline(contact_file, line);){

      istringstream CurrLine{line}; //creates input stringstream

      CurrLine >> CurrContactType;
      getline(CurrLine, junk, ',');
      getline(CurrLine, CurrFirstName, ',');
      getline(CurrLine, CurrLastName, ',');
      getline(CurrLine, CurrStreetNumber, ',');
      getline(CurrLine, CurrStreetName, ',');
      getline(CurrLine, CurrCity, ',');
      getline(CurrLine, CurrState, ',');
      getline(CurrLine, CurrPostalCode, ',');
      getline(CurrLine, CurrEmail, ',');
      getline(CurrLine, CurrDateOfBirth, ',');
      getline(CurrLine, junk, ',');
      getline(CurrLine, CurrPhone, ',');
      getline(CurrLine, CurrCell, ',');

      Contact CurrContact{CurrPhone, CurrCell, static_cast<char>(toupper(CurrContactType))}; //creates a Contact object

      //sets the remaining information of the contact
      CurrContact.setFirstName(CurrFirstName);
      CurrContact.setLastName(CurrLastName);
      CurrContact.setEmail(CurrEmail);
      CurrContact.setDateOfBirth(CurrDateOfBirth);
      CurrContact.setAddress(stoi(CurrStreetNumber), CurrStreetName, CurrCity, CurrState, stoi(CurrPostalCode));
      
      contacts.push_back(CurrContact); //adds the contact to the data member vector contacts

    }

    return "success: " + to_string(contacts.size()) + " contacts added"; //returns success message
   }
}

/*This function deletes a contact from the ContactList object
Takes in one parameter:
A integer indicating the index position of the contact in the vector contacts*/
string ContactList::deleteContact(int contactIdx){

   int size = contacts.size();

   if (contactIdx >= 0 && contactIdx < size){ //checks if contactIdx is valid index
      string contact_name = contacts.at(contactIdx).getName(); //stores contact name in variable

      contacts.erase(contacts.begin() + contactIdx); //deletes the element at the index
      return  "success: deleted contact " + contact_name; //returns success message
   }
   else{ //returns error message if invalid
      return "failure: unable to delete contact " + to_string(contactIdx);
   }

}

/*This function adds a Contact object to the ContactList object
Takes in one parameter:
A Contact object by reference*/
string ContactList::addContact(Contact& new_contact){

   int previous_size = contacts.size(); //stores the original size of contacts

   contacts.push_back(new_contact); //pushes new_contact to contacts
   
   if (static_cast<int>(contacts.size()) == previous_size + 1){ //checks if the contact is added
      return "success: contact " + new_contact.getName() + "\n"; //returns success message
   }
   else{
      return "failure: unable to add contact\n"; //returns error message
   }
}

//This function sorts the contacts vector alphabetically by name
string ContactList::sortContacts(){
   vector<Contact> previous_list = contacts; //saves the vector before sorting
   
   sort(contacts.begin(), contacts.end()); //uses the sort() method to sort the vector

   if (contacts == previous_list){ //checks if the vectors are the same
      return "failure"; //error message
   }
   
   return "success"; //success message
}

/*This is a helper function that capitalizes every letter in a string
Takes in one parameter:
A string parameter of the original string*/
string upperCaseConvert(string orig_str){

   string new_string = "";

   //loops through each character of orig_str and capitalizes each letter
   for (char currChar: orig_str){

      if (isalpha(currChar)){
         new_string += toupper(currChar); //adds the character to new_string
      }
      else{
         new_string += currChar;
      }
   }

   return new_string; //returns the string
}

/*This function searches through the contacts vector for a contact
Returns a vector of integers representing the indices of contacts
Takes in one parameter:
A string indictating the contact name to search for*/
vector<int> ContactList::findContactsByName(string target_contact) const{

   vector<int> index_pos; //vector to be returned
   int size = contacts.size();

   for (int i = 0; i < size; i++){

      string upper_version = upperCaseConvert(contacts.at(i).getName()); //stores the fully upper case name

      if (upper_version.find(upperCaseConvert(target_contact)) != string::npos){ //checks if target_contact is a substring of the contact name
         index_pos.push_back(i); //pushes the index to index_pos
      }
   }

   return index_pos; //returns vector
}

//This function prints out the contacts of ContactList
void ContactList::printContacts() const{

   int counter = 0;
   int size = contacts.size();

   //do while loop that prints out each contact
   do{
      for (int i = 0; i < 20; i++){
         cout << "-";
      }
      cout << endl;
      cout << endl;
      cout << contacts.at(counter).getAsString();
      cout << endl;
      counter++;
   }while(counter < size);
}

/*Secondary version of printContacts but instead prints out a selection of contacts
Takes one parameter:
A vector of integers indicating which elements to print out*/
void ContactList::printContacts(const vector<int>& positions) const{

   int pos_size = positions.size();

   for (int i = 0; i < pos_size; i++){
      for (int i = 0; i < 20; i++){
         cout << "-";
      }
      cout << endl;
      cout << endl;
      cout << contacts.at(positions.at(i)).getAsString(); //same process, but uses the elements of positions instead of a integer variable
      cout << endl;
   }
}

/*This function returns a Contact* pointer to represent a contact
Takes one parameter:
A integer indicating the index position of the contact in the vector contacts*/
Contact* ContactList::getContact(int idx) {
    return &contacts.at(idx); //returns memory address of element
}
