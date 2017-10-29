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

class Room;

class Entity {
public:

    Entity(const char* name = "NONAME", const char* description = "NODESCRIPTION",const char* long_description = "NODESCRIPTION", Entity* parent = nullptr, EntityType type = EntityType::ENTITY);
    virtual ~Entity();

    void RemoveChild(Entity* child);
    void ChangeParent(Entity* new_parent);
    bool Find(Entity* entity) const;
    Entity* Find(string name, EntityType type) const;
    void FindAll(EntityType type, vector<Entity*>& container) const;

    // Getters
    std::string GetName() const;
    std::string GetDescription() const;
    Entity* GetParent() const;
    vector<Entity*> GetChilds() const;
    EntityType GetType() const;
    std::string GetLongDescription() const;

    //Setters
    void SetName(std::string& new_name);
    void SetDescription(std::string& new_description);
    void SetParent(Entity* parent);
    void SetChild(Entity* child);
    void SetLongDescription(std::string& new_long_description);

private:

    std::string _name;
    std::string _description;
    std::string _long_description;
    EntityType _type;
    Entity* _parent;
    vector<Entity*> _childs;

};

#endif