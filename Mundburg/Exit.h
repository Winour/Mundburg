#ifndef __Exit__
#define __Exit__

#include <string>
#include <vector>

#include "Entity.h"

#include <iostream>
using namespace std;

class Exit : public Entity{
public:
    Exit();
    ~Exit();

    std::string GetDirection();

};

#endif // __Exit__
