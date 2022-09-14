//============================================================================
// Name        : cell.h
// Author      : paganinik
// Assignment  : CS 2040, Lab 5
// Description : Cell in the map declaration
//============================================================================

#ifndef CELL_H_
#define CELL_H_

// Tracks the contents of a particular cell on the map.
// Is there gold at this location, is it occupied by a robot,
// is there a pit there? Each cell needs to track
// where it is on the grid (x, y) and the type of
// object at that location. The provided methods are suggestions;
// feel free to add/remove as needed.
class MapCell {
  int xLocation, yLocation;
  char token;
  bool hasRobot;
  
public:

//============================================================================
// Constructor
// Param: int x, int y, char type
// Cell with x and y coordinate and letter value
//============================================================================
  MapCell(int x, int y, char type);


//============================================================================
// true if pit at this location
//============================================================================
  bool hasPit();
 
//============================================================================ 
// true if gold at this location
//============================================================================
  bool hasGold();

//============================================================================  
// remove the gold at this location
//============================================================================
  void removeGold();
  
//============================================================================
// is this location occupied by something that the robot
//   cannot move over?
//============================================================================
  bool occupied();
  
//============================================================================
// return the character to display for this location
//============================================================================
  char display();

//============================================================================
// robot enters location
//============================================================================
  void enter();
  
//============================================================================
// robot leaves location
//============================================================================
  void vacate();
  
  
//============================================================================
// What did the cell have before the RAAAAAAAIIIIDER entered
//============================================================================
  char previousToken;
};

#endif /* CELL_H_ */
