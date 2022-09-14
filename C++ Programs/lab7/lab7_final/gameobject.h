/**
 * @file GameObject.h
 * @author Kevin Paganini paganinik
 * @brief 
 * @version 0.1
 * @date 2022-04-21
 * 
 * @copyright Copyright (c) 2022
 * 
 */

using namespace std;

#ifndef GAMEOBJ_H_
#define GAMEOBJ_H_


#include <string>
#include "player.h"
#include "forest.h"
#include "posfunctions.h"

class Cell;
class Player;

class GameObject {

    public:
        /**
         * @brief Get the Name object
         * @return name of the GameObject
         */
        string getName();
        /**
         * @brief Get the Proximity prompt
         * @return string 
         */
        string getProximity();

        /**
         * @brief Get the Type of the gameobject
         * @return string 
         */
        string getType();
        /**
         * @brief Is the object destroyable
         * @return bool
         */
        bool isDestroyable();

        /**
         * @brief performs actions altering the state of the player, 
         * returning a prompt as a result of the encounter.
         * 
         * @param player Player whose state will be altered
         * @return a prompt to be printed as a result of 
         * the encounter
         */

        //Needs to be implemented by children
        virtual string playerEncounter(Player *player) = 0;
        virtual void destroy() = 0;
        virtual ~GameObject() {};
    
    protected:
        /**
         * @brief Name of the objec
         */
        string name;
        /**
         * @brief The proximity prompt for the object
         */
        string proximityPrompt;
        /**
         * @brief The encounter prompt for the object
         */
        string encounterPrompt;
        /**
         * @brief Is the object destroyable
         */
        bool destroyable;
        /**
         * @brief the type of the object
         */
        string type;
};


//---- BOSS DEFINITION ----//
class Boss: public GameObject {
    public:
        /**
         * @brief Construct a new Boss object
         */
        Boss();
        /**
         * @brief is the boss dead?
         * @return bool
         */
        bool isDead();
        /**
         * @brief Boss kills player when player enters cell
         * @param player 
         * @return string 
         */
        string playerEncounter(Player *player) override;
        /**
         * @brief Destroys the Boss
         */
        void destroy() override;
    private:
        /**
         * @brief Is the boss alive or dead
         */
        bool dead;
};

//---- THIEF DEFINITION ----//
class Thief : public GameObject {
    public:
        /**
         * @brief Construct a new Thief object
         * @param skill 
         */
        Thief(int skill);
        /**
         * @brief destroys the thief
         */
        void destroy() override;
        /**
         * @brief Thief steals from player when player
         * enters cell
         * @param player 
         * @return string 
         */
        string playerEncounter(Player *player) override;
    private:
        /**
         * @brief steals from the player
         * @param player 
         */
        void stealFrom(Player *player);
        /**
         * @brief how many items it steals
         */
        int skill;
};


//---- TREEPORTAL DEFINITION ----//
class TreePortal : public GameObject {
    public:
        /**
         * @brief Construct a new Tree Portal object
         * @param xMax 
         * @param yMax 
         */
        TreePortal(int xMax, int yMax);
        /**
         * @brief destroys the tree portal
         * when the player uses bomb or arrow
         */
        void destroy() override;
        /**
         * @brief Moves player from one position
         * to another
         * @param player 
         * @return string 
         */
        string playerEncounter(Player *player) override;
    private:
        /**
         * @brief x and y coordinates it can move the player to
         */
        int xMax, yMax;
};
//-------------//

//---- CAMPFIRE DEFINITION ----//
class CampFire : public GameObject{
    public:
        /**
         * @brief Construct a new Camp Fire object
         */
        CampFire();
    private:
        /**
         * @brief How many number player gets back
         */
        static int constexpr numMovesToRestore = 10;
        /**
         * @brief restores moves to player
         * @param player 
         * @return string 
         */
        string playerEncounter(Player *player) override;
        /**
         * @brief destroys the campfire
         */
        void destroy() override;
};
//-------------//

//----TRAPS----//
class Trap : public GameObject {
    public:
        /**
         * @brief destroy the trap
         */
        void destroy() override;
        /**
         * @brief calls the correct trap function
         * @param player 
         * @return string 
         */
        string playerEncounter(Player *player) override;
    private:
        /**
         * @brief Kills the player
         * @param player 
         */
        void kill(Player *player);
};
//---- BEAR TRAP ----//
class BearTrap : public Trap {
    public:
        /**
         * @brief Construct a new Bear Trap object
         */
        BearTrap();
};

//---- PIT ----//
class Pit : public Trap {
    public:
        /**
         * @brief Construct a new Pit object
         */
        Pit();
};
//-------------//

//----ITEMS----//
class Item: public GameObject {
    public:
        /**
         * @brief uses a item
         * (Strategy Pattern for the win)
         * @param forest 
         * @param pos 
         * @return string 
         */
        virtual string use(Forest *forest, int *pos) = 0;
        /**
         * @brief Destroys the item if
         * its destroyable
         */
        void destroy() override;
        /**
         * @brief player picks up item
         * @param player 
         * @return string 
         */
        string playerEncounter(Player *player) override;
        /**
         * @brief attempts to destroy the item
         * @param cell 
         * @param forest 
         * @param pos 
         */
        void attemptDestroy(Cell *cell, Forest *forest, int *pos);
};



class Bomb: public Item {
    public:
        /**
         * @brief Construct a new Bomb object
         */
        Bomb();
        /**
         * @brief Clears all surrounding cells
         * @param forest 
         * @param playerPos 
         * @return string 
         */
        string use(Forest *forest, int *playerPos) override;
    };

class Arrow: public Item {
    public: 
        /**
         * @brief Construct a new Arrow object
         */
        Arrow();
        /**
         * @brief Uses an arrow
         * @param forest 
         * @param playerPos 
         * @return string 
         */
        string use(Forest *forest, int *playerPos) override;
};

class NightHawk: public Item {
    public:
        /**
         * @brief Construct a new Night Hawk object
         */
        NightHawk();
        /**
         * @brief Uses a nighthawk
         * @param forest 
         * @param playerPos 
         * @return string 
         */
        string use(Forest *forest, int *playerPos) override;
};
//-------------//


#endif