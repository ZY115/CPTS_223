#include "Player.h"

Player::Player(const std::string& playerName) : name(playerName), score(0) {}

const std::string& Player::getName() const {
    return name;
}

int Player::getScore() const {
    return score;
}

void Player::increaseScore(int points) {
    score += points;
}

void Player::decreaseScore(int points) {
    score -= points;
    if (score < 0) {
        score = 0;
    }
}
