#ifndef __Room__
#define __Room__

#include <string>
#include <vector>

#include "Entity.h"

#include <iostream>
using namespace std;

class Exit;

class Room : public Entity {
public:

    Room(const char* name = "NONAME", const char* description = "NODESCRIPTION");
    ~Room();

    void SetExit(Exit* exit);
    Exit* GetExit(const string direction) const;

    void Look(bool full_description = false);


private:

    vector<Exit*> _exits;
    bool _visited;



};

#endif //__Room__