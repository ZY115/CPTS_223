#pragma once

#include <string>
#include <vector>

class FileHandler {
public:
    FileHandler();

    bool readCommands(const std::string& filename);
    bool readProfiles(const std::string& filename);
    bool writeProfiles(const std::string& filename);

    int getCommandCount() const;
    const std::string& getCommand(int index) const;
    const std::string& getDescription(int index) const;

    bool addCommand(const std::string& command, const std::string& description);
    bool removeCommand(int index);

    int getProfileScore(const std::string& playerName) const;
    bool setProfileScore(const std::string& playerName, int score);

private:
    std::vector<std::pair<std::string, std::string>> commands;
    std::vector<std::pair<std::string, int>> profiles;
    std::string Filename = "commands.csv";
};
