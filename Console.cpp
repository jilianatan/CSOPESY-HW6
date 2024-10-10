#include "Console.h"
#include <iostream>
#include <ctime>
#include <string>

// constructor
Console::Console(std::string n, int cLine, int tLines, int id) : name(n), currentLine(cLine), totalLines(tLines), processId(id) {
	// Get current timestamp
	std::time_t now = std::time(nullptr);
	struct tm timeInfo;
	localtime_s(&timeInfo, &now);
	char timeStr[64];
	std::strftime(timeStr, sizeof(timeStr), "%m/%d/%Y, %I:%M:%S %p", &timeInfo);
	timestamp = timeStr;
}

std::string Console::getName() const {
	return name;
}
void Console::drawMain() {

	std::cout << " _______  _______  _______  _______  _______  _______  __   __  \n";
	std::cout << "|       ||       ||       ||       ||       ||       ||  | |  |\n";
	std::cout << "|       ||  _____||   _   ||    _  ||    ___||  _____||  |_|  | \n";
	std::cout << "|       || |_____ |  | |  ||   |_| ||   |___ | |_____ |       |\n";
	std::cout << "|      _||_____  ||  |_|  ||    ___||    ___||_____  ||_     _|\n";
	std::cout << "|     |_  _____| ||       ||   |    |   |___  _____| |  |   |   \n";
	std::cout << "|_______||_______||_______||___|    |_______||_______|  |___|  \n\n";

	std::cout << "\033[1;32m"; // 1;32m represents bold green text
	std::cout << "Hi, Welcome to the CSOPESY command line!" << std::endl;

	std::cout << "\033[1;33m"; // 1;33m represents bold yellow text
	std::cout << "Type 'exit' to quit, 'clear' to clear the screen" << std::endl;
	std::cout << "\033[0m"; // Reset text color to default

}
void Console::drawProcess() {
	system("cls");
	std::cout << "Process: " << name << std::endl;
	std::cout << "ID: " << processId << std::endl;
	std::cout << "Current instruction line: " << currentLine << std::endl;
	std::cout << "Total line of instruction: " << totalLines << std::endl;
	std::cout << "Timestamp: " << timestamp << std::endl;

}


