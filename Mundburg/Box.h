#ifndef __BOX__
#define __BOX__

#include "Item.h"

//class Entity;

class Box : public Item {
public:
    Box(const char* name, const char* description, const char* long_description, Entity* parent);
    ~Box();

    void Open();
    void Close();

private:
    bool _open;

};

#endif // __BOX__
