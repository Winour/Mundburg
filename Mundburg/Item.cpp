#include "Item.h"



Item::Item(const char* name, const char* description, const char* long_description, Item_type type, Entity* parent, int value, int weight) :
    Entity(name, description,long_description, parent, EntityType::ITEM), _value(value), _weight(weight), _type(type)
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

Item_type Item::GetItemType() const {
    return _type;
}