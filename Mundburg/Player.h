#ifndef __Player__
#define __Player__

#include "Creature.h"
#include <iostream>
using namespace std;

class Player : public Creature {
public:
    Player(const char* name, const char* description, Room* room, EntityType type = EntityType::PLAYER);
    ~Player();

    bool Go(vector<string>& instructions);
	bool Open(vector<string>& instructions);
    void Look() const;

};

#endif //__Player__

