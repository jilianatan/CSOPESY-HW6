#pragma once

#include <string>
class Console {
private:
    std::string name;
    int currentLine;
    int totalLines;
    std::string timestamp;
    int processId;
    
public:
    Console(std::string n, int cLine, int tLines, int id);

    void drawMain();
    void drawProcess();

    std::string getName() const;

};
