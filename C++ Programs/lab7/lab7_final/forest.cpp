
using namespace std;
#include "forest.h"
#include <iostream>

//---- CELL DECLARATION ----//
Cell::Cell(string type, int x, int y, GameObject *obj){
    type = type;
    x = x;
    y = y;
    this->obj = obj;
    taken = false;
}

Cell::~Cell(){
    delete(obj);
}

// the game object contained in the cell
GameObject *Cell::isOccupied(){
    return obj;
}

bool Cell::isTaken() {
    return taken;
}

void Cell::setTaken(bool taken) {
    this->taken = taken;
}

Forest::Forest(){
    for (int i = 0; i < MAX_X; i++){
        for (int j = 0; j < MAX_Y; j++){
            grid[i][j] = new Cell("   ", i, j, nullptr);
        }
    }
    
    // Boss initialize
    Boss *vladimir = new Boss();
    boss = vladimir;
    addToGrid(vladimir);


    // Thief initialize
    GameObject *thief = new Thief(5);
    addToGrid(thief);

    // 5 arrows
    GameObject *arrow1 = new Arrow();
    addToGrid(arrow1);
    GameObject *arrow2 = new Arrow();
    addToGrid(arrow2);
    GameObject *arrow3 = new Arrow();
    addToGrid(arrow3);
    GameObject *arrow4 = new Arrow();
    addToGrid(arrow4);
    GameObject *arrow5 = new Arrow();
    addToGrid(arrow5);

    // 2 bombs
    GameObject *bomb1 = new Bomb();
    addToGrid(bomb1);
    GameObject *bomb2 = new Bomb();
    addToGrid(bomb2);    
    // Campfire initialize
    GameObject *campfire = new CampFire();
    addToGrid(campfire);
    // 1 nightHawk
    GameObject *nightHawk = new NightHawk();
    addToGrid(nightHawk);
    // 2 TreePortal
    GameObject *portal1 = new TreePortal(MAX_X, MAX_Y);
    addToGrid(portal1);
    GameObject *portal2 = new TreePortal(MAX_X, MAX_Y);
    addToGrid(portal2);

    // 4 pits
    GameObject *pit1 = new Pit();
    addToGrid(pit1);
    // 4 bear traps
    GameObject *bearTrap1 = new BearTrap();
    addToGrid(bearTrap1);   
    GameObject *bearTrap2 = new BearTrap();
    addToGrid(bearTrap2);
    GameObject *bearTrap3 = new BearTrap();
    addToGrid(bearTrap3);
    GameObject *bearTrap4 = new BearTrap();
    addToGrid(bearTrap4);
}

void Forest::clearCell(int x, int y){
    grid[x][y] = new Cell("   ", x, y, nullptr);
}

bool Forest::isPositionTaken(int *pos){
    // checks if there's a game object
    if (grid[pos[0]][pos[1]]->isTaken()){
        
        return true;
    }
    return false;
}

void Forest::addToGrid(GameObject *obj){
    //for random placement of objects at game start
    int pos[2];
    PosFunctions::getPos(pos, MAX_X, MAX_Y);
    while (isPositionTaken(pos)){
        PosFunctions::getPos(pos, MAX_X, MAX_Y);
    }
    Cell *cell = new Cell(obj->getType(), pos[0], pos[1], obj);
    cell->setTaken(true);
    grid[pos[0]][pos[1]] = cell;
    
}

void Forest::randomEmptyPosition(int *pos){
    PosFunctions::getPos(pos, MAX_X, MAX_Y);
    while (isPositionTaken(pos)){
        PosFunctions::getPos(pos, MAX_X, MAX_Y);
    }
}

void Forest::printMap(int x, int y){
    cout << "+-----------------------------------------------------------------------+";
    for (int i = 0; i < MAX_Y; i++){

        cout << endl;

        for (int j = 0; j < MAX_X; j++){
            cout << " | ";
            cout << j << ", " << i;
            if(grid[j][i]->isTaken()){
                cout << grid[j][i]->isOccupied()->getName().substr(0,3);
            } else {
                //player position
                if (i == y && j == x){
                    cout << " P ";
                } else {
                    cout << "   ";
                }  
            }
        }
        cout << " |";
    }
    cout << endl;
    cout << "+-----------------------------------------------------------------------+";
    cout << endl;

}


