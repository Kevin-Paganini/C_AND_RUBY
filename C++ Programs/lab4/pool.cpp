//
// pool.h: declares the class Pool
//
// Author: Kevin Paganini
// Professor: Dr. Hasker
// Date: 4/3/2022
// Assignment: Lab 4, 2021

// Class implementation of Pool

#include "pool.h"
#include <iostream>
#include <string>
#include <set>

using namespace std;



//Constructor
Pool::Pool() {
  names_size = 0;

}

// Adds a name to list and increases size
void Pool::add(string name) {
  names[names_size] = name;
  names_size++;
}


// Checks if list is empty
bool Pool::empty(){
    bool flag = false;
    if(names_size == 0){
        flag = true;
    }
    return flag;
}

// reads in names from standard input
void Pool::readNames(){
    string name;
    cin >> name;
    
    while(name != "END" && cin){
        if(!isFull()){
            
            
            add(name);
            cin >> name;
            
        } else {
            cin >> name; // basically gets ignored
            
        }
        
    }
    
    
}


// print all matches between two pools
void Pool:: printMatches(Pool *pool){
        //loop through list of pool using method from passed in pool
        for(int j = 0; j < names_size; j++){
            pool->printMatches(names[j]);
        }
    
    
}
  
// print all matches with one particular name
void Pool:: printMatches(string name){
    
    string no_match[MAX_NAMES];
    int no_match_size = 0;
    
    
    // Removing names that are the same ignoring underscores
    for(int i = 0; i < names_size; i++){
        
       
        if(removeUnderscores(names[i]) !=  removeUnderscores(name)){
            no_match[no_match_size] = names[i];
            no_match_size++;
            
        }
        
    }
    string name_no_us = removeUnderscores(name);
    
    
    // Finding letters in common and printing them
    int k = 0;
    while(k < no_match_size){
        isMatchingPair(name, no_match[k]);
       
        k++;
    }
    
   
    
}


// Do two names have a letter in common
// If they do it prints and stops looking
bool Pool:: isMatchingPair(string name1, string name2){
     for(unsigned int i = 0; i < name1.size(); i++){

        for(unsigned int j = 0; j < name2.size(); j++){
            

           if(name1[i] != '_'){
               if(name1[i] == name2[j]){
                
                prettyPrint(name1, name2);
                return true;
                

            }
           }
            
        }
    }
    return false;
}



// is the pool full?
bool Pool:: isFull(){
    bool flag;
    if (names_size < MAX_NAMES) {
        flag = false;
    } else {
        flag = true;
    }
    return flag;
}




// Removes underscores from a passed in string
string Pool:: removeUnderscores(string name){
    unsigned int i = 0;
    string new_name = "";
    char forbidden = '_';
    while (i < name.size()){
        if (name[i] != forbidden){
            new_name += name[i];
        }
        i++;
    }
    return new_name;
}


// Prints the output string
void Pool::prettyPrint(string name1, string name2){
    
 
        string match = "A perfect match for " + name1 + ": " + name2;
        cout << match << endl;
   
   
}


