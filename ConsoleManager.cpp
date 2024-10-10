#include "ConsoleManager.h"
#include "Console.h"
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

ConsoleManager::ConsoleManager() : currentConsole(nullptr), previousConsole(nullptr) {

    // Create a Console object for the main menu
    std::shared_ptr<Console> mainConsole(new Console("MAIN_MENU", 1, 1, 0));
    consoles.push_back(mainConsole);
    currentConsole = mainConsole;
  
}

void ConsoleManager::addConsole(const std::shared_ptr<Console>& console) {

    consoles.push_back(console);
}

ConsoleManager::~ConsoleManager() {}

void ConsoleManager::drawMainMenu() {

    currentConsole->drawMain(); // Draw the main menu

}

std::string ConsoleManager::getCurrentConsoleName() const {

    if (currentConsole) {
        return currentConsole->getName();
    }
    else {
        return "MAIN_MENU";
    }

}

void ConsoleManager::handleInput(const std::string& input) {

    // Handle user input

    // tokenize user input
    std::stringstream ss(input);
    std::vector<std::string> tokens;
    std::string token;

    while (ss >> token) {

        tokens.push_back(token);

    }

    if (input == "exit" && (currentConsole->getName() != "MAIN_MENU")) {

        system("cls");
        // Find the console with the name "MAIN_MENU"
        for (const auto& consolePtr : consoles) {

            if (consolePtr->getName() == "MAIN_MENU") {

                currentConsole = consolePtr;
                break;

            }
        }
        // If "MAIN_MENU" console is found, draw its main content
        if (currentConsole && currentConsole->getName() == "MAIN_MENU") {

            currentConsole->drawMain();

        }

    }
    else if (input == "exit" && (currentConsole->getName() == "MAIN_MENU")) {

        return;

    }
    else if (tokens.size() == 3 && tokens[0] == "screen" && tokens[1] == "-s" && tokens[2] != "" && currentConsole->getName() == "MAIN_MENU") {

        bool isExistingProcess = false;

        for (const auto& consolePtr : consoles) {

            if (consolePtr->getName() == tokens[2]) {

                std::cout << "Please choose another name.\n";
                isExistingProcess = true;
                break;

            }
        }
        if (!isExistingProcess) {

            std::shared_ptr<Console> newConsole(new Console(tokens[2], 0, 50, 1234));
            addConsole(newConsole);

            currentConsole = newConsole;
            currentConsole->drawProcess();

        }

    }

    else if (input == "show") {

        drawAllConsoles();

    }
    else if (tokens.size() == 3 && tokens[0] == "screen" && tokens[1] == "-r" && tokens[2] != "" && currentConsole->getName() == "MAIN_MENU") {
        
        for (const auto& consolePtr : consoles) {
           
            if (consolePtr->getName() == tokens[2]) {

                currentConsole = consolePtr;
                break;

            }
        }

        if (currentConsole && currentConsole->getName() == tokens[2]) {

            currentConsole->drawProcess();

        }
        else {

            std::cout << "Can't find screen\n" << std::endl;

        }

    }
    else if (tokens.size() == 3 && tokens[0] == "screen" && tokens[1] == "-s" && tokens[2] != "" && currentConsole->getName() != "MAIN_MENU") {
        
        std::cout << "Unkown Command\n" << std::endl;

    }

    else if (tokens.size() == 3 && tokens[0] == "screen" && tokens[1] == "-r" && tokens[2] != "" && currentConsole->getName() != "MAIN_MENU") {

        std::cout << "Unkown Command\n" << std::endl;

    }


 
}
void ConsoleManager::drawAllConsoles() {
   
    for (const auto& consolePtr : consoles) {

        Console& console = *consolePtr;

        // Now you can access properties of the console object
        std::cout << "Name: " << console.getName() << std::endl;
        
        //consolePtr->drawProcess();
    }

    std::cout << "Currently Selected Console: " << std::endl;
    std::cout << currentConsole->getName();
}