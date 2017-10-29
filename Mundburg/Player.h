#ifndef __Player__
#define __Player__

#include <vector>
#include "Creature.h"

class Item;

class Player : public Creature {
public:
    Player(const char* name, const char* description, const char* long_description, Room* room);
    ~Player();

    bool Go(std::vector<std::string>& instructions);
	bool Open(std::vector<std::string>& instructions);
    bool Close(std::vector<std::string>& instructions);
    void Look() const;
    void Examine(std::vector<std::string>& instructions) const;
    void Inventory()const;
    void Equipment() const;
    void Equip(std::vector<std::string>& instructions);
    void Unequip(std::vector<std::string>& instructions);
    void Take(std::vector<std::string>& instructions, bool offset = false);
    void Unlock(std::vector<std::string>& instructions);
    void Lock(std::vector<std::string>& instructions);
    void Throw(std::vector<std::string>& instructions);
    void Attack(std::vector<std::string>& instructions);
    void DrinkPotion(std::vector<std::string>& instructions);

public:
    int long_descriptions = 0;                      // 0 = Normal Description, 1 = Short Description, 2 = Long Description

};

#endif //__Player__

