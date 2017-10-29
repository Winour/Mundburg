#ifndef __Room__
#define __Room__

#include <string>
#include <vector>
#include <iostream>
#include "Entity.h"


class Exit;

class Room : public Entity {
public:

    Room(const char* name, const char* description, const char* long_description);
    ~Room();

    void SetExit(Exit* exit);
    Exit* GetExit(const string& direction) const;
    void PrintExits() const;

    void Look(int long_descriptions = 0, bool full_description = false);
    vector<Exit*> exits;


private:
    bool _visited;



};

#endif //__Room__