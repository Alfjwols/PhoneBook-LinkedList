/**
 * @file PhoneBook.h
 * @author alfonsowolski
 * @date 2025-03-10
 * @brief Definition of the PhoneBook Class
 * 
 * The Definition of the PhoneBook class
 */

#ifndef PHONEBOOK_H
#define PHONEBOOK_H

#include <string>

using namespace std;

struct entry{
  string first_name;
  string last_name;
  string phone_number;

  entry* next;

  ~entry();
};

class PhoneBook{
 public:
  

/**
 * Constructor for PhoneBook
 *
 * @post 
 * 
 */
  PhoneBook();


/**
 * Deconstructor for PhoneBook
 * 
 * @post Linked List of entries will be deallocated
 * 
 */
  ~PhoneBook();


/**
 * Places entry 'item' at front of list
 *
 * @param entry* item pointer to the item to place at front of list
 * @pre item exists
 * @return void 
 * @post all elements will be 1 further down the list
 * 
 */
  void push_front(entry* item);


/**
 * Places entry 'item' at back of list
 *
 * @param entry* item pointer to the item to place at back of list
 * @pre item exists
 * @return void  
 * 
 */
  void push_back(entry* item);


/**
 * Populates linked list with items from a file
 *
 * @param string filePath the path to the file we want to read data from
 * @pre file exists, and follows proper format: "name lastname number" on each line
 * @return bool true if file is found, false if file is not found 
 * @post Linked list has been populated from elements from file
 * 
 */
  bool read_from_file(string filePath);


/**
 * Writes linked list data to a file, either creating a new or overwriting existing
 *
 * @param string filePath the file to (create?) save the information to
 * @return void 
 * @post file at filePath will contain entries following format: "name lastname number" on each line
 * 
 */
  void write_to_file(string filePath);


/**
 * Place item into linked list where it would fall alphabetically
 *
 * @param entry* item pointer to the item to add to the list
 * @pre list is already ordered alphabetically (not required but highly recomended)
 * @return void 
 * @post item is placed in it's alphabetical place and some elements may be moved further down the list
 * 
 */
  void insert_sorted(entry* item);




/**
 * Checks list for the name and returns the number if found
 *
 * @param string firstName the first name of the person to look up
 * @param string lastName the last name of the person to look up
 * @return string the number of the person that was found
 * 
 */
  string lookup(string firstName, string lastName);


/**
 * Checks list for the number and returns the name if found
 *
 * @param string phone_number the number you want to find the owner of
 * @return string the name of the person whose phone it is (first and last name seperated by a space)
 * 
 */
  string reverse_lookup(string phone_number);


/**
 * Print the full list of entries to the console
 *
 * @return void 
 * 
 */
  void print();


/**
 * Deletes the entry with the specified name
 *
 * @param string firstName The first name of the entry to delete
 * @param string lastName the last name of the entry to delete
 * @pre 
 * @return void 
 * @post the entry is removed and items are pulled forward to fill any gap
 * 
 */
  void delete_user(string firstName, string lastName);
  
  
 private:
  entry* start;
};

#endif
