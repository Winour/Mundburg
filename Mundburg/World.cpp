#include "World.h"
#include "Entity.h"
#include "Room.h"
#include "Exit.h"
#include "Creature.h"
#include "Player.h"
#include "GlobalFunctions.h"



World::World() {
    Room* hall = new Room("Hall", "There is not too much to see.\n3 doors, a huge pile of rocks blocks the 4th one behind you.");
    Room* stairs = new Room("Stairs", "A spiral staircase communicates the first floor\nwith the upper room of the castle.");
    Room* dungeon = new Room("Dungeon", "A dark dungeon, it seems that someone lives in here.");
    Room* library = new Room("Library", "The room is full of books, however,\nthere's one that draws your attention.\nThe door is to the east.");
    Room* warehouse = new Room("Warehouse", "There are some shelves, they could contain something interesting.\nYou notice something on the south wall.");
    Room* secret_room = new Room("Secret Room", "Why are the walls shining?");
    entities.push_back(hall);
    entities.push_back(stairs);
    entities.push_back(dungeon);
    entities.push_back(library);
    entities.push_back(warehouse);
    entities.push_back(secret_room);

    Exit* e1 = new Exit("A", "B", hall, stairs, "north", nullptr, true, false);
    Exit* e2 = new Exit("Wooden door", "It looks like a normal wooden door.", hall, dungeon, "east", nullptr, true, false);
    Exit* e3 = new Exit("Wooden door", "It looks like a normal wooden door.", hall, warehouse, "west", nullptr, true, false);
    hall->SetExit(e1);
    hall->SetExit(e2);
    Exit* e4 = new Exit("Steel door", "It is made of steel, however, it is so light...", stairs, library, "up", nullptr, false, false);
    stairs->SetExit(e4);
    player = new Player("Lancelot", "Handsome heroe", hall);
    player->Look();

}


World::~World() {
}

bool World::Tick(vector<string>& instructions) {
    bool ret = true;

    if (instructions.size() > 0 && instructions[0].length() > 0) {
        ret = ParseInstructions(instructions);
    }

    GameLoop();
    return ret;    
}

bool World::ParseInstructions(vector<string>& instructions) {
    bool ret = true;

    switch (instructions.size()) {
        case 1:
            if (Compare(instructions[0], "look") || Compare(instructions[0], "l")) {

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

            } else if (Compare(instructions[0], "suicide")) {

                player->Look();         // TODO

            } else if (Compare(instructions[0], "examine")) {

                player->Look();         // TODO

            } else if (Compare(instructions[0], "inventory") || Compare(instructions[0], "i")) {

                player->Look();//TODO

            } else if (Compare(instructions[0], "heal")) {

                player->Look();//TODO

            } else if (Compare(instructions[0], "equipment")) {

                player->Look();//TODO

            } else if (Compare(instructions[0], "instructions") || Compare(instructions[0], "help")) {

                player->Look();//TODO

            } else {

                ret = false;

            }
            break;
        case 2:
            if (Compare(instructions[0], "go")) {

                player->Go(instructions);

            } else if (Compare(instructions[0], "take")) {

                player->Go(instructions);//TODO

            } else if (Compare(instructions[0], "examine")) {

                player->Go(instructions);//TODO

            } else if (Compare(instructions[0], "equip")) {

                player->Go(instructions);//TODO

            } else if (Compare(instructions[0], "unequip")) {

                player->Go(instructions);//TODO

            } else if (Compare(instructions[0], "throw") || Compare(instructions[0], "drop")) {

                player->Go(instructions);//TODO

            } else if (Compare(instructions[0], "attack")) {

                player->Go(instructions);//TODO

            } else if (Compare(instructions[0], "loot")) {

                player->Look();         // TODO

            } else if (Compare(instructions[0], "examine")) {

                player->Look();         // TODO

            } else if (Compare(instructions[0], "read")) {

                player->Look();//TODO

            } else if (Compare(instructions[0], "use")) {

                player->Look();//TODO

            } else if (Compare(instructions[0], "open")) {

                player->Look();//TODO

            } else {

                ret = false;

            }
            break;
        case 3:
            if (Compare(instructions[0], "talk") && (Compare(instructions[1], "to") || Compare(instructions[1], "with"))) {

                player->Look();//TODO

            } else if (Compare(instructions[0], "pick") && Compare(instructions[1], "up")) {

                player->Go(instructions); //TODO

            //} else if (Compare(instructions[0], "east")) {

            //    instructions.push_back("east");
            //    player->Go(instructions);

            //} else if (Compare(instructions[0], "west")) {

            //    instructions.push_back("west");
            //    player->Go(instructions);

            } else {

                ret = false;

            }
            break;
        case 4:
            if (Compare(instructions[0], "lock")) {

                player->Look();//TODO

            } else if (Compare(instructions[0], "unlock")) {

                player->Go(instructions);//TODO

            } else if (Compare(instructions[0], "throw")) {

                instructions.push_back("east");
                player->Go(instructions);

            } else {

                ret = false;

            }
            break;
        default:
            ret = false;
    }
    return ret;
}

void World::GameLoop() {

}