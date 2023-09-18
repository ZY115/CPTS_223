#include "Game.h"
#include <algorithm>

Game::Game(const FileHandler& handler) : fileHandler(handler), playerScore(0) {}

void Game::start() {
    playerScore = 0;
    displayMainMenu();
}

void Game::addCommand() {
    std::cout << "Please enter the command to be added:";
    std::string command, description;
    std::cin >> command;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "Please enter a description of the order:";
    std::getline(std::cin, description);

    if (fileHandler.addCommand(command, description)) {
        std::cout << "The command has been added." << std::endl;
    }
    else {
        std::cout << "Failed to add command." << std::endl;
    }
}

void Game::removeCommand() {
    displayCommands();
    if (fileHandler.getCommandCount() == 0) {
        std::cout << "No removable commands." << std::endl;
        return;
    }

    std::cout << "Please enter the order number to be deleted: (1-" << fileHandler.getCommandCount() << "): ";
    int choice;
    std::cin >> choice;
    if (choice < 1 || choice > fileHandler.getCommandCount()) {
        std::cout << "null hypothesis." << std::endl;
    }
    else {
        if (fileHandler.removeCommand(choice - 1)) {
            std::cout << "The command has been deleted.." << std::endl;
        }
        else {
            std::cout << "Delete command failed." << std::endl;
        }
    }
}

void Game::displayMainMenu() {
    while (true) {
        std::cout << "\nMain Menu:\n";
        std::cout << "1. Game rules\n";
        std::cout << "2. Start new game\n";
        std::cout << "3. Continue game\n";
        std::cout << "4. Add command\n";
        std::cout << "5. Delete command\n";
        std::cout << "6. Quit game\n";
        std::cout << "please select: ";
        
        int choice;
        std::cin >> choice;
        fileHandler.readCommands("commands.csv");
        fileHandler.writeProfiles("profiles.csv");
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (choice) {
        case 1:
            std::cout << "This is a game to practice linux commands and instructions. \n";
            std::cout << "The player needs to select the number of questions he/she wishes to answer (minimum five).\n";
            std::cout << "Then they will be presented with a question and three options.\n";
            std::cout << "The player has to choose the option that he/she thinks is correct.\n";
            std::cout << "A point is awarded for a correct choice and a point is deducted for a wrong choice. \n";
            std::cout << "Note that your score can be negative.\n";
            break;
        case 2:
            std::cout << "Enter your name:";
            std::getline(std::cin, playerName);
            play();
            break;
        case 3:
            continueGame();
            break;
        case 4:
            addCommand();
            break;
        case 5:
            removeCommand();
            break;
        case 6:
            return;
        default:
            std::cout << "Input error, please re-select." << std::endl;
            break;
        }
    }
}

void Game::displayCommands() {
    int count = fileHandler.getCommandCount();
    std::cout << "List of commands:" << std::endl;
    for (int i = 0; i < count; ++i) {
        std::cout << i + 1 << ". " << fileHandler.getCommand(i) << " - " << fileHandler.getDescription(i) << std::endl;
    }
}

void Game::play() {
    
    
    int maxQuestions = std::min(fileHandler.getCommandCount(), 100);
    int questionCount;

    do {
        std::cout << "Please enter the number of questions you wish to answer: (5-" << maxQuestions << "): ";
        std::cin >> questionCount;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    } while (questionCount < 5 || questionCount > maxQuestions);

    

    for (int i = 0; i < questionCount; ++i) {
        int questionIndex = i % fileHandler.getCommandCount();
        if (askQuestion(questionIndex)) {
            playerScore++;
            std::cout << "Answer correctly!\n";
        }
        else {
            playerScore--;
            std::cout << "Wrong answer!\n";
        }
    }

    fileHandler.setProfileScore(playerName, playerScore);
    std::cout << "Game over, score:" << playerScore << std::endl;
}

bool Game::askQuestion(int questionIndex) {
    std::cout << "\nQuestion" << questionIndex + 1 << ":\n";
    std::cout << "Commands: " << fileHandler.getCommand(questionIndex) << "\n";

    std::vector<int> shuffledIndices(fileHandler.getCommandCount());
    for (int i = 0; i < fileHandler.getCommandCount(); ++i) {
        shuffledIndices[i] = i;
    }

    std::random_shuffle(shuffledIndices.begin(), shuffledIndices.end());

    for (int i = 0; i < 3; ++i) {
        std::cout << i + 1 << ". " << fileHandler.getDescription(shuffledIndices[i]) << "\n";
    }

    int playerChoice;
    std::cout << "Please enter your choice (1-3): ";
    std::cin >> playerChoice;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    int correctOption = 1 + std::find(shuffledIndices.begin(), shuffledIndices.end(), questionIndex) - shuffledIndices.begin();

    return playerChoice == correctOption;
}

void Game::continueGame() {
    std::cout << "Enter your name";
    std::getline(std::cin, playerName);

    int savedScore = fileHandler.getProfileScore(playerName);
    if (savedScore == NULL) {
        std::cout << "No games matching this name were found, a new game has been started for you!\n";
        
        playerScore = 0;
        play();
    }
    else {
        std::cout << "Continue the last game and score:" << savedScore << "\n";
        playerScore = savedScore;
        play();
    }
}
