using namespace std;
#include "player.h"
#include <string>
#include <iostream>

class GameObject;
class Item;

Player::Player(int startX, int startY, Forest *forest){
    currentX = startX;
    currentY = startY;
    numMovesLeft = 20;
    numItems = 5;
    inventory[0] = new Arrow(); 
    inventory[1] = new Arrow(); 
    inventory[2] = new Arrow();
    inventory[3] = new Arrow();
    inventory[4] = new NightHawk();
    this->forest = forest;

}

bool Player::move(int *pos){
    
    // position is in range
    if (pos[0] < 0 || pos[0] >= MAX_X || pos[1] < 0 || pos[1] >= MAX_Y){
        return false;
    }
    
    //move the player
    if (numMovesLeft > 0){
        numMovesLeft--;
        currentX = pos[0];
        currentY = pos[1];
        
        
        if (numMovesLeft < 0){
            numMovesLeft = 0;
        }
        
    }

    // check if something is in the new position
    if (forest->isPositionTaken(pos)){
        
        GameObject *thing = forest->grid[pos[0]][pos[1]]->obj;
        
        if(thing->getType() == "item"){
            forest->clearCell(pos[0], pos[1]);
        }

        // picks up item, trips trap, falls in hole...
        cout << thing->playerEncounter(this);
    }   
    
   
    return true;

}

void Player:: senseNearbyCells(){
    int xCheck = currentX;
    int yCheck = currentY;

    GameObject *thing;

    // looks at cells in a 3x3 grid with the player at the center
    for(int i = -1; i <= 1; i++) {
        if(xCheck + i >= 0 && i + xCheck < forest->MAX_X) {
            for(int j = -1; j <= 1; j++) {
                if(j + yCheck >= 0 && j + yCheck < forest->MAX_Y) {
                    if(i != 0 || j != 0) {
                        

                        if(forest->grid[xCheck + i][yCheck + j]->isOccupied() != nullptr) {
                            thing = forest->grid[xCheck + i][yCheck + j]->obj;

                            //senses what's nearby
                            cout << thing->getProximity() << endl;
                        }
                        

                    }
                }
            }
        }
    }
}

void Player::use(Item *item, int *pos){
    // Pass it along to item
    int indexToRemove = 100;
    
    for (int i = 0; i < numItems; i++){
        if (inventory[i]->getName() == item->getName()){
            indexToRemove = i;
        }
    }
    if (indexToRemove == 100){
        cout << "That item is not in your inventory";
    } else if (indexToRemove != 100){
        cout << item->use(forest, pos) << endl;
        numItems--;
        //vopying elements over 
        // the last element will still be there but thats ok cause it
        // will get overwritten
        for (int i = indexToRemove; i < inventorySize; i++){
            inventory[i] = inventory[i +1];
        }
    }
    
    
}

int Player::getNumItems(){
    return numItems;
}

void Player::setNumItems(int numItems){
    this->numItems = numItems;
}



int Player::getMovesLeft(){
    return numMovesLeft;
}

void Player::setMovesLeft(int moves){
    numMovesLeft = moves;
}

void Player::addItem(Item *item){
    if (numItems < inventorySize){
        inventory[numItems++] = item;
    }    
}

void Player::printInventory(){
    cout << "Inventory:" << endl;
    for (int i = 0; i < numItems; i++){
        cout << inventory[i]->getName() << endl;
    }
    
}

bool Player::inventoryIsFull(){
    if (numItems < inventorySize) {
        return false;
    }
    return true;
}


