#include "ConsoleManager.h"
#include "fcfs_scheduler.h"
#include <iostream>
#include <thread>
#include <chrono>
#include <string>
#include <random>
#include <sstream>

int main() {
    ConsoleManager manager;
    // Display the initial main menu
    manager.drawMainMenu();

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(1000, 2000);

    const int num_cores = 4;
    FCFS_Scheduler scheduler(num_cores);
    scheduler.start();

    std::thread scheduler_thread;
    int process_count = 0;
    bool scheduler_testing = false;

    std::string command;
    std::string screenName;
    bool isInAnotherScreen = false;

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
