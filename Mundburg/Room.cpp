#include "Room.h"
#include "Exit.h"

#include <iostream>


Room::Room(const char* name, const char* description, const char* long_description) :
Entity(name, description, long_description, nullptr, EntityType::ROOM), _visited(false) {
}


Room::~Room() {
}

void Room::SetExit(Exit* exit) {
    for (size_t i = 0; i < exits.size(); i++) {                  // Looks for exit duplication
        if (exit == exits[i]) {
            return;
        }
    }
    exits.push_back(exit);
}

Exit* Room::GetExit(const string direction) const {
    for (size_t i = 0; i < exits.size(); i++) {
        if (exits[i]->GetDirection() == direction) {

            return exits[i];
        }
    }
    return nullptr;
}

void Room::GetExits() const {
    for (size_t i = 0; i < exits.size(); i++) {
        std::cout << exits[i]->GetName() << " ("<< exits[i]->GetDirection() <<")" <<std::endl;
    }
}

void Room::Look(bool full_description) {
    cout <<GetName() << std::endl << std::endl;
    if (full_description) {
        _visited = true;
        std::cout << GetDescription() << std::endl;
        for (size_t i = 0; i < GetChilds().size(); i++) {
            if (GetChilds()[i]->GetType() == EntityType::ITEM) {
                std::cout <<GetChilds()[i]->GetDescription() << std::endl;
            }
        }
        return;
    } else if (long_descriptions == 2) {
        _visited = true;
        std::cout << GetDescription() << std::endl;
        for (size_t i = 0; i < GetChilds().size(); i++) {
            if (GetChilds()[i]->GetType() == EntityType::ITEM) {
                std::cout << "-" << GetChilds()[i]->GetName() << std::endl;
            }
        }
        return;
    } else if (long_descriptions == 0 && _visited == false) {
        _visited = true;
        std::cout << GetDescription()<<std::endl;
        for (size_t i = 0; i < GetChilds().size(); i++) {
            if (GetChilds()[i]->GetType() == EntityType::ITEM) {
                std::cout << "-" << GetChilds()[i]->GetName() << std::endl;
            }
        }
        return;
    }
}