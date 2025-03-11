/**
 * @file main.cpp
 * @author alfonsowolski
 * @date 2025-03-10
 * @brief Testing file for PhoneBook object
 * 
 * Contains several interactions and tests for the PhoneBook object
 */



#include <iostream>
#include "PhoneBook.h"

using namespace std;

string PHONE_BOOK_FILE = "PhoneBookData.txt";

int UsePhoneBook(PhoneBook &PH);

int main() {
  
  PhoneBook PH = PhoneBook();

  string str;
  
  cout << "Please enter desired phonebook(filePath)): ";
  cin >> str;

  if(!PH.read_from_file(str)){
    return 1; // file not found
  }
  
  
  while(UsePhoneBook(PH));  
  return 0;
}


int UsePhoneBook(PhoneBook &PH){

  cout << endl << endl;
  
  PH.print();
  
  string fName,lName,number;
  char inpChar;

  cout << endl << endl;

  cout << "Please choose an action: " << endl
       << "(f) Find Contact" << endl
       << "(i) Contact Info" << endl
       << "(a) Add Contact" << endl
       << "(r) Remove Contact" << endl
       << "(s) Save" << endl
       << "(q) Quit" << endl;
  cin >> inpChar;

  switch(inpChar){
  case 'f':{
    cout << endl << "Find Contact" << endl
	 << "Enter Phone Number: ";
    cin >> number;
    cout << "Contact: " << PH.reverse_lookup(number) << endl;
    return 1;
  }
  case 'i':{
    cout << endl << "Contact Info" << endl
	 << "Enter first name: ";
    cin >> fName;
    cout << "Enter last name: ";
    cin >> lName;
    cout << "Number: " << PH.lookup(fName,lName);
    return 1;
  }
  case 'a':{
    cout << endl << "Add Contact" << endl
	 << "Enter contact first name: ";
    cin >> fName;
    cout << "Enter contact last name: ";
    cin >> lName;
    cout << "Enter contact number: ";
    cin >> number;

    entry* en = new entry();

    en->first_name = fName;
    en->last_name = lName;
    en->phone_number = number;
    
    PH.insert_sorted(en);
    return 1;
  }
  case 'r':{
    cout << endl << "Remove Contact" << endl
	 << "Enter contact first name";
    cin >> fName;
    cout << "Enter contact last name";
    cin >> lName;
    
    PH.delete_user(fName,lName);
    return 1;
  }
  case 's':{
    cout << endl << "Save" << endl
	 << "Enter file to save to: ";
    cin >> fName;
    PH.write_to_file(fName);
    return 1;
  }
  case 'q':{
    return 0;
  }
  }
  

  cout << endl << "invalid input" << endl;
  return 1;
}
