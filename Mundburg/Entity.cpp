#include "Entity.h"



Entity::Entity(const char* name, const char* description, EntityType type, Entity* parent ) :
_name(name), _description(description),  _parent(parent), _type(type) {

    if (parent != nullptr) {
        parent->SetParent(parent);
    }
}

Entity::~Entity() {
}

void Entity::RemoveChild(Entity* child) {
    for (int i = 0; i < _childs.size(); i++) {
        if (_childs[i] == child) {
            _childs.erase(_childs.begin() + i);
        }
    }
}

std::string Entity::GetName() const {
    return _name;
}

std::string Entity::GetDescription() const {
    return _description;
}

Entity* Entity::GetParent() const {
    return _parent;
}

vector<Entity*> Entity::GetChilds() const {
    return _childs;
}

EntityType Entity::GetType() const {
    return _type;
}

void Entity::SetChild(Entity* child) {
    for (int i = 0; i < _childs.size(); i++) {                  // Looks for child duplication
        if (child == _childs[i]) {
            return;
        }
    }
    _childs.push_back(child);
}

void Entity::SetParent(Entity* parent) {
    _parent = parent;
}

void Entity::SetName(std::string new_name) {
    _name = new_name;
}

void Entity::SetDescription(std::string new_description) {
    _description = new_description;
}