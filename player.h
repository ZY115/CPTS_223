#pragma once

#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <string>

class Player {
private:
    std::string name;
    int score;

public:
    Player(const std::string& playerName);

    const std::string& getName() const;
    int getScore() const;
    void increaseScore(int points);
    void decreaseScore(int points);
};

#endif 
