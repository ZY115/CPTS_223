#pragma once

#include <iostream>
#include <string>
#include "FileHandler.h"

class Game {
public:
    Game(const FileHandler& handler);

    void start();
    void continueGame();
    void addCommand();
    void removeCommand();

private:
    FileHandler fileHandler;
    std::string playerName;
    int playerScore;

    void displayMainMenu();
    void displayCommands();
    void play();
    bool askQuestion(int questionIndex);
};
