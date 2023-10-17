#include <iostream>
#include <map>
#include "TwitterData.hpp"
using namespace std;

int main(int argc, char* argv[])
{
    string raw_data[5][6] = {
        {"rangerPower", "Smit", "Rick", "smitRick@gmail.com", "1117", "power lifting"},
        {"kittyKat72", "Smith", "Kathryn", "kat@gmail.com", "56", "health"},
        {"lexi5", "Anderson", "Alexis", "lexi5@gmail.com", "900", "education"},
        {"savage1", "Savage", "Ken", "ksavage@gmail.com", "17", "president"},
        {"smithMan", "Smith", "Rick", "rick@hotmail.com", "77", "olympics"}
    };

    TwitterData* twitter_data = new TwitterData[5];
    for (int i = 0; i < 5; ++i)
    {
        twitter_data[i].setUserName(raw_data[i][0]);
        twitter_data[i].setActualName(raw_data[i][2] + " " + raw_data[i][1]);
        twitter_data[i].setEmail(raw_data[i][3]);
        twitter_data[i].setNumTweets(stoi(raw_data[i][4]));
        twitter_data[i].setCategory(raw_data[i][5]);
    }

    // Map Scenario 1: Search based on UserName
    std::map<std::string, TwitterData> searchByName;
    for (int i = 0; i < 5; ++i) {
        searchByName[raw_data[i][0]] = twitter_data[i];
    }

    cout << "Print searchByName map:" << endl;
    for (const auto& pair : searchByName) {
        cout << "Key: " << pair.first << ", Value: " << pair.second.print() << endl;
    }

    cout << "Search for key: savage1 Value: " << searchByName["savage1"].print() << endl;
    searchByName.erase("savage1");

    // Map Scenario 2: Search based on EmailAddress
    std::map<std::string, TwitterData> searchByEmail;
    for (int i = 0; i < 5; ++i) {
        searchByEmail[raw_data[i][3]] = twitter_data[i];
    }

    cout << "Print searchByEmail map:" << endl;
    for (const auto& pair : searchByEmail) {
        cout << "Key: " << pair.first << ", Value: " << pair.second.print() << endl;
    }

    cout << "Search for key: kat@gmail.com Value: " << searchByEmail["kat@gmail.com"].print() << endl;
    searchByEmail.erase("kat@gmail.com");

    delete[] twitter_data;
    return 0;
}
