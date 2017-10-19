#include "Exit.h"
#include "Room.h"

#include <iostream>

Exit::Exit(const char* name, const char* description, Room* room, Room* destination, std::string direction, Entity* key, bool closed, bool locked) :
Entity(name, description, room, EntityType::EXIT), _destination(destination), _direction(direction), _key(key), _closed(closed), _locked(locked)
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

void Exit::Open() {
    if (_locked) {
        std::cout << "\nThe " << GetName() << " is locked, you need a " << _key->GetName() << " in order to open it.\n";
    } else if (!_closed) {
        std::cout << "\nThe " << GetName() << " is already open.\n";
    } else {
        _closed = false;
    }
}

void Exit::Close() {
    if (_closed) {
        std::cout << "\nThe " << GetName() << " is already closed.\n";
    } else {
        _closed = true;
    }
}

void Exit::Lock(Entity* key) {
    if (_key == nullptr) {
        std::cout << "\nThere's no lock\n";  
    } else if (_key != key) {
        std::cout << "\nThe " << key->GetName() << " doesn't fit into the lock.\n";
    } else if (_locked) {
        std::cout << "\nThe " << GetName() << " it's already locked.\n";
    } else {
        _locked = true;
    }
}

void Exit::Unlock(Entity* key) {
    if (_key == nullptr) {
        std::cout << "\nThere's no lock\n";
    } else if (_key != key) {
        std::cout << "\nThe " << key->GetName() << " doesn't fit into the lock.\n";
    } else if (!_locked) {
        std::cout << "\nThe " << GetName() << " it's already unlocked.\n";
    } else {
        _locked = false;
    }
}


