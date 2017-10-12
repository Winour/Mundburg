#include <iostream>
#include <conio.h>
#include <string>
#include <vector>

#include "GlobalFunctions.h"

using namespace std;


int main() {

	char key;
	string player_input;
	vector<string> instructions;
	instructions.reserve(10);


	while (true) {

		if (_kbhit() != 0) {	

			key = _getch();

			if (key == '\b') {			                                        // Backspace		

				if (player_input.length() > 0) {
					player_input.pop_back();
					cout << '\b';
					cout << " ";
					cout << '\b';
				}

			} else if (key != '\r'){	                                        // Type
				player_input += key;
				cout << key;
            } else {                                                            // Enter
                EnterInstructions(instructions, player_input);
            }
		}

        if (instructions.size() > 0 && Compare(instructions[0], "quit")) {
            break;
        }

        // TODO : Process the input

        if (instructions.size() > 0) {
            instructions.clear();
            player_input = "";
            std::cout << "\n\n";
        }

	}
}