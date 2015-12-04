#ifndef _ZORK_MAIN_
#define _ZORK_MAIN_


#include "Object.hpp"
#include "Zork_Def.hpp"
#include "Room.hpp"
#include <functional>
#include "Map.hpp"
#include "Container.hpp"
#include <string>
#include <iostream>


using namespace std;
using namespace rapidxml;


Container Inventory(emptystr,emptystr,emptystr);
Room* CurRoomPtr = nullptr;

Map ZorkMap;

class Game {
public:
    
    Game(string);
    virtual ~Game();
    void startGame();
    bool gameReady = false;
    string currentRoom;
    
private:
    bool loadXML(string filename);
    
};


#endif
