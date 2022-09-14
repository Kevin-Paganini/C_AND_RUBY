//============================================================================
// Name        : map.cpp
// Author      : paganinik
// Assignment  : CS 2040, Lab 5
// Description : Map keeping track of all cells declaration
//============================================================================
#include "map.h"
#include "cell.h"
#include <string>
#include <iostream>
#include <iomanip>

using namespace std;


// Constructor
Map::Map(){}


// Printing out the map
void Map::write(){
    cout << "+--------------------+" << endl;
    for(int row = 0; row < ARENA_ROWS; row++){
        cout << "|" << flush;
        for(int col = 0; col < ARENA_COLS; col++){
            
            cout << cells[row][col]->display() << flush;
            
        }
        cout << "|" << endl;
    }
    cout << "+--------------------+" << endl;
    
}
// Loading intial map in
void Map::load(){
    string line;
    int row = 0;
    getline(cin, line);
    while (getline(cin, line) && row < ARENA_ROWS) {
       
        for (int col = 0; col < ARENA_COLS; col++){
            cells[row][col] = new MapCell(col,row, line[col+1]);
        }
        row++;
    }
    
}


//Get a specific cell
MapCell* Map::getCell(int x, int y){
    
    return cells[y][x];
}



