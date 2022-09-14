//
// doc.cpp
// Author: Kevin Paganini
// CS 2040, Spring 2022
//

#include "doc.h"
#include <fstream>
#include <iostream>
#include "line.h"
#include <list>
#include <iomanip>

using namespace std;

// Document Destructor
Document::~Document(){
    for(auto line : text){
        delete line;
    }
    
    
}
// Document Constructor
Document::Document(){

}

// Read in the source file ignoring empty lines
void Document::read(string source_file){
    ifstream infile(source_file);
    if (!infile.good()){
        cerr << "Cannot read " << source_file << endl;
        exit(2);
    }

    while (infile.good()){
        string cur_line;
        getline(infile, cur_line);
        if(cur_line != ""){
            text.push_back(new Line(cur_line));
        }
        
    }


}
// Appending to a Document with a new line
void Document::append(string new_line){
    text.push_back(new Line(new_line));
}

//Inserting a new line into the specified line number
void Document::insert(int before, string new_line){
    auto it = text.begin();
    advance(it, before);
    text.insert(it, new Line(new_line));
}

//Removing a specific line from the document
void Document::remove(int num){
    auto it = text.begin();
    advance(it, num);
    auto line = *it;
    delete line;
    text.erase(it);

}

// Removing a section of the Document startinf from int start
// Until int end
void Document::remove(int start, int end){
    auto it_begin = text.begin();
    auto it_end = text.begin();
    advance(it_begin, start);
    advance(it_end, end + 1);

    // Used for destructing it
    auto it_for_begin = text.begin();
    advance(it_for_begin, start);
    auto it_for_end = text.begin();
    advance(it_for_end, end + 1);

    for(; it_for_begin != it_for_end; it_for_begin++){
        auto line = *it_for_begin;
        delete line;
    }

    // Deleting it from the document
    text.erase(it_begin, it_end);    
    
    
}

// Printing out the contents of the file
// with the line number
void Document::list(){
    int num = 0;
    for(Line *line : text){
        
        if (line->to_string() != ""){
            cout << setw(3) << num++ << ": ";
            cout << line->to_string() << endl;
            
        }
        
    }
}
// Making a map of all the lines containing the target_text
// <line number, line object>
map<int, Line*> Document::find(string target_text, int start){
    map<int, Line*> ret;
    auto it = text.begin();
    advance(it, start);
    for (; it != text.end(); it++) {
        auto line = *it;
        if(line->contains(target_text)){
            ret[start] = line;
        } 
        
        start++;
    }

    return ret;
}

