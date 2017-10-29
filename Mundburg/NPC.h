#ifndef __NPC__
#define __NPC__

#include "Creature.h"

class NPC : public Creature {
public:
    NPC(const char* name, const char* description, const char* long_description, Room* room, int lvl = 1);
    ~NPC();
};

#endif // __NPC__
