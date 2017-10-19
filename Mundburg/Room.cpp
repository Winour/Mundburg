#include "Room.h"
#include "Exit.h"

#include <iostream>


Room::Room(const char* name, const char* description) :
Entity(name, description, nullptr, EntityType::ROOM), _visited(false) {
}


Room::~Room() {
}

void Room::SetExit(Exit* exit) {
    for (int i = 0; i < _exits.size(); i++) {                  // Looks for exit duplication
        if (exit == _exits[i]) {
            return;
        }
    }
    _exits.push_back(exit);
}

Exit* Room::GetExit(const string direction) const {
    for (int i = 0; i < _exits.size(); i++) {
        if (_exits[i]->GetDirection() == direction) {

            return _exits[i];
        }
    }
    return nullptr;
}

void Room::Look(bool full_description) {
    cout <<GetName() << std::endl << std::endl;
    if (full_description) {
        std::cout << GetDescription() << std::endl;
        return;
    } else if (long_descriptions == 2) {
        std::cout << GetDescription() << std::endl;
        return;
    } else if (long_descriptions == 0 && _visited == false) {
        _visited = true;
        std::cout << GetDescription()<<std::endl;
        return;
    }
}