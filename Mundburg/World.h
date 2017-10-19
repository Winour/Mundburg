#ifndef __World__
#define __World__

#include <string>
#include <vector>

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
    bool Tick(vector<string>& instructions);
    bool ParseInstructions(vector<string>& instructions);
    void GameLoop();
    Player* player;
    vector<Entity*> entities;
};

#endif 