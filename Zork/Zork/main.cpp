//
//  main.cpp
//  Zork
//
//  Created by Tian Qiu on 11/29/15.
//  Copyright © 2015 Tian Qiu. All rights reserved.
//

#include <iostream>
#include "Zork_main.hpp"

using namespace std;

int main(void)
{
    cout << "xml opening" << endl;
    Game * game = new Game("rapidxml/sample.xml");
    
    if(game->gameReady) {
        cout << "Game starting" << endl;
        game->startGame();
    }
    
    delete game;
    return 0;
}