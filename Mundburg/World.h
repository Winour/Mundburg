#ifndef __World__
#define __World__

#include <string>
#include <vector>

#include "GlobalFunctions.h"

#include <iostream>
using namespace std;

class Entity;
class Creature;
class Player;

class World {
public:
    World();
    ~World();

public:
    Game_States Tick(vector<string>& instructions);
    Game_States ParseInstructions(vector<string>& instructions);
    void GameLoop();
    Player* player;
    vector<Entity*> entities;
};

#endif 