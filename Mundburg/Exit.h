#ifndef __Exit__
#define __Exit__

#include <string>
#include <vector>

#include "Entity.h"

#include <iostream>
using namespace std;

class Room;
class Item;

class Exit : public Entity{
public:
    Exit(const char* name, const char* description, const char* long_description, Room* room, Room* destination, std::string direction, Item* key, bool closed, bool locked);
    ~Exit();

    //Getters
    std::string GetDirection() const;
    Room* GetDestination() const;
    bool IsClosed() const;
    bool IsLocked() const;
    Item* GetKey() const;

    //Setters
    void Open();
    void Close();
    bool Lock(Entity* key);
    bool Unlock(Entity* key);

private:    //ALL OK
    
    bool _closed;
    bool _locked;
    std::string _direction;
    Room* _destination;
    Item* _key;

};

#endif // __Exit__
