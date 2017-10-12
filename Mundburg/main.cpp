#include <iostream>
#include <conio.h>
#include <string>
#include <vector>

#include "GlobalFunctions.h"
#include "World.h"
#include "Entity.h"

using namespace std;

void Lol(string hola) {
    cout << hola;
}

int main() {

    Entity* a = new Entity("Padre", "Es el padre");
    Entity* b = new Entity();
    Entity* c = new Entity();
    

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


    std::cout << "\n\n";
    std::cout << "........................................................................" << std::endl;
    std::cout << ".......................,.;.,....-*****--....,.;.,......................." << std::endl;
    std::cout << ".......................\\\\|/...'          '...|//........................" << std::endl;
    std::cout << "........................\\-;-/   ()   ()   \\-;-/........................." << std::endl;
    std::cout << "........................// ;               ; \\\\........................." << std::endl;
    std::cout << ".......................//__; :.         .; ;__\\\\........................" << std::endl;
    std::cout << "......................`-----\\'.'-.....-'.'/-----'......................." << std::endl;
    std::cout << ".............................'.'.-.-,_.'.'.............................." << std::endl;
    std::cout << "...............................'(  (..-'................................" << std::endl;
    std::cout << ".................................'-'...................................." << std::endl;
    std::cout << "........................................................................" << std::endl;
    std::cout << "------------------------------------------------------------------------" << std::endl;
    std::cout << "--------------------------THANKS FOR PLAYING----------------------------" << std::endl;
    std::cout << "------------------------------------------------------------------------" << std::endl;
    std::cout << "\n(Press any key to exit)\n";
    _getch();
    return 0;
}