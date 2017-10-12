#ifndef  __GlobalFunctions__
#define  __GlobalFunctions__

#include <string>
#include <vector>

void EnterInstructions(std::vector<std::string>& instructions, const std::string player_input);
bool Compare(const std::string a, const std::string b);
bool Compare(const char* a, const std::string b);
bool Compare(const std::string a, const char * b);
bool Compare(const char* a, const char* b);

#endif 

