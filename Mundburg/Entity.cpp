#include "Entity.h"
#include "Room.h"
#include "GlobalFunctions.h"



Entity::Entity(const char* name, const char* description,const char* long_description, Entity* parent, EntityType type) :
_name(name), _description(description),  _parent(parent), _type(type), _long_description(long_description){

    if (parent != nullptr) {
        parent->SetChild(this);
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
void Entity::ChangeParent(Entity* new_parent) {
    if (_parent != nullptr) {
        _parent->RemoveChild(this);
    }
    _parent = new_parent;
    if (_parent != nullptr) {
        _parent->SetChild(this);
    }
}

bool Entity::Find(const Entity* entity) const {
    for (int i = 0; i < _childs.size(); i++) {
        if (_childs[i] == entity) {
            return true;
        }
    }
    return false;
}

Entity* Entity::Find(const string name, EntityType type) const {
    for (int i = 0; i < _childs.size(); i++) {
        if (_childs[i]->_type == type) {
            if (Compare(_childs[i]->_name, name)) {
                return _childs[i];
            }
        }
    }
    return nullptr;
}
void Entity::FindAll(EntityType type, vector<Entity*>& container) const {
    for (int i = 0; i < _childs.size(); i++) {
        if (_childs[i]->_type == type) {
            container.push_back(_childs[i]);
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

std::string Entity::GetLongDescription() const {
    return _long_description;
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

void Entity::SetName(std::string& new_name) {
    _name = new_name;
}

void Entity::SetDescription(std::string& new_description) {
    _description = new_description;
}

void Entity::SetLongDescription(std::string& new_long_description) {
    _long_description = new_long_description;
}