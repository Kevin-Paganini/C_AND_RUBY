//============================================================================
// Name        : robot.h
// Author      : paganinik
// Assignment  : CS 2040, Lab 5
// Description : Robot to traverse game space declarations
//============================================================================
#ifndef ROBOT_H_
#define ROBOT_H_

class MapCell;

class Map;
#include <string>
#include "map.h"
#include "cell.h"

//============================================================================
// A robot which lives on a map at a particular x and y coordinate.
//============================================================================
class Robot {
    
public:
//============================================================================
// Maximum columns
//============================================================================
  static constexpr int ARENA_COLS = 20;
  
//============================================================================
// Maximum rows
//============================================================================
  static constexpr int ARENA_ROWS = 10;
  
//============================================================================
// Constructor
// Param: Map, int, int 
// Start position and the map of the grid
//============================================================================
  Robot(Map *map, int startx, int starty);
  
//============================================================================
// display robot status in the form of "Robot at 6, 7 (1 gold)" to cout
//============================================================================
  void displayStatus();
  
//============================================================================
// move robot in specified direction (e/w/s/n), returning true
//   if was able to move in that direction
//============================================================================
  bool move(char direction);
  
//============================================================================
// move robot in a series of directions, returning true if was
//   able to complete the list of directions
//============================================================================
  bool move(std::string commands);
  
  
private:
//============================================================================
// Map for the robot
//============================================================================
  Map *mapcells;

//============================================================================
// Current cell robot is in
//============================================================================
  MapCell *current;

//============================================================================
// Current x coordinate
//============================================================================
  int currentX;
  
//============================================================================
// Current y coordinate
//============================================================================
  int currentY;

//============================================================================
// Previous X position
//============================================================================
  int previousX;
  
//============================================================================
// Previous y position
//============================================================================
  int previousY;

//============================================================================
// How much gold the RAAAAAAAIIIIDDDDEEERRRRR bot has
//============================================================================
  int goldCount;
  
//============================================================================
// Is the direction given a valid position to go to
//============================================================================
  bool isValidPosition(char direction);
  
//============================================================================
// Go to the valid position that was checked
//============================================================================
  bool enterPosition(int x, int y);
  
//============================================================================
// Make sure there is no obstruction in the prospective position
//============================================================================
  bool noObstruction(int x, int y);
  
//============================================================================
// Enter the starting position
//============================================================================
  void enterStart(int x, int y);
  
  
};

#endif /* ROBOT_H_ */
