#include "Creature.h"
#include "Room.h"
#include "Exit.h"


Creature::Creature(const char* name, const char* description, const char* long_description, Room* room, EntityType type):
Entity(name, description,long_description, room, type)
{
}


Creature::~Creature() {
}

void Creature::Poison() {
    

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

void Creature::SetArmor(Item* new_armor) {
    _armor = new_armor;
}

void Creature::SetWeapon(Item* new_weapon) {
    _weapon = new_weapon;
}

bool Creature::IsAlive() const {
    return _hp > 0;
}

void Creature::ReciveDmg(int attack) {
    _hp -= attack - (attack * (_defense/100));
}