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
    Creature(const char* name, const char* description, Room* room, EntityType type = EntityType::CREATURE);
    ~Creature();
    void Poison();
    Room* GetRoom() const;
    virtual void Look() const;


    bool _poisoned;
    int _level;
    float _max_hp;
    float _hp;
    float _max_mana;
    float _mana;
    float _defense;

};

#endif // __Creature__

