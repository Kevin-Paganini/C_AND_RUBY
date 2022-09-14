
#ifndef POSFUNCTIONS_H_
#define POSFUNCTIONS_H_



#include <cstdlib>
#include <time.h>
#include <iostream>

using namespace std;

class PosFunctions {
    public:
        /**
         * @brief Get a random empty cell
         * @param posToWriteTo 
         * @param xMax 
         * @param yMax 
         */
        static void getPos(int *posToWriteTo, int xMax, int yMax) {
            posToWriteTo[0] = rand() % xMax;
            posToWriteTo[1] = rand() % yMax;
        }
        /**
         * @brief does the entire direction choosing prompts
         * @param posOffset (which direction to move in)
         */
        static void directionChooser(int *posOffset) {
            char direction = 'z';
            // prompts user until correct direction is chosen
            while(direction == 'z') {
                cout << "Specify direction ('n', 's', 'e', or 'w'): ";
                cin >> direction;

                if(direction != 'n' && direction != 's' && direction != 'e' && direction != 'w') {
                    cout << endl << "Invalid direction, try again" << endl;
                    direction = 'z';
                }}


            switch (direction) {
                case 'n':
                    posOffset[1] = -1;
                    break;
                case 's':
                    posOffset[1] = 1;
                    break;
                case 'e':
                    posOffset[0] = 1;
                    break;
                case 'w':
                    posOffset[0] = -1;
                    break;
                default:
                    break;
            }

        }

        
};

#endif