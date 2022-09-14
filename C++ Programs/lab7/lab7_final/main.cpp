/**
 * main.cpp
 * 
 * Kevin Paganini and Jackson Rolando
 * Spring 2022 
 */

#include <iostream>
#include <ctime>
#include <cstdlib>
#include "forest.h"
#include "gameobject.h"
#include "player.h"
#include "posfunctions.h"


using namespace std;


bool DEBUG = true;

string endstr = 
            "\n"
            "███▀▀▀██ ███▀▀▀███ ███▀█▄█▀███ ██▀▀▀\n"
            "██    ██ ██     ██ ██   █   ██ ██   \n"
            "██   ▄▄▄ ██▄▄▄▄▄██ ██   ▀   ██ ██▀▀▀\n"
            "██    ██ ██     ██ ██       ██ ██   \n"
            "███▄▄▄██ ██     ██ ██       ██ ██▄▄▄\n"
            "                                    \n"
            "███▀▀▀███ ▀███  ██▀ ██▀▀▀ ██▀▀▀▀██▄ \n"
            "██     ██   ██  ██  ██    ██     ██ \n"
            "██     ██   ██  ██  ██▀▀▀ ██▄▄▄▄▄▀▀ \n"
            "██     ██   ██  █▀  ██    ██     ██ \n"
            "███▄▄▄███    ▀█▀    ██▄▄▄ ██     ██▄\n";

string winStr = 
            "\n"
            " ,ggg,         gg                           ,ggg,      gg      ,gg                 \n"
            "dP\"\"Y8a        88                          dP\"\"Y8a     88     ,8P                  \n"
            "Yb, `88        88                          Yb, `88     88     d8'                  \n"
            " `\"  88        88                           `\"  88     88     88 gg                \n"
            "     88        88                               88     88     88 ""                \n"
            "     88        88    ,ggggg,   gg      gg       88     88     88 gg    ,ggg,,ggg,  \n"
            "     88       ,88   dP\"  \"Y8gggI8      8I       88     88     88 88   ,8\" \"8P\" \"8, \n"
            "     Y8b,___,d888  i8'    ,8I  I8,    ,8I       Y8    ,88,    8P 88   I8   8I   8I \n"
            "      \"Y88888P\"88,,d8,   ,d8' ,d8b,  ,d8b,       Yb,,d8\"\"8b,,dP_,88,_,dP   8I   Yb,\n"
            "           ,ad8888P\"Y8888P\"   8P'\"Y88P\"`Y8        \"88\"    \"88\" 8P\"\"Y88P'   8I   `Y8\n"
            "          d8P\" 88                                                                  \n"
            "        ,d8'   88                                                                  \n"
            "        d8'    88                                                                  \n"
            "        88     88                                                                  \n"
            "        Y8,_ _,88                                                                  \n"
            "         \"Y888P\"\n";

// ---- ITEM CHOOSING LOGIC ----//
void itemChooser(Player *player, char itemChoice){
    int pos[2];
    pos[0] = player->currentX;
    pos[1] = player->currentY;
    if (itemChoice == 'a'){
        Arrow *arrow = new Arrow();
        player->use(arrow, pos);
    } else if (itemChoice == 'b'){
        Bomb *bomb = new Bomb();
        player->use(bomb, pos);
    } else if (itemChoice == 'n'){
        NightHawk *nightHawk = new NightHawk();
        player->use(nightHawk, pos);
    }
}
//-------------//


// DIRECTION CHOOSING LOGIC ----//
void directionChooser(Player *player){
   int pos [2];
   pos[0] = player->currentX;
   pos[1] = player->currentY;
   int posToMove[2] = {};
   PosFunctions::directionChooser(posToMove);
   pos[0] += posToMove[0]; 
   pos[1] += posToMove[1];
   
   player->move(pos);
}
//-------------//

//------------------------//
// HELP MENU
//------------------------//
string getHelp() {
    string helpStr = 
        "\n"
        "*-----------HELP MENU-----------*\n"
        "The game is played in a 7x7 grid,\n"
        "with the origin at the top left:\n"
        "     0,0                7,0\n"
        "     +--------------------+\n"
        "     |__|__|__|__|__|__|__|\n"
        "     |__|__|__|__|__|__|__|\n"
        "     |__|__|__|__|__|__|__|\n"
        "     |__|__|__|__|__|__|__|\n"
        "     |__|__|__|__|__|__|__|\n"
        "     |__|__|__|__|__|__|__|\n"
        "     |__|__|__|__|__|__|__|\n"
        "     +--------------------+\n"
        "     0,7                7,7\n\n"

        "Your mission is to protect the\n"
        "Siberian forest and the creatures in it\n"
        "from the cruel, vodka-loving\n"
        "Wumpus, Vladimir. Find him in\n"
        "the forest, and kill him. \n\n"

        "------------ ITEMS --------------\n"
        "You have many tools at your \n"
        "disposal, some starting in your\n"
        "backpack, with more scattered\n"
        "about the forest.\n\n "

        "Your most basic tool, the \n"
        "arrow, fires one square \n"
        "in the specified direction, \n"
        "destroying what lies in it.\n\n"

        "Another tool you start with \n"
        "is the Nighthawk, a very useful \n"
        "bird which you've trained to scout \n"
        "the map around you.\n"
        "It scouts your entire row or column,\n"
        "depending on what you specify.\n\n"
        
        "Bombs, aka weapons of mass destruction,\n"
        "destroy the things in the 8 squares around\n"
        "you. Because of this item's power,\n"
        "you must find it in the forest.\n"
        "---------------------------------\n\n"

        "------------ TRAPS --------------\n"
        "There are several hazards in the \n"
        "forest, some of which will kill\n"
        "you immediately. \n\n"
        
        "Because of some tragic events of\n"
        "which we will not speak, bottomless\n"
        "pits exist throughout the forest. \n"
        "You will feel a breeze if there's \n"
        "one nearby, and if you fall in, \n"
        "you'll fall for so long that you\n"
        "starve to death. Avoid these, \n"
        "they cannot be destroyed\n\n"
        
        "Locals also set traps for our \n"
        "skyrocketing bear population, \n"
        "so watch out for those as well. \n"
        "Shooting one of these will destroy\n"
        "it. \n"
        "---------------------------------\n\n"

        "--------- OTHER HAZARDS ----------\n"
        "Tree portals, which make a sort of \n"
        "sparkling noise, will teleport you to\n"
        "a random part of the forest, which \n"
        "could be occupied by a trap or Vladimir\n"
        "himself.\n\n"

        "Swiper the fox, a good-for-nothing\n"
        "pickpocketer, can steal a number of\n"
        "items from your inventory, so watch \n"
        "out. \n"
        "----------------------------------\n\n"

        "Good luck on your journey, we're all\n"
        "counting on you. It's cold out there,\n"
        "so make sure to warm up by a campfire.\n\n"

        "Stay vigilant.\n"
        "You want to make sure to kill Vladimir\n"
        "before you meet your own demise."
        "";

    return helpStr;
}


//---- MAIN GAME LOOP ----//
void gameLoop(){
    Forest *forest = new Forest();
    int startPos[2];

    forest->randomEmptyPosition(startPos);

    Player *player = new Player(startPos[0], startPos[1], forest);
    bool playerAlive = true;
    bool win = false;


    if(DEBUG) {
        cout << "Hello Dr. Hasker, this map is for your convenience. It can be turned off by setting DEBUG to false at the top of main.cpp :)" <<endl;
    }
    

    while(playerAlive && !win){
        if (DEBUG) {
            forest->printMap(player->currentX, player->currentY);
        }

        // looks at everything adjacent
        player->senseNearbyCells();

        cout << endl << "Current x pos: " << player->currentX << endl;
        cout << "Current y pos: " << player->currentY << endl;
        cout << "Number of moves left: " << player->getMovesLeft() << endl;

        cout << "Press 'm' to move or 'u' to use a item, 'h' for help, 'i' to print inventory: ";
        char userInput;
        cin >> userInput;

        if (userInput == 'm'){
            directionChooser(player);

        } else if (userInput == 'u'){
            player->printInventory();
            char itemChoice;
            cout << "Press 'a' for arrow, 'b' for bomb or 'n' for nighthawk: ";
            cin >> itemChoice;
            if (itemChoice == 'a' || itemChoice == 'b' || itemChoice == 'n'){
                itemChooser(player, itemChoice);
            } else {
                cout << "That was some not so good input" << endl;
            }

        } else if (userInput == 'h') {
            cout << getHelp() << endl;

        } else if (userInput == 'i') {
            player->printInventory();
            
        } else {
            cout << "That was some not so good input" << endl;
        }

        // death
        if (player->getMovesLeft() <= 0){
            cout << endl << "You've frozen in Siberia" << endl;
            cout << endstr;
            playerAlive = false;
        }

        // win
        if (forest->boss->isDead()){
            cout << "You have defeated the mighty Vladimir, now all the majestic creatures are free" << endl;
            cout << winStr << endl;
            win = true;
        }
        
        cout << endl;
    }


}
//-------------//


//---- MAIN LOOP ----//
int main() {
    srand(time(NULL));
    char inChar;
    string welcomePrompt = "Welcome to the Dark Forest Game";
    string playAgainPrompt = "Press any key to play or press q to stop";
    cout << welcomePrompt << endl;
    cout << playAgainPrompt << endl;
    while(cin >> inChar && tolower(inChar) != 'q') {
        cout << endl;
        gameLoop();
        cout << playAgainPrompt << endl;
    }
    cout << "Exiting..." << endl;
    exit(0);
}
//-------------//

