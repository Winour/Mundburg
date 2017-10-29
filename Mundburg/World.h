#ifndef __World__
#define __World__

#include <string>
#include <vector>
#include <time.h>

#include "GlobalFunctions.h"

#include <iostream>
using namespace std;

class Entity;
class Creature;
class Player;
class NPC;

class World {
public:
    World();
    ~World();

    Game_States Update(vector<string>& instructions);
    Game_States ParseInstructions(vector<string>& instructions);
    void GameLoop();


private:
    Player* player;
    NPC* finalBoss;
    vector<Entity*> entities;
    clock_t tick_timer;
};

#endif 