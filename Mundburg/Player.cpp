#include "Player.h"
#include "Exit.h"
#include "Room.h"
#include "Item.h"
#include "GlobalFunctions.h"



Player::Player(const char* name, const char* description, const char* long_description, Room* room, EntityType type):
    Creature(name, description, long_description, room, type)
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

bool Player::Close(vector<string>& instructions) {
    switch (instructions.size()) {
    case 1:
        break;
    case 2:
        break;
    case 3:
        for (size_t i = 0; i < GetRoom()->exits.size(); i++) {
            if (Compare((instructions[1] + " " + instructions[2]), GetRoom()->exits[i]->GetName())) {
                GetRoom()->exits[i]->Close();
            }
        }
        break;
    default:
        break;
    }
    return false;
}

bool Player::Open(vector<string>& instructions) {
	switch (instructions.size()) {
	    case 1:
		    break;
	    case 2:
		    break;
	    case 3:
            for (size_t i = 0; i < GetRoom()->exits.size(); i++) {
                if (Compare((instructions[1] + " " + instructions[2]), GetRoom()->exits[i]->GetName())) {
                    GetRoom()->exits[i]->Open();
                    return true;
                }
            }
		    break;
	    default:
		    break;
	}
	return false;
}

void Player::Look() const {
    GetRoom()->Look(true);
}

void Player::Inventory() const {
    vector<Entity*> inv;
    FindAll(EntityType::ITEM, inv);

    for (size_t i = 0; i < inv.size(); i++) {

        if (((Item*)inv[i])->GetItemType() == Item_type::STANDARD) {
            std::cout << "-" << inv[i]->GetName() << " " << ((Item*)inv[i])->GetWeight() << "Kg\n";
        } else if (((Item*)inv[i])->GetItemType() == Item_type::WEAPON) {
            std::cout << "-" << inv[i]->GetName() << " (" << ((Item*)inv[i])->GetValue() << " attack) " << ((Item*)inv[i])->GetWeight() << "Kg\n";
        } else if (((Item*)inv[i])->GetItemType() == Item_type::KEY) {
            std::cout << "-" << inv[i]->GetName() << std::endl;
        } else if (((Item*)inv[i])->GetItemType() == Item_type::ARMOR) {
            std::cout << "-" << inv[i]->GetName() << " (" << ((Item*)inv[i])->GetValue() << " defense) " << ((Item*)inv[i])->GetWeight() << "Kg\n";
        } else if (((Item*)inv[i])->GetItemType() == Item_type::POTION) {
            std::cout << "-" << inv[i]->GetName() << " (" << ((Item*)inv[i])->GetValue() << " Heal) " << ((Item*)inv[i])->GetWeight() << "Kg\n";
        } else if (((Item*)inv[i])->GetItemType() == Item_type::CONTAINER) {
            if(inv[i]->GetChilds().size() == 0){
                std::cout << "-" << inv[i]->GetName() << " (Empty) " << ((Item*)inv[i])->GetWeight() << "Kg\n";
            } else {
                std::cout << "-" << inv[i]->GetName() << " (" << inv[i]->GetChilds()[0]->GetName() << ") " << ((Item*)inv[i])->GetWeight() << "Kg\n";
            }
        }
    }
}

void Player::Equip(vector<string>& instructions) {      //DOING
    vector<Entity*> inv;
    FindAll(EntityType::ITEM, inv);
    switch (instructions.size()) {
        case 2:
            for (size_t i = 0; i < inv.size(); i++) {
                if (Compare(instructions[1],inv[i]->GetName())) {
                    if (((Item*)inv[i])->GetItemType() == Item_type::ARMOR) {
                        if (inv[i] == GetArmor()) {
                            std::cout << "You already have it equipped.\n";
                        } else {
                            SetArmor((Item*)inv[i]);
                            std::cout << inv[i]->GetName() << " equiped.\n";
                        }
                        return;                  
                    } else if (((Item*)inv[i])->GetItemType() == Item_type::WEAPON) {
                        if (inv[i] == GetWeapon()) {
                            std::cout << "You already have it equipped.\n";
                        } else {
                            SetWeapon((Item*)inv[i]);
                            std::cout << inv[i]->GetName() << " equiped.\n";
                        }
                        return;
                    } else {
                        std::cout << "You can't equip that.\n";
                        return;
                    }
                    std::cout << "You don't have that item.\n";
                }
            }
            break;
        case 3:
            for (size_t i = 0; i < GetRoom()->exits.size(); i++) {
                if (Compare((instructions[1] + " " + instructions[2]), GetRoom()->exits[i]->GetName())) {
                    GetRoom()->exits[i]->Open();
                }
            }
            break;
        default:
            break;
    }
}

void Player::Equipment() const {
    std::cout << "Weapon: ";
    if (GetWeapon() != nullptr) {
        std::cout << GetWeapon()->GetName() << " (" << GetWeapon()->GetValue() << " attack).\n";
    } else {
        std::cout << "None.\n";
    }
    std::cout << "Armor: ";
    if (GetArmor() != nullptr) {
        std::cout << GetArmor()->GetName() << " (" << GetArmor()->GetValue() << " defense).\n";
    } else {
        std::cout << "None.\n";
    }
}