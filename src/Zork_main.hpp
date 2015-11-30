#ifndef _ZORK_MAIN_
#define _ZORK_MAIN_


#include <list>
/*#include "Object.hpp"
#include "Zork_Def.hpp"
#include "Room.hpp"
#include <functional>
#include "Map.hpp"
#include "Container"
 */
#include <string>
#include <stdio.h>
#include <iostream>

#include <iterator>
#include <vector>
#include <map>
#include <queue>
#include "rapidxml/rapidxml.hpp"

using namespace std;
using namespace rapidxml;


/*
Map ZorkMap;
Container Inventory;
Room* CurRoomPtr;
Map loadMap(string& filename);
*/
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
