#ifndef __Item__
#define __Item__

#include "Entity.h"
#include <iostream>
using namespace std;

enum class Item_type {
    NOT_PICKABLE,
    POTION,
    KEY,
    ARMOR,
    WEAPON,
    CONTAINER,
    FLUID,
    STANDARD
};

class Item : public Entity{
public:

    Item(const char* name, const char* description, const char* long_description, Item_type type, Entity* parent, int value, int weight);
    ~Item();

    int GetValue() const;
    int GetWeight() const;
    Item_type GetItemType() const;

    int _value;
    int _weight;
    Item_type _type;

};

#endif // __Item__