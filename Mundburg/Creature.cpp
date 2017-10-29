#include "Creature.h"
#include "Item.h"
#include "Room.h"
#include "Exit.h"
#include <assert.h>


Creature::Creature(const char* name, const char* description, const char* long_description, Room* room, int lvl, EntityType type) :
    Entity(name, description, long_description, room, type), _level(lvl), _exp(0), target(nullptr)
{
    _max_hp = hp = _level * 50;
    _max_mana = mana = _level * 10;
    attack = _level * 7;
    defense = _level * 5;
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

bool Creature::ReceiveAttack(int attack) {
    if ((defense / 2) < attack) {
        hp -= attack - (defense / 2);
    }
    return !IsAlive();
}

void Creature::Attack(Entity* objective) {
    if (objective->GetType() == EntityType::EXIT) {
        std::cout << "Why would you attack a door? To break it? Don't be lazy and search the key!!\n";
    }  else if (objective->GetType() == EntityType::NPC || objective->GetType() == EntityType::PLAYER) {
        int dmg;
        if (_weapon != nullptr) {
            dmg = attack + _weapon->GetValue();
        } else {
            dmg = attack;
        }
        std::cout << GetName() << " attacked with " << dmg << " power.\n";
        if (((Creature*)objective)->ReceiveAttack(dmg)) {
            ReceiveExp(((Creature*)objective)->GetLevel() * 40);
            ((Creature*)objective)->to_destroy = true;
            target = nullptr;
            objective->ChangeParent(nullptr);
        }
    } else {
        std::cout << "Eeeehhhh...better don't do that...\n";
    }
}

void Creature::ReceiveExp(int exp) {
    _exp += exp;
    while (_exp >= 40) {
        LevelUp();
    }
}

void Creature::LevelUp() {
    _level++;
    std::cout << std::endl << GetName() <<" level Up! Lvl " << _level << "!\n";
    _exp -= 40;
    _max_hp = hp = _level * 50;
    _max_mana = mana = _level * 10;
    attack = _level * 7;
    defense = _level * 5;
    std::cout << "Hp and Mana full restored!\n";
}

void Creature::SetTarget(Entity* objective) {
    if (objective->GetType() == EntityType::EXIT) {
        std::cout << "Why would you attack a door? To break it? Don't be lazy and search the key!!\n";
    } else if (objective->GetType() == EntityType::NPC || objective->GetType() == EntityType::PLAYER) {
        target = objective;
        if (((Creature*)target)->target == nullptr) {
            ((Creature*)target)->SetTarget(this);
        }
    } else {
        std::cout << "Eeeehhhh...better don't do that...\n";
    }
}

void Creature::Update() {
    if (IsAlive()) {
        if (target != nullptr) {
            if (GetRoom()->Find(target)) {
                Attack(target);
                return;
            } else {
                target = nullptr;
                return;
            }
        }
    }
}
