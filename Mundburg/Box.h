#ifndef __BOX__
#define __BOX__

#include "Item.h"
//#include <string>

class Box : public Item {
public:
    Box(const char* name, const char* description, const char* long_description, Entity* parent);
    ~Box();

    bool IsOpen() const;
    void Open();
    void Close();
    bool TakeItem(const char* item, Entity* new_parent);

private:
    bool _open;

};

#endif // __BOX__
