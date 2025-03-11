/**
 * @file PhoneBook.cpp
 * @author alfonsowolski
 * @date 2025-03-10
 * @brief Implementation of the phonebook class
 * 
 * Implementation of the PhoneBook class
 */


#include "PhoneBook.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>

using namespace std;

bool DEBUG = false;

entry::~entry(){
  if(next != nullptr){
    delete next;
  }
}

PhoneBook::PhoneBook(){
  start = nullptr;
}

PhoneBook::~PhoneBook(){
  if(start != nullptr){
    delete start;
  }
  else{
    cout << "Null was empty!" << endl;
  }
}

void PhoneBook::push_front(entry* item){
  entry* temp = start;
  start = item;

  item->next = temp;
}

void PhoneBook::push_back(entry* item){
  entry* temp = start;
  while(true){
    if(temp->next == nullptr){
      temp->next = item;
    }
    else{
      temp = temp->next;
    }
  }
}

bool PhoneBook::read_from_file(string filePath){
  ifstream file;

  file.open(filePath, std::ios::in);

  if(!file){
    cout << filePath << " not found!" << endl;
    return false; 
  }
  if(DEBUG){ cout << "Reading from: " << filePath << endl; }
  
  string fName, lName, Pnum;

  file >> fName >> lName >> Pnum;
  while(file){
    entry* en = new entry();

    if(DEBUG){ cout << "found: " << fName  << " " << lName << " " << Pnum << endl; }
    
    en->first_name = fName;
    en->last_name = lName;
    en->phone_number = Pnum;
    en->next = nullptr;

    insert_sorted(en);
    
    
    file >> fName >> lName >> Pnum;
  }
  
  file.close();
  return true;
}

void PhoneBook::write_to_file(string filePath){
  cout << "Writing to: " << filePath << endl;
  ofstream file(filePath);
  entry* temp = start;
  
  while(temp != nullptr){
    cout << "| writing: " << temp->first_name << " " << temp->last_name << endl;
    file << temp->first_name << " " << temp->last_name << " " << temp->phone_number << endl;

    temp = temp->next;
  }

  file.close();
}

void PhoneBook::insert_sorted(entry* item){
  entry* temp = start;
  entry* prev = nullptr;

  string fName, lName, tfName, tlName;

  fName = item->first_name;
  lName = item->last_name;

  if ( start == nullptr ) {
    if(DEBUG){ cout << " enterting first object: " << fName << " " << lName << endl;}
    start = item;
    return;
  }
   // since we confirmed temp is an entry we can move to next entry on first and subsequent cycles
  prev = temp;
  temp = temp->next;

  
  int shorterNameLen;
  
  // assumes if temp == nullptr, then reached end of list
  while(temp != nullptr){
    
    tfName = temp->first_name;
    tlName = temp->last_name;

    if(DEBUG){cout << "Checking " << fName << " " << lName << " against " << tfName << " " << tlName << endl;}
    
    // Same last name
    if( tlName == lName ){
      
      // also same first name
      if( tfName == fName ) {
	break;
      }

      // Checking which first name is shorter and grabbing the size
      shorterNameLen = (tfName.length() < fName.length())? tfName.length() : fName.length();

      // Comparing first names
      for( int i = 0; i < shorterNameLen; i++){

	// checks if fName[i] comes before tfName[i]
	if( fName[i] < tfName[i] ){
	  // placing item between prev and temp
	  prev->next = item;
	  item->next = temp;
	  if(DEBUG){
	    cout << "added " << fName << " " << lName << " after " << prev->first_name << " " << prev->last_name
		 << " and before " << tfName << " " << tlName << endl;
	  }
	  return;
	}
	else if( fName[i] > tfName[i] ){ // checks if fName[i] comes after tfName[i]
	  // it comes after so we move on
	  break;
	}
	else if(( i = (shorterNameLen - 1)) && (fName[i] == tfName[i])){ // if made it to last charachter with each being equal despite different names
	  // one name must contain the other
	  if( fName.length() < lName.length()){ // if fName is shorter it comes first
	    // placing item between prev and temp
	    prev->next = item;
	    item->next = temp;
	    if(DEBUG){
	      cout << "added " << fName << " " << lName << " after " << prev->first_name << " " << prev->last_name
		   << " and before " << tfName << " " << tlName << endl;
	    }
	    return;
	  }
	  // fName is longer so it comes after, just continue to loop end
	}
	// chars must be equal so we cycle to next	
      }
      
    }
    else{ // not same last name

      // Checking which last name is shorter and grabbing size
      shorterNameLen = (tlName.length() < lName.length())? tlName.length() : lName.length();

      // Comparing last names
      for(int i = 0; i < shorterNameLen; i++){

	// checks if lName[i] comes before tlName[i]
	if( lName[i] < tlName[i] ){
	  // placing item between prev and temp
	  prev->next = item;
	  item->next = temp;
	  if(DEBUG){
	    cout << "added " << fName << " " << lName << " after " << prev->first_name << " " << prev->last_name
		 << " and before " << tfName << " " << tlName << endl;
	  }
	  return;
	}
	else if( lName[i] > tlName[i]){ // check if lName[i] comes after tlName[i]
	  // it comes after so we are done checking and can move on
	  break;
	}
	else if( (i == (shorterNameLen - 1)) && (lName[i] == tlName[i]) ) { // if made it to last charachter with each being equal despite different names
	  // one name must contain the other
	  if( lName.length() < tlName.length() ){ // check if lName is the shorter one
	    // placing item between prev and temp
	    prev->next = item;
	    item->next = temp;
	    if(DEBUG){
	      cout << "added " << fName << " " << lName << " after " << prev->first_name << " " << prev->last_name
		   << " and before " << tfName << " " << tlName << endl;
	    }
	    return;
	  }
	  // lName is longer so it comes after so just go to end of loop
	}
	
	// chars are equal so we must cycle next
      }
    }

    // move forward in list
    prev = temp;
    temp = temp->next;
    if(DEBUG){ cout << "Checking next" << endl; }
    // looping while
  }
  // must have reached end as temp == nullptr
  prev->next = item; // add item to end of list (prev is current last element)
  if(DEBUG){ cout << "adding " << fName << " " << lName << " to end of list" << endl; }
}

string PhoneBook::lookup(string firstName, string lastName){

  entry* temp = start;
  
  while(temp != nullptr){
    if ( (temp->first_name == firstName) && (temp->last_name == lastName) ){
      return temp->phone_number;
    }
    temp = temp->next;
  }

  cout << "Could not find number for \"" << firstName << " " << lastName << "\"" << endl;	
  return "";
}

string PhoneBook::reverse_lookup(string number){
  entry* temp = start;

  while(temp != nullptr){
    if( temp->phone_number == number ){
      return (temp->first_name + " " + temp->last_name);
    }
    temp = temp->next;
  }

  cout << "failed to find contact with number: " << number << endl;
  return "";
}

void PhoneBook::print(){
  cout << "PhoneBook Listing: " << endl;
  
  entry* temp = start;
  
  while(temp != nullptr){
    cout << "Name: " << temp->first_name << " " << temp->last_name << "   Number: " << temp->phone_number << endl;
    temp = temp->next;
  }
}

void PhoneBook::delete_user(string firstName, string lastName){
  entry* temp = start;
  entry* prev = nullptr;
  
  while(temp != nullptr){
    if( (temp->first_name == firstName) && (temp->last_name == lastName) ){
      if (prev != nullptr) { // not on first element
	prev->next = temp->next;
	temp->next = nullptr;
	delete temp;
      }
      else{ // first element
	prev = temp->next; // prev is being used as a place holder
	temp->next = nullptr;
	delete temp;
	start = prev;
      }
      return;
    }
    prev = temp;
    temp = temp->next;
  }

    cout << "Did not find user: " << firstName << " " << lastName << endl;
}
