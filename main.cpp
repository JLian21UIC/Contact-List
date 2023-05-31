/*-------------------------------------------
Program 4: Contact List Application
Course: CS 141, Spring 2023, UIC
System: Visual Studio Code on Windows 11
Author: Jason Liang, with starter code provided by CS 141 Professors
------------------------------------------- */

#include <iomanip>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

//Include header files to include the Contact class and ContactList class
#include "Contact.h"
#include "ContactList.h"

using namespace std;

//Forward declaration of functions 
void display_start();
void load_from_file(ContactList& load_to);
void search(ContactList& search_from);
void contact_editing(Contact* edit, ContactList& search_from);
void edit_address(Contact* edit);
void edit_dob(Contact* edit);
void edit_email(Contact* edit);
void edit_name(Contact* edit);
void edit_numbers(Contact* edit);
void delete_contact(Contact* edit, ContactList& delete_from);

//This function displays the starting instructions of the program
void display_start(){
  cout << "********************************************\n"
       << "Main Menu\n\n"
       << "Enter the letter for the desired menu option:\n"
       << "   C - Get count\n"
       << "   L - Load contacts from file\n"
       << "   S - Search contacts\n"
       << "   P - Print contacts\n"
       << "   X - Exit\n\n";

}

/*
This function handles the importing of the content of a file into a ContactList object
Takes in one ContactList parameter by reference
*/
void load_from_file(ContactList& load_to){
  string load_file; //string used to capture the user's input
  cout << "Enter a filename\n";
  cin >> load_file; //takes in user input 
  cout << load_to.loadContactsFromFile(load_file) << "\n\n\n"; //uses the loadContactsFromFile function to import the contents of a file

}

/*
This function handles the search functionality of the program
Searches through a ContactList object for a keyword as part of a name
Takes in one ContactList object as an parameter by reference
*/
void search(ContactList& search_from){

  //declaration of several objects to be used
  string search_contact;
  vector<int> searchResultsIdx;
  vector<Contact*> searchResultsItems;

  cout << "\nEnter a search term\n";
  cin >> search_contact; //reads in the keyword 

  searchResultsIdx = search_from.findContactsByName(search_contact); //uses the findContactsByName function to find and store the indices of each search result into a vector

  //reports back the number of results
  cout << "\nFound " << searchResultsIdx.size(); 

  if (searchResultsIdx.size() == 1){
    cout << " result\n";
  }
  else{
    cout << " results\n";
  }

  //uses getContact function to store the search results as a vector of pointers
  for (int idx : searchResultsIdx) {
    searchResultsItems.push_back(search_from.getContact(idx));
  }

  int size = searchResultsItems.size();

  //displays each search results as a numbered list 
  for (int i = 0; i < size; i++) {
    cout << i + 1 << ". " << (*searchResultsItems.at(i)).getName() << endl;
  }
  
  //display the options the user can choose
  cout << "\nEnter an option:\n"
       << "   P - Print contacts\n"
       << "   or a Contact number to view/edit\n"
       << "   R - Return to main menu\n";

  string contact_choice;

  cout << endl;
  cin >> contact_choice; //reads the user's choice into a string

  bool is_number = (isdigit(contact_choice.at(0))) ? true: false; //uses a boolean variable to determine if the user entered a contact number

  if (is_number){ //checks whether is_number is true
    int contact_num = stoi(contact_choice) - 1; //conversts into an integer

    cout << searchResultsItems.at(contact_num) ->getAsString() << endl; //displays the contact information of the contact the user chose
    
    contact_editing(searchResultsItems.at(contact_num), search_from); //calls the contact_editing function to handle the editing of the contact
  }

  //the following branches handle the other two choices
  else if(contact_choice == "P"){
    search_from.printContacts(searchResultsIdx); //uses the printContacts function to print out all the contact information of the search results
  }
  else if(contact_choice == "R"){
    cout << endl; //exits back to the main menu   
  }

}

/*
This function handles the editing of a contact
Takes in 2 parameters, one Contact pointer and ContactList object
*/
void contact_editing(Contact* edit, ContactList& search_from){

  //displays the editing options
  cout << "Enter an option for contact:\n"
       << "   A - Edit address\n"
       << "   B - Edit date of birth\n"
       << "   E - Edit email address\n"
       << "   N - Edit name\n"
       << "   P - Edit phone numbers\n"
       << "   R - Return to main menu\n"
       << "   D - Delete\n\n";

    char edit_choice;
    cin >> edit_choice; //reads in the user's choice

    //switch case statement to determine how to edit the contact
    switch(edit_choice){
      case 'a':
      case 'A':
        edit_address(edit); //calls the edit_address function if the choice was 'a' or 'A'
        break;
      case 'b':
      case 'B':
        edit_dob(edit); //calls the edit_dob function if the choice was 'b' or 'B'
        break;
      case 'e':
      case 'E':
        edit_email(edit); //calls the edit_email function if the choice was 'e' or 'E'
        break;
      case 'n':
      case 'N':
        edit_name(edit); //calls the edit_name function if the choice was 'n' or 'N'
        break;
      case 'p':
      case 'P':
        edit_numbers(edit); //calls the edit_numbers function if the choice was 'p' or 'P'
        break;
      case 'r':
      case 'R':
        cout << endl; //returns back to the main menu if the choice was 'r' or 'R'
        break;
      case 'd':
      case 'D':
        delete_contact(edit, search_from); //calls the delete_contact function if the choice was 'd' or 'D'
        break;
    }

}

void edit_address(Contact* edit){
  int streetNumber, postalCode;
  string full_input, streetName, city, state;
  char wspace;

  cin.clear();
  cin.sync();
  
  cout << "Enter a new address or 'C' to cancel.\n";
  getline(cin, full_input);

  if (full_input != "C" && full_input != "c"){
    stringstream address_input{full_input};

    address_input >> streetNumber >> wspace;

    getline(address_input, streetName, ',');
    address_input >> wspace;
    getline(address_input, city, ',');
    address_input >> wspace >> state >> postalCode;

    edit->setAddress(streetNumber, streetName, city, state, postalCode);
    cout << "Changed address to: " << edit->getAddress() << "\n\n";
  }
}

void edit_dob(Contact* edit){
  string dob;
  cout << "Pleae enter a new date of birth in the following format: MM-DD-YEAR\nOr C to cancel.\n";
  cin >> dob;
  if (dob != "C" && dob != "c"){
    edit->setDateOfBirth(dob);
    cout << "Changed date of birth to: " << edit->getDateOfBirth() << "\n\n";
  }
}

/*
This function handles the email editing of the contact
Takes in a Contact pointer as a parameter
*/
void edit_email(Contact* edit){
  string email;
  cout << "Current email:\n" << edit->getEmail() << endl;
  cout << "Enter new email or C to cancel:\n";
  cin >> email; //gets the user's input for an email

  if (email != "C" && email != "c"){ //checks whether the user enter an email or the letter C
    edit->setEmail(email); //uses the setEmail function to update the contact's email
    cout << "Email updated:\n" << edit->getEmail() << "\n\n";
  }
  else{ //returns back to the main menu
    cout << endl; 
  }
}

void edit_name(Contact* edit){
  string first_name, last_name;
  cout << "Please enter the first name followed by the last. (Ex: John Smith)\nOr 'C' to cancel\n";
  cin >> first_name;
  if (first_name != "C" && first_name != "c"){
    cin >> last_name;
    edit->setFirstName(first_name);
    edit->setLastName(last_name);
  }
}

/*
This function handles editing the phone number of a contact
Takes in a Contact pointer as a parameter
*/
void edit_numbers(Contact* edit){
  vector<string> numbers = edit->getPhoneNumbers(); //retrieves all the phone numbers linked to the contact

  //reports back the phone numbers found
  cout << "Found " << numbers.size();
  if (numbers.size() == 1){
    cout << " phone number\n";
  } 
  else{
    cout << " phone numbers\n";
  }
  int vec_size = numbers.size();
  string curr_num;
  for (int i = 0; i < vec_size; i++){
    curr_num = numbers.at(i);
    
    cout << i + 1 << ". " << curr_num << endl;
  }


  cout << "Enter an option:\n"
       << "   A - Add a phone number\n"
       << "   R - Return to main menu\n"
       << "   or list number to delete\n\n";

  string phone_option;

  cin >> phone_option; //gets the user's choice on how to edit the phone numbers

  bool is_number = (isdigit(phone_option.at(0))) ? true: false; //checks if the user enter a number

  if (is_number){ //checks whether is_number is true
    int phone_pos = stoi(phone_option) - 1; //converts the input into an integer position

    cout << "Are you sure you want to delete phone:  "
         << numbers.at(phone_pos) << "?\n"
         << "Enter 'Y' to confirm.";
    
    char confirm;
    cin >> confirm; //reads in the user's confirmation

    if (toupper(confirm) == 'Y'){ //deletes the phone number if the user inputted 'Y'
      cout << edit->deletePhone(phone_pos) << "\n\n\n";
    }
    else{
      cout << endl;
    }

  }
  else if(phone_option == "A" || phone_option == "a"){ //if the user inputted "A", a phone number is added
    char new_phone_type;
    string new_number;

    cout << "Enter the letter for the phone number type:\n"
         << "C(ell), W(ork) or H(ome)\n";
    cin >> new_phone_type; //reads in the phone type

    cout << "Enter the phone number:\n";
    cin >> new_number; //reads in the new phone number

    cout << edit->addPhone(new_phone_type, new_number) << "\n\n"; //adds the phone number
  }
  else if(phone_option == "R" || phone_option == "r"){ //returns back to the main menu if the user inputted "R"
    cout << endl;
  }
}

/*
This function handles the deletion of a contact
Takes in 2 parameters: a Contact pointer and ContactList object
*/
void delete_contact(Contact* edit, ContactList& delete_from){
  cout << "Are you sure you want to delete contact " << edit->getName() << "?\n"
       << "Enter 'Y' to confirm.\n";

  char confirm;
  cin >> confirm; //reads in the user's confirmation

  if (toupper(confirm) == 'Y'){ //if the user inputted 'Y', the contact will be deleted
    vector<int> idx_pos = delete_from.findContactsByName(edit->getName()); //find in what position the contact is within delete_from's vector data member

    cout << delete_from.deleteContact(idx_pos.at(0)) << endl; //deletes the contact
  }
}

int main() {
  //declares a character object and ContactList object
  char user_choice;
  ContactList contact_list;

  do {
    display_start(); //calls function to display main menu

    cin >> user_choice; //reads in user's choice

    switch (toupper(user_choice)) { //switch case statements for each of the menu options
      case 'C':
        cout << "There are " << contact_list.getCount() << " contacts\n\n\n"; //use getCount() to report back how many contacts are currently saved into contact_list
        break;
      case 'L':
        load_from_file(contact_list); //calls load_from_file() to import contacts from a file
        break;
      case 'S':
        search(contact_list); //calls search() to search contact_list
        break;
      case 'P':
        contact_list.printContacts(); //calls printContacts() to print out every contact saved in contact_list
        break;
      }
  } while (toupper(user_choice) != 'X');

  return 0;
}