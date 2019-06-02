//
//  Asteroids
//
//  Created by Miles di Prata on 2018-04-06.
//  Copyright © 2018 Miles di Prata. All rights reserved.
//

#include <iostream>
#include "AsteroidsGame.h"

using namespace std;

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

int main(const int argc, const char * argv[])
{
    // cout << "Press any key to start the game...";
    // cin.get();
    AsteroidsGame game;
    game.InitalizeGraphics("Asteroids", SCREEN_WIDTH, SCREEN_HEIGHT);
    game.Start();
    return 0;
}
