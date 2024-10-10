#pragma once

#include "Console.h"
#include <string>
#include <vector>
#include <memory>

class ConsoleManager {
private:
    std::shared_ptr<Console>currentConsole;
    std::shared_ptr<Console>previousConsole;
    std::vector<std::shared_ptr<Console>> consoles;

public:
    ConsoleManager();

    ~ConsoleManager();

    void drawMainMenu();

    void addConsole(const std::shared_ptr<Console>& console);

    void drawAllConsoles();

    void handleInput(const std::string& input);

    std::string getCurrentConsoleName() const;
};

