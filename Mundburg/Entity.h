#ifndef __Entity__
#define __Entity__

#include <string>
#include <vector>

#include <iostream>
using namespace std;

enum class EntityType {
    ENTITY,
    ROOM,
    EXIT,
    PLAYER,
    CREATURE,
    ITEM
};


class Entity {
public:

    Entity(const char* name = "NONAME", const char* description = "NODESCRIPTION", Entity* parent = nullptr);
    virtual ~Entity();

    void RemoveChild(Entity* child);

    // Getters
    std::string GetName() const;
    std::string GetDescription() const;
    Entity* GetParent() const;
    vector<Entity*> GetChilds() const;
    EntityType GetType() const;

    //Setters
    void SetName(std::string new_name);
    void SetDescription(std::string new_description);
    void SetParent(Entity* parent);
    void SetChild(Entity* child);

private:

    std::string _name;
    std::string _description;
    EntityType _type;
    Entity* _parent;
    vector<Entity*> _childs;

};

#endif