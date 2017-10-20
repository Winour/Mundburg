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

    Room(const char* name, const char* description, const char* long_description);
    ~Room();

    void SetExit(Exit* exit);
    Exit* GetExit(const string direction) const;
    void GetExits() const;

    void Look(bool full_description = false);
    vector<Exit*> exits;

private:
    bool _visited;



};

#endif //__Room__