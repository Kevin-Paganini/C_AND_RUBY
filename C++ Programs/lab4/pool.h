//
// pool.h: declares the class Pool
//
// Author: Kevin Paganini
// Professor: Dr. Hasker
// Date: 4/3/2022
// Assignment: Lab 4, 2021

// Class definition of Pool
//

// do not change the next two lines - we will explain later

//~magic~
#ifndef _pool_h
#define _pool_h

#include <iostream>
#include <string>
#include <set>
using namespace std;

class Pool {
    
//********************************************************
// PUBLIC FUNCTIONS AND VARIABLES
//********************************************************
public:
  
  // Constructor
  Pool();
  
  // Add name to list
  void add(string name);
  
  // check if list is empty
  bool empty();
  
  // reads names until max or end of file
  // fills list of names
  void readNames();
  
  // print all matches between two pools
  void printMatches(Pool *pool);
  
  // print all matches with one particular name
  void printMatches(string name);
  


//********************************************************
// PRIVATE FUNCTIONS AND VARIABLES
//********************************************************

private:
  // maximum names in the list
  static constexpr int MAX_NAMES = 20;
  
  // List to store the names
  string names[MAX_NAMES];
  
  // Keeps track of how many names are in the list
  int names_size;
  
  
  
  // is the array full
  // Return: Boolean
  bool isFull();
  
  //Removes underscore from a string
  // Param: string name to remove underscores from
  // Return: clean string
  string removeUnderscores(string name);
  
  
  // Prints match in desired format
  // Param: string name1, string name2 (names to print)
  void prettyPrint(string name1, string name2);
  
  
  // Calls pretty print if two names have a letter in common
  // Param: string name1, string name2 (the names to compare)
  // Return: boolean (whether they match or not)
  bool isMatchingPair(string name1, string name2);
  
};

// do not touch the next line

// ~ more magic ~
#endif
