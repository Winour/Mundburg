#ifndef __Exit__
#define __Exit__

#include <string>
#include <vector>

#include "Entity.h"

#include <iostream>
using namespace std;

class Room;

class Exit : public Entity{
public:
    Exit(const char* name, const char* description, const char* long_description, Room* room, Room* destination, std::string direction, Entity* key, bool closed, bool locked);
    ~Exit();

    //Getters
    std::string GetDirection() const;
    Room* GetDestination() const;
    bool IsClosed() const;
    bool IsLocked() const;

    //Setters
    void Open();
    void Close();
    void Lock(Entity* key);
    void Unlock(Entity* key);

private:
    
    bool _closed;
    bool _locked;
    std::string _direction;
    Room* _destination;
    Entity* _key;

};

#endif // __Exit__
