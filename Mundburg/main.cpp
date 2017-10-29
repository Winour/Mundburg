#include <iostream>
#include <conio.h>
#include <string>
#include <vector>

#include "GlobalFunctions.h"
#include "World.h"
#include "Entity.h"

using namespace std;



int main() {                           

	char key;
    bool game_over = false;
	string player_input;
	vector<string> instructions;

	instructions.reserve(10);

    World world;

	while (!game_over) {

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
                std::cout << std::endl <<std::endl;
            }
		}
        switch (world.Update(instructions)) {
            case Game_States::EXIT:
                game_over = true;
                break;
            case Game_States::DEAD:
                std::cout << "You are dead\n";
                game_over = true;
                break;
            case Game_States::REPEAT_INSTRUCTION:
                std::cout << "I did not understand you \n";
                break;
            case Game_States::WIN:
                std::cout << "YOU WIN!!!!!\n";
                game_over = true;
                break;
            default:
                break;
        }
        //if (instructions.size() > 0 && Compare(instructions[0], "quit")) {
        //    break;
        //}

        //if (world.Tick(instructions) == false) {
        //    std::cout << "I did not understand you \n";
        //}

        if (instructions.size() > 0) {
            instructions.clear();
            player_input = "";
            std::cout << "\n";
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