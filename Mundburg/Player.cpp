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
        GetRoom()->Look(long_descriptions);
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
        case 2: {
            std::vector<Entity*> temp = GetRoom()->GetChilds();
            for (size_t i = 0; i < temp.size(); i++) {
                if (Compare((instructions[1]), temp[i]->GetName())) {
                    GetRoom()->exits[i]->Open();            // HERE OPEN BOX
                    return true;
                }
            }
        }
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
    std::cout << "Sorry but you can't open that.\n";
	return false;

}

void Player::Look() const {
    GetRoom()->Look();
}

void Player::Examine(vector<string>& instructions) const {
    switch (instructions.size()) {
        case 1:
            std::cout << GetName() << " Level " << GetLevel()<< ": " << GetDescription() << "." << std::endl << std::endl;
            std::cout << "Stats:" << std::endl;

            std::cout << "   Health -> " << GetMaxHp() << "/" << hp << std::endl;
            std::cout << "   Mana -> " << GetMaxMana() << "/" << hp << std::endl;
            if (GetWeapon() == nullptr) {
                std::cout << "   Attack -> " << attack << " (+0)" << endl;
            } else {
                std::cout << "   Attack -> " << attack + GetWeapon()->GetValue() << " (+" << GetWeapon()->GetValue() << ")" << endl;
            }
            if (GetArmor() == nullptr) {
                std::cout << "   Defense -> " << defense << " (+0)" << endl;
            } else {
                std::cout << "   Defense -> " << defense + GetArmor()->GetValue() << " (+" << GetArmor()->GetValue() << ")" << endl;
            }

            break;
        case 2: {
            std::vector<Entity*> temp = GetRoom()->GetChilds();
            for (size_t i = 0; i < temp.size(); i++) {
                if (Compare(instructions[1], temp[i]->GetName())) {
                    std::cout << temp[i]->GetLongDescription() << std::endl;
                    return;
                }
            }
            temp = GetChilds();
            for (size_t i = 0; i < temp.size(); i++) {
                if (Compare(instructions[1], temp[i]->GetName())) {
                    std::cout << temp[i]->GetLongDescription() << std::endl;
                    return;
                }
            }
        }
            break;
        case 3: {
            std::vector<Entity*> temp = GetRoom()->GetChilds();
            for (size_t i = 0; i < temp.size(); i++) {
                if (Compare(instructions[1] + " " + instructions[2], temp[i]->GetName())) {
                    std::cout << temp[i]->GetLongDescription() << std::endl;
                    return;
                }
            }
            temp = GetChilds();
            for (size_t i = 0; i < temp.size(); i++) {
                if (Compare(instructions[1] + " " + instructions[2], temp[i]->GetName())) {
                    std::cout << temp[i]->GetLongDescription() << std::endl;
                    return;
                }
            }
        }

            break;
        default:
            break;
    }
}

void Player::Inventory() const {
    vector<Entity*> inv;
    FindAll(EntityType::ITEM, inv);

    for (size_t i = 0; i < inv.size(); i++) {

        if (((Item*)inv[i])->item_type == ItemType::STANDARD) {
            std::cout << "-" << inv[i]->GetName() << " " << ((Item*)inv[i])->GetWeight() << "Kg\n";
        } else if (((Item*)inv[i])->item_type == ItemType::WEAPON) {
            std::cout << "-" << inv[i]->GetName() << " (" << ((Item*)inv[i])->GetValue() << " attack) " << ((Item*)inv[i])->GetWeight() << "Kg\n";
        } else if (((Item*)inv[i])->item_type == ItemType::KEY) {
            std::cout << "-" << inv[i]->GetName() << std::endl;
        } else if (((Item*)inv[i])->item_type == ItemType::ARMOR) {
            std::cout << "-" << inv[i]->GetName() << " (" << ((Item*)inv[i])->GetValue() << " defense) " << ((Item*)inv[i])->GetWeight() << "Kg\n";
        } else if (((Item*)inv[i])->item_type == ItemType::POTION) {
            std::cout << "-" << inv[i]->GetName() << " (" << ((Item*)inv[i])->GetValue() << " Heal) " << ((Item*)inv[i])->GetWeight() << "Kg\n";
        } else if (((Item*)inv[i])->item_type == ItemType::CONTAINER) {
            if(inv[i]->GetChilds().size() == 0){
                std::cout << "-" << inv[i]->GetName() << " (Empty) " << ((Item*)inv[i])->GetWeight() << "Kg\n";
            } else {
                std::cout << "-" << inv[i]->GetName() << " (" << inv[i]->GetChilds()[0]->GetName() << ") " << ((Item*)inv[i])->GetWeight() << "Kg\n";
            }
        }
    }
}

void Player::Equip(vector<string>& instructions) {
    vector<Entity*> inv;
    FindAll(EntityType::ITEM, inv);

    switch (instructions.size()) {
        case 2:
            for (size_t i = 0; i < inv.size(); i++) {
                if (Compare(instructions[1],inv[i]->GetName())) {
                    if (((Item*)inv[i])->item_type == ItemType::ARMOR) {
                        if (inv[i] == GetArmor()) {
                            std::cout << "You already have it equipped.\n";
                        } else {
                            SetArmor((Item*)inv[i]);
                            std::cout << inv[i]->GetName() << " equiped.\n";
                        }
                        return;                  
                    } else if (((Item*)inv[i])->item_type == ItemType::WEAPON) {
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

                }
            }
            std::cout << "You don't have that item.\n";
            break;
        case 3:
            break;
        default:
            break;
    }
}

void Player::Unequip(vector<string>& instructions) {
    if (GetArmor() != nullptr && (Compare(instructions[1], "armor") || Compare(instructions[1], GetArmor()->GetName()))) {
        std::cout << GetArmor()->GetName() << " unequiped.\n";
        SetArmor(nullptr);
        return;
    } else if (GetWeapon() != nullptr && (Compare(instructions[1], "weapon") || Compare(instructions[1], GetWeapon()->GetName()))) {
        std::cout << GetWeapon()->GetName() << " unequiped.\n";
        SetWeapon(nullptr);
        return;
    } else {
        std::cout << "You don't have this item equiped.\n";
        return;
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

void Player::Take(vector<string>& instructions, bool offset) {
    vector<Entity*> items;
    GetRoom()->FindAll(EntityType::ITEM, items);
    GetRoom()->FindAll(EntityType::CREATURE, items);
    GetRoom()->FindAll(EntityType::EXIT, items);

    if (offset) {
        instructions.erase(instructions.begin() + 1);
    }

    switch (instructions.size()) {
    case 2:
        for (size_t i = 0; i < items.size(); i++) {
            if (Compare(instructions[1], items[i]->GetName())) {
                if (EntityType::CREATURE == items[i]->GetType()) {
                    std::cout << "Why would you pick a " << items[i]->GetName() << "???\n";
                    return;
                } else if (EntityType::EXIT == items[i]->GetType()) {
                    std::cout << "You can't take a door...\n";
                    return;
                } else if (ItemType::NOT_PICKABLE == ((Item*)items[i])->item_type) {
                    std::cout << "You can't take that.\n";
                    return;
                } else if(ItemType::FLUID == ((Item*)items[i])->item_type){
                    std::cout << "You need a container to take that.\n";
                    return;
                } else {
                    items[i]->ChangeParent(this);
                    std::cout << "You took " << items[i]->GetName() << std::endl;
                    return;
                }
            }
        }
        std::cout << "You can't see that.\n";
        break;
    case 3:
        for (size_t i = 0; i < items.size(); i++) {
            if (Compare(instructions[1] + " " + instructions[2], items[i]->GetName())) {
                if (EntityType::CREATURE == items[i]->GetType()) {
                    std::cout << "Why would you pick a " << items[i]->GetName() << "???\n";
                    return;
                } else if (EntityType::EXIT == items[i]->GetType()) {
                    std::cout << "You can't take a door...\n";
                    return;
                } else if (ItemType::NOT_PICKABLE == ((Item*)items[i])->item_type) {
                    std::cout << "You can't take that.\n";
                    return;
                } else if (ItemType::FLUID == ((Item*)items[i])->item_type) {
                    std::cout << "You need a container to take that.\n";
                    return;
                } else {
                    items[i]->ChangeParent(this);
                    std::cout << "You took " << items[i]->GetName() << std::endl;
                    return;
                }
            }
        }
        std::cout << "You can't see that.\n";
        break;
    default:
        break;
    }
}

void Player::Unlock(vector<string>& instructions) {
    switch (instructions.size()) {
    case 3:
        std::cout << "With what?\n";
        break;
    case 5:
        for (size_t i = 0; i < GetRoom()->exits.size(); i++) {
            if (Compare((instructions[1] + " " + instructions[2]), GetRoom()->exits[i]->GetName())) {
                if (!Compare(instructions[3], "with")) {
                    std::cout << "I think you wanted to say unlock with, if you didn't, remember to write: UNLOCK + DOOR TO UNLOCK + WITH + KEY.\n";
                }
                if (GetRoom()->exits[i]->Unlock(Find(instructions[4], EntityType::ITEM))) {
                    std::cout << "You unlocked the " << GetRoom()->exits[i]->GetName() << std::endl;
                }
                return;
            }
        }
        break;
    case 6:
        for (size_t i = 0; i < GetRoom()->exits.size(); i++) {
            if (Compare((instructions[1] + " " + instructions[2]), GetRoom()->exits[i]->GetName())) {
                if (!Compare(instructions[3], "with")) {
                    std::cout << "I think you wanted to say unlock with, if you didn't, remember to write: UNLOCK + DOOR TO UNLOCK + WITH + KEY.\n";
                }
                if (GetRoom()->exits[i]->Unlock(Find(instructions[4] + " " + instructions[5], EntityType::ITEM))) {
                    std::cout << "You unlocked the " << GetRoom()->exits[i]->GetName() << std::endl;
                }
                return;
            }
        }
        
        break;
    default:
        break;
    }

}

void Player::Lock(vector<string>& instructions) {

    switch (instructions.size()) {
    case 3:
        std::cout << "With what?\n";
        break;
    case 5:
        for (size_t i = 0; i < GetRoom()->exits.size(); i++) {
            if (Compare((instructions[1] + " " + instructions[2]), GetRoom()->exits[i]->GetName())) {
                if (!Compare(instructions[3], "with")) {
                    std::cout << "I think you wanted to say lock with, if you didn't, remember to write: LOCK + DOOR TO LOCK + WITH + KEY.\n";
                }
                if (GetRoom()->exits[i]->Lock(Find(instructions[4], EntityType::ITEM))) {
                    std::cout << "You locked the " << GetRoom()->exits[i]->GetName() << std::endl;
                }
                return;
            }
        }
        break;
    case 6:
        for (size_t i = 0; i < GetRoom()->exits.size(); i++) {
            if (Compare((instructions[1] + " " + instructions[2]), GetRoom()->exits[i]->GetName())) {
                if (!Compare(instructions[3], "with")) {
                    std::cout << "I think you wanted to say lock with, if you didn't, remember to write: LOCK + DOOR TO LOCK + WITH + KEY.\n";
                }
                if (GetRoom()->exits[i]->Lock(Find(instructions[4] + " " + instructions[5], EntityType::ITEM))) {
                    std::cout << "You locked the " << GetRoom()->exits[i]->GetName() << std::endl;
                }
                return;
            }
        }

        break;
    default:
        break;
    }

}