//============================================================================
// Name        : robot.cpp
// Author      : paganinik
// Assignment  : CS 2040, Lab 5
// Description : Robot to navigate the environment and 
// collect gold definitions
//============================================================================
#include "robot.h"
#include "map.h"
#include "cell.h"
#include <string>
#include <iostream>
#include <iomanip>
#include <cctype>
using namespace std;







// Constructor
  Robot::Robot(Map *map, int startx, int starty){
      currentX = startx;
      currentY = starty;
      mapcells = map;
      goldCount = 0;
      enterStart(startx, starty);
      current = map->getCell(startx, starty);
      
      
  }
  

// display robot status in the form of "Robot at 6, 7 (1 gold)" to cout

  void Robot::displayStatus(){
      cout << "Robot at " << currentX << ", " << currentY << " (" << goldCount << " gold)";
      
  }
  
  

// move robot in specified direction (e/w/s/n), returning true

  bool Robot::move(char direction){
      char ch = tolower(direction);
      
      if (isValidPosition(ch) == true){
          
        enterPosition(currentX, currentY);
        return true;
          
      } else {
          return false;
      }
      
  }
  
// move robot in a series of directions, returning true if was
//   able to complete the list of directions
  bool Robot::move(std::string commands){
      for(unsigned int i = 0; i < commands.size(); i++){
          bool check = move(commands[i]);
          if (check == false){
              return false;
          }
      }
      return true;
  }
  
  
// Is the position the robot is going to
// not a pit and in bounds
  bool Robot::isValidPosition(char direction){
      bool valid = false;
      if (direction == 'e'){
          if (currentX + 1 < ARENA_COLS && noObstruction(currentX + 1, currentY) == true){
            previousX = currentX;
            currentX++;
            valid = true;
          }
         
          
      } else if (direction == 'w'){
          if (currentX - 1 >= 0 && noObstruction(currentX - 1, currentY) == true){
            previousX = currentX;
            currentX--;
            valid = true;
          }
          
          
      } else if (direction == 'n'){
          if (currentY - 1 >= 0 && noObstruction(currentX, currentY - 1) == true){
            previousY = currentY;
            currentY--;
            valid = true;  
          }
          
          
      } else if (direction == 's'){
          if (currentY + 1 < ARENA_ROWS && noObstruction(currentX, currentY + 1) == true){
            previousY = currentY;
            currentY++;
            valid = true;
          }
          
          
      }
      return valid;
  }
  
  // Go to validated position
  bool Robot::enterPosition(int x, int y){
      MapCell* cell = mapcells->getCell(x, y);
      current-> vacate();
      current = cell;
      if(current->hasGold() == true){
          goldCount++;
          current-> enter();
          
          
          
      } else {
          current-> enter();
      
      
      }
      
      return true;
  }
  // Enter cell at start of game
  void Robot::enterStart(int x, int y){
      MapCell* cell = mapcells->getCell(x, y);
      
      current = cell;
      if(current->hasGold() == true){
          goldCount++;
          current-> enter();
          
          
       
      } else {
          current-> enter();
      }
      
      
      
  }
  // Make sure there is no pit in prospective cell
  bool Robot::noObstruction(int x, int y){
      MapCell* cell = mapcells->getCell(x, y);
      if (!cell->occupied()){
          return true;
      }
      return false;
  }
  
  
  
  