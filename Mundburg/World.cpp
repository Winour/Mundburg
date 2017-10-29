#include "World.h"
#include "Entity.h"
#include "Item.h"
#include "Box.h"
#include "Room.h"
#include "Exit.h"
#include "Creature.h"
#include "Player.h"
#include "NPC.h"
#include "GlobalFunctions.h"



World::World() {
    tick_timer = clock();

    Room* hall = new Room("Hall", "It's a large room, it has 3 doors but none similar to each other.", "");
    Room* stairs = new Room("Stairs", "A spiral staircase communicates the first floor\nwith the upper room of the castle.", "");
    Room* dungeon = new Room("Dungeon", "A dark dungeon, it seems that someone lives in here.", "");
    Room* library = new Room("Library", "The room is full of books, however,\nthere's one that draws your attention.\nThe door is to the east.", "");
    Room* warehouse = new Room("Warehouse", "There are some shelves, they could contain something interesting.\nYou notice something on the south wall.", "");
    Room* secret_room = new Room("Secret Room", "Why are the walls shining?", "");
    entities.push_back(hall);
    entities.push_back(stairs);
    entities.push_back(dungeon);
    entities.push_back(library);
    entities.push_back(warehouse);
    entities.push_back(secret_room);

    player = new Player("Lancelot", "Handsome heroe", "", hall);
    entities.push_back(player);

    Item* shirt = new Item("Shirt", "Old shirt", "", ItemType::ARMOR, player, 4, 1);
    Item* knife = new Item("Knife", "Rusty knife", "", ItemType::WEAPON, player, 10, 2);
    entities.push_back(shirt);
    entities.push_back(knife);

    NPC* enemyHall = new NPC("Orc", "A naked orc", "", hall, 2);
    entities.push_back(enemyHall);

    Item* potion6 = new Item("Potion", "Healing potion", "Potion", ItemType::POTION, hall, 1, 1);
    entities.push_back(potion6);

    Item* potion1 = new Item("Potion", "Healing potion", "Potion", ItemType::POTION, enemyHall, 1, 1);
    Item* ironKey = new Item("Iron Key", "A shiny iron key.", "", ItemType::KEY, enemyHall, 1, 1);
    entities.push_back(potion1);
    entities.push_back(ironKey);

    NPC* enemyWarehhouse = new NPC("Dog", "That dog has the rabies.", "", warehouse, 4);
    entities.push_back(enemyWarehhouse);

    Item* potion2 = new Item("Potion", "Healing potion.", "", ItemType::POTION, enemyWarehhouse, 1, 1);
    Item* tusk = new Item("Tusk", "The tusk of a huge animal.", "", ItemType::STANDARD, enemyWarehhouse, 1, 1);
    entities.push_back(potion2);
    entities.push_back(tusk);

    NPC* enemyLibrary = new NPC("Zombie", "A live zombie!!!.", "", library, 9);
    entities.push_back(enemyLibrary);

    Item* awesomeSword = new Item("Timais", "An awesome sword, looks powerful...", "", ItemType::WEAPON, enemyLibrary, 60, 5);
    entities.push_back(awesomeSword);

    NPC* enemyDungeon = new NPC("Vampire", "Now a vampire...what's wrong with this castle?", "", dungeon, 9);
    entities.push_back(enemyDungeon);

    Item* awesomeArmor = new Item("Demoleon", "The definitive armor.", "", ItemType::ARMOR, enemyDungeon, 90, 5);
    entities.push_back(awesomeArmor);

    finalBoss = new NPC("Demon", "The last stage of this infernal castle...", "", secret_room, 30);
    entities.push_back(finalBoss);

    Item* water = new Item("Water", "A water leak breaks the silence of the room.", "Water drops fall from a leak on the ceiling of the room and creates a puddle on the floor.", ItemType::NOT_PICKABLE, hall, 1, 1);
    Item* rocks = new Item("Rocks", "A huge pile of rocks blocks the 4th door behind you.", "", ItemType::NOT_PICKABLE, hall, 1, 1);
    entities.push_back(water);
    entities.push_back(rocks);

    Box* box = new Box("Chest", "Small chest.", "A small chest, looks like a pirate one.", warehouse);
    Item* greyKey = new Item("Grey Key", "An old grey key.", "An old grey key.", ItemType::KEY, box, 1, 1);
    entities.push_back(box);
    entities.push_back(greyKey);

    Exit* e1 = new Exit("Iron door", "It has nothing special", "", hall, stairs, "north", ironKey, true, true);
    Exit* e2 = new Exit("Grey door", "It looks like a normal door.", "", hall, dungeon, "east", greyKey, true, true);
    Exit* e3 = new Exit("Wooden door", "It looks like a normal wooden door.", "", hall, warehouse, "west", nullptr, true, false);
    hall->SetExit(e1);
    hall->SetExit(e2);
    hall->SetExit(e3);
    entities.push_back(e1);
    entities.push_back(e2);
    entities.push_back(e3);

    Exit* e4 = new Exit("Steel door", "It is made of steel, however, it is so light...", "", stairs, library, "up", nullptr, false, false);
    Exit* e5 = new Exit("Iron door", "It has nothing special", "", stairs, hall, "down", nullptr, false, false);
    stairs->SetExit(e4);
    stairs->SetExit(e5);
    entities.push_back(e4);
    entities.push_back(e5);

    Exit* e6 = new Exit("Steel door", "It is made of steel, however, it is so light...", "", library, stairs, "east", nullptr, false, false);
    library->SetExit(e6);
    entities.push_back(e6);

    Exit* e7 = new Exit("Grey door", "It looks like a normal door.", "", dungeon, hall, "west", nullptr, false, false);
    dungeon->SetExit(e7);
    entities.push_back(e7);

    Exit* e8 = new Exit("Wooden door", "It looks like a normal wooden door.", "", warehouse, hall, "east", nullptr, false, false);
    Exit* e9 = new Exit("Secret door", "It looks like the door doesn't want to be opened...", "", warehouse, secret_room, "south", nullptr, false, false);
    warehouse->SetExit(e8);
    warehouse->SetExit(e9);
    entities.push_back(e8);
    entities.push_back(e9);

    player->Look();
    std::cout << "\n";

}


World::~World() {
    for (size_t i = 0; i < entities.size(); i++) {
        delete entities[i];
    }
    entities.clear();
}

Game_States World::Update(vector<string>& instructions) {
    Game_States ret = Game_States::CONTINUE;

    if (instructions.size() > 0 && instructions[0].length() > 0) {
        ret = ParseInstructions(instructions);
    }

    GameLoop();

    if (player->IsAlive() == false) {
        ret = Game_States::DEAD;
    }
    return ret;
}


void World::GameLoop() {
    clock_t now = clock();
    if ((now - tick_timer) > 2500.0f) {
        for (size_t i = 0; i < entities.size(); i++) {
            entities[i]->Update();
        }
        for (size_t i = 0; i < entities.size();) {
            if (entities[i]->to_destroy) {
                entities[i]->DropItems();
                delete entities[i];
                entities.erase(entities.begin() + i);
            } else {
                ++i;
            }
        }
        tick_timer = now;
    }
}

Game_States World::ParseInstructions(vector<string>& instructions) {
    Game_States ret = Game_States::CONTINUE;

    switch (instructions.size()) {
    case 1:
        if (Compare(instructions[0], "quit")) {
            ret = Game_States::EXIT;
        } else if (Compare(instructions[0], "look") || Compare(instructions[0], "l")) {

            player->Look();

        } else if (Compare(instructions[0], "north")) {

            instructions.push_back("north");
            player->Go(instructions);

        } else if (Compare(instructions[0], "east")) {

            instructions.push_back("east");
            player->Go(instructions);

        } else if (Compare(instructions[0], "west")) {

            instructions.push_back("west");
            player->Go(instructions);

        } else if (Compare(instructions[0], "south")) {

            instructions.push_back("south");
            player->Go(instructions);

        } else if (Compare(instructions[0], "up")) {

            instructions.push_back("up");
            player->Go(instructions);

        } else if (Compare(instructions[0], "down")) {

            instructions.push_back("down");
            player->Go(instructions);

        } else if (Compare(instructions[0], "superbrief")) {

            std::cout << "Superbrief mode: now you won't get rooms description,\neven if you haven't been there before.\nUnless you use 'Look'.\n";
            player->long_descriptions = 1;

        } else if (Compare(instructions[0], "brief")) {

            std::cout << "Brief mode: now you will only get rooms description\nif you haven't been there before or you use 'Look'.\n";
            player->long_descriptions = 0;

        } else if (Compare(instructions[0], "long")) {

            std::cout << "Long mode: now you will always get rooms description.\n";
            player->long_descriptions = 2;

        } else if (Compare(instructions[0], "suicide")) {
            std::cout << "You realise that this is the end and there's nothing you can do...\n";
            std::cout << "You slowly take a pill from your pocket...Cyanide...\n";
            std::cout << "While the pill enters on your mouth,\nall you can think is if you are going to get a good grade on programming.\n";
            player->hp = 0;
            ret = Game_States::DEAD;

        } else if (Compare(instructions[0], "examine") || Compare(instructions[0], "stats")) {

            player->Examine(instructions);

        } else if (Compare(instructions[0], "inventory") || Compare(instructions[0], "i")) {

            player->Inventory();

        } else if (Compare(instructions[0], "equipment")) {

            player->Equipment();

        } else if (Compare(instructions[0], "exits")) {

            player->GetRoom()->PrintExits();

        } else if (Compare(instructions[0], "instructions") || Compare(instructions[0], "help")) {

            std::cout << "Welcome to Mundburg:\n" << std::endl;
            std::cout << "In this game, you have to explore the castle and find items, equipment and learn spells" << std::endl;
            std::cout << "in order to defeat a final boss." << std::endl;
            std::cout << "You can use some of the following commands:" << std::endl;
            std::cout << "  -GO + DIRECTION: if you dont know which directions you can go, type the comand 'exits'\nto get all possible directions. You can also omit 'GO'." << std::endl;
            std::cout << "  -SUPERBRIEF: you won't get rooms description, even if you haven't been there before.\nUnless you use 'Look'." << std::endl;
            std::cout << "  -BRIEF: you will only get rooms description if you haven't been there before or use 'Look'." << std::endl;
            std::cout << "  -LONG: you will always get rooms description." << std::endl;
            std::cout << "  -SUICIDE: if you give up..." << std::endl;
            std::cout << "  -EXAMINE + WHAT TO EXAMINE: if you don't specify what to examine, you will examine yourself." << std::endl;
            std::cout << "  -INVENTORY: a list of all your items." << std::endl;
            std::cout << "  -EQUIPMENT: your armor and your weapon." << std::endl;
            std::cout << "  -EQUIP + WHAT TO EQUIP: equip a weapon or an armor." << std::endl;
            std::cout << "  -TAKE + WHAT TO TAKE: take something from the room." << std::endl;
            std::cout << "  -DROP + WHAT TO DROP: drop something." << std::endl;
            std::cout << "  -THROW + WHAT TO THROW + TO + OBJECTIVE: throw a item of your inventory to something." << std::endl;
            std::cout << "  -LOOT + DEAD BODY TO LOOT: take all useful items from a dead body." << std::endl;
            std::cout << "These are some useful commands, there might be some more, for example: UNEQUIP, OPEN, CLOSE, UNLOCK..." << std::endl;

        } else if (Compare(instructions[0], "commands")) {

            std::cout << "You can use some of the following commands:" << std::endl;
            std::cout << "  -GO + DIRECTION: if you dont know which directions you can go, type the comand 'exits'\nto get all possible directions. You can also omit 'GO'." << std::endl;
            std::cout << "  -SUPERBRIEF: you won't get rooms description, even if you haven't been there before.\nUnless you use 'Look'." << std::endl;
            std::cout << "  -BRIEF: you will only get rooms description if you haven't been there before or use 'Look'." << std::endl;
            std::cout << "  -LONG: you will always get rooms description." << std::endl;
            std::cout << "  -SUICIDE: if you give up..." << std::endl;
            std::cout << "  -EXAMINE + WHAT TO EXAMINE: if you don't specify what to examine, you will examine yourself." << std::endl;
            std::cout << "  -INVENTORY: a list of all your items." << std::endl;
            std::cout << "  -EQUIPMENT: your armor and your weapon." << std::endl;
            std::cout << "  -EQUIP + WHAT TO EQUIP: equip a weapon or an armor." << std::endl;
            std::cout << "  -TAKE + WHAT TO TAKE: take something from the room." << std::endl;
            std::cout << "  -DROP + WHAT TO DROP: drop something." << std::endl;
            std::cout << "  -THROW + WHAT TO THROW + TO + OBJECTIVE: throw a item of your inventory to something." << std::endl;
            std::cout << "  -LOOT + DEAD BODY TO LOOT: take all useful items from a dead body." << std::endl;
            std::cout << "These are some useful commands, there might be some more, for example: UNEQUIP, OPEN, CLOSE, UNLOCK..." << std::endl;

        } else {

            ret = Game_States::REPEAT_INSTRUCTION;

        }
        break;
    case 2:
        if (Compare(instructions[0], "go")) {

            player->Go(instructions);

        } else if (Compare(instructions[0], "take")) {

            player->Take(instructions);

        } else if (Compare(instructions[0], "examine")) {

            player->Examine(instructions);

        } else if (Compare(instructions[0], "equip")) {

            player->Equip(instructions);

        } else if (Compare(instructions[0], "unequip")) {

            player->Unequip(instructions);

        } else if (Compare(instructions[0], "throw") || Compare(instructions[0], "drop")) {

            player->Throw(instructions);

        } else if (Compare(instructions[0], "attack")) {

            player->Attack(instructions);

        } else if (Compare(instructions[0], "use") || Compare(instructions[0], "drink")) {

            player->DrinkPotion(instructions);

        } else if (Compare(instructions[0], "open")) {

            player->Open(instructions);

        } else if (Compare(instructions[0], "close")) {

            player->Close(instructions);

        } else {

            ret = Game_States::REPEAT_INSTRUCTION;

        }
        break;
    case 3:
        if (Compare(instructions[0], "pick") && Compare(instructions[1], "up")) {

            player->Take(instructions, true);

        } else if (Compare(instructions[0], "open")) {

            player->Open(instructions);

        } else if (Compare(instructions[0], "close")) {

            player->Close(instructions);

        } else if (Compare(instructions[0], "take")) {

            player->Take(instructions);

        } else if (Compare(instructions[0], "unlock")) {

            player->Unlock(instructions);

        } else if (Compare(instructions[0], "lock")) {

            player->Unlock(instructions);

        } else if (Compare(instructions[0], "throw") || Compare(instructions[0], "drop")) {

            player->Throw(instructions);

        } else if (Compare(instructions[0], "examine")) {

            player->Examine(instructions);

        } else if (Compare(instructions[0], "attack")) {

            player->Attack(instructions);

        } else {

            ret = Game_States::REPEAT_INSTRUCTION;

        }
        break;
    case 4:
        if (Compare(instructions[0], "take") && Compare(instructions[2], "from")) {

            player->Take(instructions);

        } else {

            ret = Game_States::REPEAT_INSTRUCTION;

        }
        break;
    case 5:
        if (Compare(instructions[0], "unlock")) {

            player->Unlock(instructions);

        } else if (Compare(instructions[0], "lock")) {

            player->Lock(instructions);

        } else {

            ret = Game_States::REPEAT_INSTRUCTION;

        }
        break;
    case 6:
        if (Compare(instructions[0], "unlock")) {

            player->Unlock(instructions);

        } else if (Compare(instructions[0], "lock")) {

            player->Lock(instructions);

        }
        break;
    default:
        ret = Game_States::REPEAT_INSTRUCTION;
        break;
    }
    return ret;
}
