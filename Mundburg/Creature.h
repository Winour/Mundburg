#ifndef __Creature__
#define __Creature__

#include "Entity.h"

#include <string>

using namespace std;

class Item;
class Room;
class Exit;

class Creature : public Entity {
public:
    Creature(const char* name, const char* description,const char* long_description, Room* room, EntityType type = EntityType::CREATURE);
    ~Creature();
    void Poison();
    Room* GetRoom() const;
    Item* GetWeapon() const;
    Item* GetArmor() const;
    void SetArmor(Item* new_armor);
    void SetWeapon(Item* new_weapon);
    bool IsAlive() const;
    void ReciveDmg(int attack);



    bool _poisoned;
    int _level;
    int _max_hp;
    int _hp;
    int _max_mana;
    int _mana;
    int _attack;
    int _defense;
    Item* _weapon;
    Item* _armor;

};

#endif // __Creature__

