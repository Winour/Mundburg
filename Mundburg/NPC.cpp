#include "NPC.h"



NPC::NPC(const char* name, const char* description, const char* long_description, Room* room, int lvl):
Creature(name, description, long_description, room, lvl, EntityType::NPC)
{
}


NPC::~NPC() {
}
