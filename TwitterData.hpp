#pragma once
#ifndef TWITTER_DATA_H
#define TWITTER_DATA_H

#include <iostream>
#include <string>

class TwitterData
{
public:
    TwitterData() = default;
    TwitterData(const std::string& userName, const std::string& actualName,
        const std::string& email, const std::string& category, int numTweets)
        : mpUserName(userName), mpActualName(actualName),
        mpEmail(email), mpCategory(category), mpNumTweets(numTweets) {}

    std::string getUserName() const;   // Return a copy of the string, not the pointer
    std::string getActualName() const; // Return a copy of the string, not the pointer
    std::string getEmail() const;	   // Return a copy of the string, not the pointer
    std::string getCategory() const;   // Return a copy of the string, not the pointer
    int getNumTweets() const;		   // Return a copy of the integer, not the pointer

    void setUserName(const std::string& newUserName);
    void setActualName(const std::string& newActualName);
    void setEmail(const std::string& newEmail);
    void setCategory(const std::string& newCategory);
    void setNumTweets(int newNumTweets);

    std::string print() const;

private:
    std::string mpUserName, mpActualName,
        mpEmail, mpCategory;
    int mpNumTweets;
};

#endif
