#include "GlobalFunctions.h"
#include <iostream>

void EnterInstructions(std::vector<std::string>& instructions, const std::string player_input) {

    const char* ptr = player_input.c_str();

    do {

        const char* begin = ptr;

        while (*ptr != ' ' && *ptr != 0) {
            ptr++;
        }

        instructions.push_back(std::string(begin,ptr));

    } while (*ptr++ != 0);    
}

bool Compare(const std::string a, const std::string b) {

    return _stricmp(a.c_str(), b.c_str()) == 0;
}

bool Compare(const char* a, const std::string b) {

    return _stricmp(a, b.c_str()) == 0;
}

bool Compare(const std::string a, const char * b) {

    return _stricmp(a.c_str(), b) == 0;
}

bool Compare(const char* a, const char* b) {

    return _stricmp(a, b) == 0;
}