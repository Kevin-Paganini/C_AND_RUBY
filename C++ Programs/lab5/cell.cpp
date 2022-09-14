//============================================================================
// Name        : cell.cpp
// Author      : paganinik
// Assignment  : CS 2040, Lab 5
// Description : Cell in the map definition
//============================================================================

#include "cell.h"
#include <string>
#include <iostream>
#include <iomanip>
using namespace std;


//============================================================================
// Constructor for Cell
// Param: x coord, y coord, and what letter
//============================================================================
  MapCell::MapCell(int x, int y, char type){
      xLocation = x;
      yLocation = y;
      token = type;
      
      hasRobot = false;
      
  }
  
  
  // true if pit at this location
  bool MapCell::hasPit(){
        return token == '#';
      
  }
  // true if gold at this location
  bool MapCell::hasGold(){
        return token == '*';
      
  }
  // remove the gold at this location
  void MapCell::removeGold(){
        token = ' ';
      
  }
  // is this location occupied by something that the robot
  //   cannot move over?
  bool MapCell::occupied(){
      bool occupant = hasPit();
      return occupant;
      
  }
  // return the character to display for this location
  char MapCell::display(){
      return token;
      
  }
  // robot enters location
  void MapCell::enter(){
      hasRobot = true;
      previousToken = token;
      
      token = 'R';
      
  }
  // robot leaves location
  void MapCell::vacate(){
      hasRobot = false;
      if(previousToken == '*'){
          token = ' ';
          
      } else {
          token = previousToken;
      }
  }
