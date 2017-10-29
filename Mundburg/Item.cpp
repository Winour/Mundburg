#include "Item.h"


Item::Item(const char* name, const char* description, const char* long_description, ItemType type, Entity* parent, int value, int weight) :
    Entity(name, description,long_description, parent, EntityType::ITEM), _value(value), _weight(weight), item_type(type)
{
}


Item::~Item() {
}

int Item::GetValue() const {
    return _value;
}

int Item::GetWeight() const {
    return _weight;
}