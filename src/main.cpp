//
//  main.cpp
//  Zork
//
//  Created by Tian Qiu on 11/29/15.
//  Copyright © 2015 Tian Qiu. All rights reserved.
//

#include <iostream>
#include "Map.hpp"
#include "main.hpp"

using namespace std;

int main(int argc, char**argv)
{
    cout << "xml opening" << endl;
    string filename = argv[1];
    ZorkMap = new Map();
    ZorkMap->loader(filename);

    while(ZorkMap->isRunning()){
    	ZorkMap->Run();
    }
    
    return 0;
}
