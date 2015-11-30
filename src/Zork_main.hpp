#ifndef _ZORK_MAIN_
#define _ZORK_MAIN_

#include <list>
#include "Object.hpp"
#include "Zork_Def.hpp"
#include "Room.hpp"
#include <functional>
#include "Map.hpp"
#include "Container.hpp"

using namespace std;

Map ZorkMap;

Container Inventory;
Room* CurRoomPtr;

Map loadMap(string& filename);


#endif
