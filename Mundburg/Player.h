#ifndef __Player__
#define __Player__

#include <vector>
#include "Creature.h"
#include <iostream>
using namespace std;

class Item;

class Player : public Creature {
public:
    Player(const char* name, const char* description, const char* long_description, Room* room);
    ~Player();

    bool Go(vector<string>& instructions);
	bool Open(vector<string>& instructions);
    bool Close(vector<string>& instructions);
    void Look() const;
    void Examine(vector<string>& instructions) const;
    void Inventory()const;
    void Equipment() const;
    void Equip(vector<string>& instructions);
    void Unequip(vector<string>& instructions);
    void Take(vector<string>& instructions, bool offset = false);
    void Unlock(vector<string>& instructions);
    void Lock(vector<string>& instructions);
    void Throw(vector<string>& instructions);
    void Attack(vector<string>& instructions);
    void DrinkPotion(vector<string>& instructions);

public:
    int long_descriptions = 0;                      // 0 = Normal Description, 1 = Short Description, 2 = Long Description

};

#endif //__Player__

