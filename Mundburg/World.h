#ifndef __World__
#define __World__

#include <string>
#include <vector>
#include <time.h>

#include "GlobalFunctions.h"


class Entity;
class Creature;
class Player;
class NPC;

class World {
public:
    World();
    ~World();

    Game_States Update(std::vector<std::string>& instructions);
    Game_States ParseInstructions(std::vector<std::string>& instructions);
    void GameLoop();


private:
    Player* player;
    NPC* finalBoss;
    std::vector<Entity*> entities;
    clock_t tick_timer;
};

#endif 