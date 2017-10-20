#ifndef __Player__
#define __Player__

#include <vector>
#include "Creature.h"
#include <iostream>
using namespace std;

class Item;

class Player : public Creature {
public:
    Player(const char* name, const char* description, const char* long_description, Room* room, EntityType type = EntityType::PLAYER);
    ~Player();

    bool Go(vector<string>& instructions);
	bool Open(vector<string>& instructions);
    bool Close(vector<string>& instructions);
    void Look() const;
    void Inventory()const;
    void Equipment() const;
    void Equip(vector<string>& instructions);

};

#endif //__Player__

