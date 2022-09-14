using namespace std;

#include <string>
#include <ctime>
#include <cstdlib>

#ifndef FOREST_H_
#define FOREST_H_

#include "gameobject.h"

class GameObject;
class Boss;

//---- CELL DEFINITION ----//
class Cell {
    public:
        /**
         * @brief Construct a new Cell object
         * 
         * @param type 
         * @param x 
         * @param y 
         * @param obj 
         */
        Cell(string type, int x, int y, GameObject *obj);
        /**
         * @brief Is the cell occupied
         * 
         * @return GameObject* 
         */
        GameObject *isOccupied();
        /**
         * @brief prints the cell position
         * and gameobject
         */
        void printCell();
        /**
         * @brief Set the GameObject
         * 
         * @param type 
         * @param obj 
         * @return boolean 
         */
        bool setObject(string type, GameObject *obj);
        /**
         * @brief The gameobject the cell holds
         * 
         */
        GameObject *obj;
        /**
         * @brief is the cell taken
         * 
         * @return bool
         */
        bool isTaken();
        /**
         * @brief Set the Taken object
         * 
         * @param taken 
         */
        void setTaken(bool taken);
        /**
         * @brief Destroy the Cell object
         * 
         */
        ~Cell();

    protected:
        /**
         * @brief x position of the cell
         * 
         */
        int x;
        /**
         * @brief y position of the cell
         * 
         */
        int y;
        /**
         * @brief is the cell taken?
         * 
         */
        bool taken;
        /**
         * @brief type of the Gameobject
         * 
         */
        string type;
        
};
//-------------//

//---- FOREST DEFINITION ----//
class Forest {

    public:
        /**
         * @brief Construct a new Forest object
         */
        Forest();
        /**
         * @brief print the forest
         */
        void printForest();
        /**
         * @brief is the position taken
         * @param position array
         * @return bool
         */
        bool isPositionTaken(int *pos);
        /**
         * @brief gives a random empty position in the forest
         * @param position array to fill
         */
        void randomEmptyPosition(int *pos);
        /**
         * @brief clears the specified cell
         * and replaces with empty cell
         * @param x 
         * @param y 
         */
        void clearCell(int x, int y);
        /**
         * @brief adds game object to grid
         * @param obj 
         */
        void addToGrid(GameObject *obj);
        /**
         * @brief forest x size
         */
        static int constexpr MAX_X = 7;
        /**
         * @brief forest y size
         */
        static int constexpr MAX_Y = 7;
        /**
         * @brief grid of cells for forest
         */
        Cell *grid[MAX_X][MAX_Y];  
        /**
         * @brief The boss of the grid
         */
        Boss *boss;
        /**
         * @brief Prints map for debugging
         * @param x (player position)
         * @param y (player position)
         */
        void printMap(int x, int y);

};
//-------------//




#endif 