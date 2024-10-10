#include "ConsoleManager.h"
#include <iostream>

int main() {
    ConsoleManager manager;
    // Display the initial main menu
    manager.drawMainMenu();

    std::string input;

    while (true) {

        if (manager.getCurrentConsoleName() == "MAIN_MENU") {

            std::cout << "Enter a command: ";
            std::getline(std::cin, input);

        }
        else {

            std::cout << "root:\\>";
            std::getline(std::cin, input);

        }

        if (input == "exit" && manager.getCurrentConsoleName() == "MAIN_MENU") {

            break;
        }
        else if (input == "clear") {

            system("cls");

        }
        manager.handleInput(input);
        // Handle user input
    }
    return 0;
}
