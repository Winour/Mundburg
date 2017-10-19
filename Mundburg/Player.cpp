#include "Player.h"
#include "Exit.h"
#include "Room.h"



Player::Player(const char* name, const char* description, Room* room, EntityType type):
    Creature(name, description, room, type)
{
}


Player::~Player() {
}

bool Player::Go(vector<string>& instructions) {
    Exit* exit = (GetRoom())->GetExit(instructions[1]);
    if (exit == nullptr) {
        cout << "There's no exit on this direction.\n";
        return false;
    } else if(exit->IsLocked()){
        cout << "The door is locked.\n";
        return false;
    } else if (exit->IsClosed()) {
        cout << "The door is closed.\n";
        return false;
    } else {
        ChangeParent(exit->GetDestination());
        GetRoom()->Look();
        return true;
    }
}

void Player::Look() const {
    GetRoom()->Look(true);
}