using namespace std;
#include "gameobject.h"
#include "player.h"
#include "forest.h"
#include "posfunctions.h"
#include <time.h>
#include <iostream>

//-----------------------------------//
// GAMEOBJECT Class implementation
//-----------------------------------//


// RETURNS NAME OF GAMEOBJECT
string GameObject::getName() {
    return name;
}

// RETURNS PROXIMITY PROMPT OF GAMEOBJECT
string GameObject::getProximity() {
    return proximityPrompt;
}

// RETURNS TYPE OF GAMEOBJECT
string GameObject::getType() {
    return type;
}

// RETURNS IF GAMEOBJECT IS DESTROYABLE
bool GameObject::isDestroyable() {
    return destroyable;
}




//-------------//

//-----------------------------------//
// BOSS Class implementation
//-----------------------------------//

//---- BOSS CONSTRUCTOR ----//
// PARAM: NONE
//-------------//
Boss::Boss() {
    name = "Vladimir";
    proximityPrompt = "You can smell the scent of vodka";
    encounterPrompt = "He found you, and your soul has been consumed";
    destroyable = true;
    dead = false;
    type = "boss";
}
//-------------//


// RETURNS IF BOSS IS DEAD
bool Boss::isDead() {
    return dead;
}
//-------------//

//---- KILLS BOSS ----//
void Boss::destroy() {
    dead = true;
}
//-------------//

//---- PLAYER ENCOUNTER FOR BOSS ----//
string Boss::playerEncounter(Player *player) {
    player->setMovesLeft(0);
    return encounterPrompt;
}

//-----------------------------------//
// THIEF class implementation
//-----------------------------------//

Thief::Thief(int skill) {
    this->skill = skill;
    name = "Swiper";
    proximityPrompt = "You can smell a fox...";
    encounterPrompt = "Swiper has swiped. Check your inventory.";
    destroyable = true;
    type = "thief";
}

void Thief::destroy() {
    cout << name << " has been killed." << endl;
    delete(this);
}

string Thief::playerEncounter(Player *player) {
    stealFrom(player);
    return encounterPrompt;
}

void Thief::stealFrom(Player *player) {
    int numItems = player->getNumItems();
    player->setNumItems(numItems / 2);
}

//-----------------------------------//
// CAMPFIRE Implementation
//-----------------------------------//
CampFire::CampFire(){
    name = "Camp Fire";
    proximityPrompt = "You feel warmth nearby";
    encounterPrompt = "The heat is giving you life and you can continue with your quest";
    destroyable = true;
    type = "campfire";
}

void CampFire::destroy(){
    cout << name << " has been put out." << endl;
    delete(this);
}

// increases player's moves left
string CampFire::playerEncounter(Player *player){
    player->setMovesLeft(player->getMovesLeft() + numMovesToRestore);
    return encounterPrompt;
}


//-----------------------------------//
// Traps implementation
//-----------------------------------//
void Trap::destroy() {
    if(isDestroyable()) {
        cout << name << " has been disarmed." << endl;
        delete(this);
    }
}

string Trap::playerEncounter(Player *player) {
    kill(player);
    return encounterPrompt;
}

void Trap::kill(Player *player) {
    player->setMovesLeft(0);
}

//-----------------------------------//
// BearTrap class implementation
//-----------------------------------//
BearTrap::BearTrap() {
    name = "Bear Trap";
    proximityPrompt = "What is that? Bear bait?";
    encounterPrompt = "CHOMP, you've lost your leg and bled out";
    destroyable = true;
    type = "beartrap";
}

//-----------------------------------//
// Pit class implementation
//-----------------------------------//
Pit::Pit() {
    name = "Pit";
    proximityPrompt = "You feel a breeze";
    encounterPrompt = "You've fallen from a high place";
    destroyable = false; //cannot destroy a bottomless pit
    type = "pit";
}

//-----------------------------------//
// TreePortal class implementation
//-----------------------------------//
TreePortal::TreePortal(int xMax, int yMax) {
    name = "tree portal";
    proximityPrompt = "**Magical Twinkles**";
    encounterPrompt = "The tree portal has moved you to: ";
    destroyable = true;
    type = "treeportal";
    this->xMax = xMax;
    this->yMax = yMax;
}

void TreePortal::destroy() {
    cout << getName() << " has been destroyed." << endl;
    delete(this);
}

// Moves the player to a random postiton on the map and the player 
//   encounters whatever lies there
string TreePortal::playerEncounter(Player *player) {
    int posToWrite[2];
    PosFunctions::getPos(posToWrite, xMax, yMax);
    cout << encounterPrompt;
    cout << posToWrite[0] << ", " << posToWrite[1] << endl; 
    player->move(posToWrite);
    return "";
}

//-----------------------------------//
// ITEM class implementations
//-----------------------------------//
void Item::destroy() {
    cout << getName() << " has been destroyed." << endl;
    delete(this);
}

// item pickup
string Item::playerEncounter(Player *player) {
    if(!player->inventoryIsFull()) {
        player->addItem(this);
        
        return encounterPrompt;
    }

    return "Your inventory is full";
}


// If gameobject is destroyable it gets destroyed
void Item::attemptDestroy(Cell *cell, Forest *forest, int *pos) {
    if(cell->isTaken()) {
        GameObject *objInCell = cell->isOccupied();
        if(objInCell->isDestroyable()) {
            objInCell->destroy();
            forest->clearCell(pos[0], pos[1]);
        }
    }
}

Arrow::Arrow() {
    name = "Arrow";
    proximityPrompt = "Hey, there's an --> arrow.";
    encounterPrompt = "You picked up an arrow.";
    destroyable = true;
    type = "item";
}

//lets the user choose the direction to shoot, then 
//  destroys what is in that cell if applicable
string Arrow::use(Forest *forest, int *playerPos) {
    int posOffset[2] = {0};
    PosFunctions::directionChooser(posOffset);
    posOffset[0] += playerPos[0];
    posOffset[1] += playerPos[1];
    

    Cell *cell = forest->grid[posOffset[0]][posOffset[1]];
    attemptDestroy(cell, forest, posOffset);
    return "Arrow has been used";
}

//-----------------------------------//
// Bomb class implementation
//-----------------------------------//

Bomb::Bomb() {
    name = "Bomb";
    proximityPrompt = "A weapon of mass destruction is around you...";
    encounterPrompt = "You have picked up a bomb...";
    destroyable = true;
    type = "item";
}

string Bomb:: use(Forest *forest, int *playerPos) {

    // looks at all surrounding cells, destroying them if applicable
    for(int i = -1; i <= 1; i++) {
        if(playerPos[0] + i >= 0 && i + playerPos[0] < forest->MAX_X) {
            for(int j = -1; j <= 1; j++) {
                if(j + playerPos[1] >= 0 && j + playerPos[1] < forest->MAX_Y) {
                    if(i != 0 || j != 0) {

                        int attemptPos[2] = {playerPos[0] + i, playerPos[1] + j};
                        Cell *cell = forest->grid[attemptPos[0]][attemptPos[1]];
                        attemptDestroy(cell, forest, attemptPos);
                        
                    }
                }
            }
        }
    }

    return "Bomb has been used";
}


//-----------------------------------//
// NightHawk class implementation
//-----------------------------------//

NightHawk:: NightHawk(){
    name = "NightHawk";
    proximityPrompt = "You can hear a nighthawk's screech near you...";
    encounterPrompt = "You have picked up a nighthawk...";
    destroyable = true;
    type = "item"; 
}
// Searches a row or column and returns string of gameobjects in path
string NightHawk:: use(Forest *forest, int *playerPos) {
    char direction;
    cout << "Specify direction ('v' for vertical, 'h' for horizontal): ";
    cin >> direction;

    if(direction != 'h' && direction != 'v') {
        return "Invalid direction, try again";
    }

    string itemString;

    if(direction == 'h') {
        // searches the whole row
        for(int i = 0; i < forest->MAX_X; i++) {
            if (forest->grid[i][playerPos[1]]->isOccupied() != nullptr){
                 itemString += forest->grid[i][playerPos[1]]->isOccupied()->getName() + ", ";
            }
           
        }
    } else {
        // searches the whole column
        for(int i = 0; i < forest->MAX_Y; i++) {
            if (forest->grid[playerPos[0]][i]->isOccupied() != nullptr){
                itemString += forest->grid[playerPos[0]][i]->isOccupied()->getName() + ", ";
            }
            
        }
    }
    
    string directionString = direction == 'h' ? "row" : "column";
    string endstr;

    if(itemString.length() == 0) {
        endstr = "Nothing has been found";
    } else {
        endstr = itemString.substr(0, itemString.length() - 2) + " present in your " + directionString;
    }

    return "Nighthawk has been used: " + endstr;
}

