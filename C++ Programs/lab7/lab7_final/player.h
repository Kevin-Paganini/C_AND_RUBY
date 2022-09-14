/**
 * @file Player.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-04-22
 * 
 * @copyright Copyright (c) 2022
 * 
 */

using namespace std;
#ifndef PLAYER_H_
#define PLAYER_H_

#include <string>
#include "gameobject.h"

class Forest;
class Item;
class GameObject;

//---- PLAYER DEFINITION ----//
class Player {
        
    private: 
        
        //max size of the inventory
        

        int numMovesLeft;
        Forest *forest;
        int numItems;
        int MAX_X = 7;
        int MAX_Y = 7;
    
    public: 
        static int constexpr inventorySize = 10;
        GameObject *inventory[inventorySize + 1]; // so that use works properly

        Player(int startX, int startY, Forest* forest);
        bool move(int *pos);
        void printInventory();
        
        /**
         * @brief Looks at the nearby cells and prints that they're nearby.
         */
        void senseNearbyCells();

        /**
         * @brief uses item in inventory
         * 
         * @param item item to use
         * @param pos position to use the item in
         */
        void use(Item *item, int *pos); // Probably need a direction

        /**
         * @brief Get the number of items in the inventory
         * 
         * @return int
         */
        int getNumItems();

        /**
         * @brief Set the Num Items object
         * 
         * @param numItems 
         */
        void setNumItems(int numItems);

        /**
         * @brief Get the number of Moves Left
         * 
         * @return int 
         */
        int getMovesLeft();

        /**
         * @brief Set the number of Moves Left
         * 
         * @param moves 
         */
        void setMovesLeft(int moves);

        /**
         * @brief Adds the specified item to the inventory
         * 
         * @param item Item to add
         */
        void addItem(Item *item);

        /**
         * @brief checks to see if the inventory is full
         * 
         * @return true 
         * @return false 
         */
        bool inventoryIsFull();

        // current player position
        int currentX;
        int currentY;
};
//-------------//
#endif 
