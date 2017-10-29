#include "Exit.h"
#include "Room.h"
#include "Item.h"

#include <iostream>

using namespace std;

Exit::Exit(const char* name, const char* description, const char* long_description, Room* room, Room* destination, std::string direction, Item* key, bool closed, bool locked) :
Entity(name, description,long_description, room, EntityType::EXIT), _destination(destination), _direction(direction), _key(key), _closed(closed), _locked(locked)
{

}


Exit::~Exit() {
}

std::string Exit::GetDirection() const {

    return _direction;
}

Room* Exit::GetDestination() const {
    return _destination;
}

bool Exit::IsClosed() const {
    return _closed;
}

bool Exit::IsLocked() const {
    return _locked;
}

Item* Exit::GetKey() const {
    return _key;
}

void Exit::Open() {
    if (_locked) {
        std::cout << "The " << GetName() << " is locked, you need the " << _key->GetName() << " in order to open it.\n";
    } else if (!_closed) {
        std::cout << "The " << GetName() << " is already open.\n";
    } else {
        std::cout << "The " << GetName() << " has been opened.\n";
        _closed = false;
    }
}

void Exit::Close() {
    if (_closed) {
        std::cout << "The " << GetName() << " is already closed.\n";
    } else {
        _closed = true;
        std::cout << "The " << GetName() << " has been closed.\n";
    }
}

bool Exit::Lock(Entity* key) {
    if (_key == nullptr) {
        std::cout << "\nThere's no lock\n";
        return false;
    } else if (nullptr == key) {
        std::cout << "\nYou don't have that key.\n";
        return false;
    } else if (_key != key) {
        std::cout << "\nThe " << key->GetName() << " doesn't fit into the lock.\n";
        return false;
    } else if (_locked) {
        std::cout << "\nThe " << GetName() << " it's already locked.\n";
        return false;
    } else {
        _locked = true;
        return true;
    }
}

bool Exit::Unlock(Entity* key) {
    if (_key == nullptr) {
        std::cout << "\nThere's no lock\n";
        return false;
    } else if (nullptr == key) {
        std::cout << "\nYou don't have that key.\n";
        return false;
    } else if (_key != key) {
        std::cout << "\nThe " << key->GetName() << " doesn't fit into the lock.\n";
        return false;
    } else if (!_locked) {
        std::cout << "\nThe " << GetName() << " it's already unlocked.\n";
        return false;
    } else {
        _locked = false;
        return true;
    }
}


