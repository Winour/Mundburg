#include "Creature.h"
#include "Room.h"
#include "Exit.h"


Creature::Creature(const char* name, const char* description, Room* room, EntityType type):
Entity(name, description, room, type)
{
}


Creature::~Creature() {
}

void Creature::Poison() {
    

}

void Creature::Look() const {
    cout << GetParent()->GetName() << endl << endl;
    GetRoom()->Look();
}


Room* Creature::GetRoom() const {
    return (Room*)GetParent();
}