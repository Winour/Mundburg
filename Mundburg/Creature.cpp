#include "Creature.h"
#include "Room.h"
#include "Exit.h"
#include <assert.h>


Creature::Creature(const char* name, const char* description, const char* long_description, Room* room, EntityType type):
Entity(name, description,long_description, room, type)
{
}


Creature::~Creature() {
}

Room* Creature::GetRoom() const {
    return (Room*)GetParent();
}

Item* Creature::GetWeapon() const {
    return _weapon;
}

Item* Creature::GetArmor() const {
    return _armor;
}

int Creature::GetLevel() const {
    return _level;
}

int Creature::GetMaxHp() const {
    return _max_hp;
}

int Creature::GetMaxMana() const {
    return _max_mana;
}

void Creature::SetArmor(Item* new_armor) {
    assert(new_armor);
    _armor = new_armor;
}

void Creature::SetWeapon(Item* new_weapon) {
    assert(new_weapon);
    _weapon = new_weapon;
}

bool Creature::IsAlive() const {
    return hp > 0;
}