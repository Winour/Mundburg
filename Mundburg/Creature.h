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
    Creature(const char* name, const char* description,const char* long_description, Room* room, int lvl = 5, EntityType type = EntityType::CREATURE);
    ~Creature();

    Room* GetRoom() const;
    Item* GetWeapon() const;
    Item* GetArmor() const;
    int GetLevel() const;
    int GetMaxHp() const;
    int GetMaxMana() const;
    void SetArmor(Item* new_armor);
    void SetWeapon(Item* new_weapon);
    bool IsAlive() const;
    bool ReceiveAttack(int attack);
    void Attack(Entity* objective);
    void ReceiveExp(int exp);
    void LevelUp();
    void SetTarget(Entity* objective);
    void Update() override;

public:
    bool poisoned;
    int hp;
    int mana;
    int attack;
    int defense;
    Entity* target;

private:
    int _level;
    int _exp;
    int _max_hp;
    int _max_mana;
    Item* _weapon;
    Item* _armor;

};

#endif // __Creature__

