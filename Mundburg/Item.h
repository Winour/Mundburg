#ifndef __Item__
#define __Item__

#include "Entity.h"
#include <iostream>
using namespace std;

enum class ItemType {
    NOT_PICKABLE,
    POTION,
    KEY,
    ARMOR,
    WEAPON,
    CONTAINER,
    FLUID,
    STANDARD,
    BOX
};

class Item : public Entity{
public:

    Item(const char* name, const char* description, const char* long_description, ItemType type, Entity* parent, int value, int weight);
    ~Item();

    int GetValue() const;
    int GetWeight() const;
    const ItemType item_type;

private:

    const int _value;
    const int _weight;


};

#endif // __Item__