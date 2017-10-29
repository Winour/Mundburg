#include "Box.h"



Box::Box(const char* name, const char* description, const char* long_description, Entity* parent):
Item(name, description, long_description, ItemType::BOX, parent, 0, 0), _open(false) {

}


Box::~Box() {
}

void Box::Open() {
    if (_open == false) {
        _open = true;
        std::cout << GetName() << " opened.\n";
    } else {
        std::cout << GetName() << " is already open.\n";
    }
}

void Box::Close() {
    if (_open == true) {
        _open = false;
        std::cout << GetName() << " closed.\n";
    } else {
        std::cout << GetName() << " is already closed.\n";
    }
}