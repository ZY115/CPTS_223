#include "FileHandler.h"
#include <iostream>
#include <fstream>
#include <sstream>

FileHandler::FileHandler() {}

bool FileHandler::readCommands(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Unable to open command file." << std::endl;
        return false;
    }

    commands.clear();
    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string command, description;
        if (std::getline(iss, command, ',') && std::getline(iss, description)) {
            commands.emplace_back(command, description);
        }
    }

    file.close();
    return true;
}


bool FileHandler::readProfiles(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Unable to open player files." << std::endl;
        return false;
    }

    profiles.clear();
    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string playerName;
        int score;
        if (std::getline(iss, playerName, ',') && iss >> score) {
            profiles.emplace_back(playerName, score);
        }
    }

    file.close();
    return true;
}

bool FileHandler::writeProfiles(const std::string& filename) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Unable to write to player file." << std::endl;
        return false;
    }

    for (const auto& profile : profiles) {
        file << profile.first << "," << profile.second << std::endl;
    }

    file.close();
    return true;
}

int FileHandler::getCommandCount() const {
    return static_cast<int>(commands.size());
}

const std::string& FileHandler::getCommand(int index) const {
    return commands[index].first;
}

const std::string& FileHandler::getDescription(int index) const {
    return commands[index].second;
}

bool FileHandler::addCommand(const std::string& command, const std::string& description) {
    commands.emplace_back(command, description);
    std::ofstream outfile("commands.csv", std::ios::app);

    if (!outfile.is_open()) {
        std::cerr << "Unable to open command file." << std::endl;
        return false;
    }

    outfile << command << "," << description << std::endl;
    outfile << std::flush;
    outfile.close();
    std::cout << "The added command has been successfully written" << std::endl;

    return true;
}

bool FileHandler::removeCommand(int index) {
    if (index < 0 || index >= static_cast<int>(commands.size())) {
        return false;
    }
    commands.erase(commands.begin() + index);
    std::ofstream outfile("commands.csv");

    if (!outfile.is_open()) {
        std::cerr << "Unable to open command file." << std::endl;
        return false;
    }
    for (const auto& cmd : commands) {
        outfile << cmd.first << "," << cmd.second << std::endl;
    }

    outfile.close(); 

    std::cout << "The command has been successfully deleted" << std::endl;
    return true;
}

int FileHandler::getProfileScore(const std::string& playerName) const {
    for (const auto& profile : profiles) {
        if (profile.first == playerName) {
            return profile.second;
        }
    }
    return 0;
}

bool FileHandler::setProfileScore(const std::string& playerName, int score) {
    for (auto& profile : profiles) {
        if (profile.first == playerName) {
            profile.second = score;
            return true;
        }
    }
    profiles.emplace_back(playerName, score);
    return true;
}
