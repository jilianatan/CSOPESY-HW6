#include "ConsoleManager.h"
#include "fcfs_scheduler.h"
#include "process.h"
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
            scheduler.stop();
            break;
        }
        else if (input == "clear") {
            system("cls");
        }
        else if (input == "scheduler-test") {
            if (!scheduler_testing) {
                std::cout << "Scheduler is running.\n";
                scheduler_testing = true;
                scheduler_thread = std::thread([&]() {
                    while (scheduler_testing) {
                        int commands_per_process = dist(gen);
                        scheduler.add_process(new Process("process" + std::to_string(++process_count), commands_per_process));
                        std::this_thread::sleep_for(std::chrono::milliseconds(500)); // Adjust based on your configuration
                    }
                    });
                scheduler_thread.detach(); // Detach to run independently
            }
            else {
                std::cout << "Scheduler test is already running.\n";
            }
        }
        else if (input == "scheduler-stop") {
            if (scheduler_testing) {
                scheduler_testing = false;
                if (scheduler_thread.joinable()) {
                    scheduler_thread.join();
                }
            }
            else {
                std::cout << "Scheduler test is not currently running.\n";
            }
        }
        else if (input == "screen-ls") {
            scheduler.screen_ls();
        }
        else if (input.find("screen -r") == 0) {
            std::stringstream ss(input);
            std::string temp, screenName;
            ss >> temp >> temp >> screenName;
            scheduler.print_process_details(screenName, 0);
            isInAnotherScreen = true;
        }
        else if (input == "process -smi") {
            if (isInAnotherScreen) {
                scheduler.print_process_details(screenName, 1);
            }
        }
        else if (input == "exit" && isInAnotherScreen) {
            isInAnotherScreen = false;
            system("cls"); // Clear screen on exit from another screen
        }
        else {
            manager.handleInput(input); // Delegate to ConsoleManager if not recognized here
        }
    }

    return 0;
}
