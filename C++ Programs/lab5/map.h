//============================================================================
// Name        : map.h
// Author      : paganinik
// Assignment  : CS 2040, Lab 5
// Description : Keeps track of all cells in game definition
//============================================================================

#ifndef MAP_H_
#define MAP_H_

// the following line (declaration) ensures do not to include cell.h
class MapCell;


//============================================================================
// Track the area the robot in which the robot moves.
// Note you will need to add declarations for the height and width.
// Add other methods and data as needed.
//============================================================================
class Map {


public:
//============================================================================
// Maximum amount of columns in game
//============================================================================
  static constexpr int ARENA_COLS = 20;
  
//============================================================================
// Maximum amount of rows in game
//============================================================================
  static constexpr int ARENA_ROWS = 10;
  
//============================================================================
// Constructor for map to keep track of cells
//============================================================================
  Map();
  
//============================================================================
// read the map from cin
//============================================================================
  void load();

//============================================================================  
// write (display) the full map to cout
//============================================================================
  void write();
  
//============================================================================
// Get specific cell
//============================================================================
  MapCell* getCell(int x, int y);
    
    
//============================================================================
// Two dimensional array to store cells
//============================================================================
  MapCell* cells[ARENA_ROWS][ARENA_COLS];

};

#endif /* MAP_H_ */
