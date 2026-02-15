#include <iostream>
#include <fstream>
#include <cstring>
#include "EmailSystem.hpp"

// Constructor to initialize emailCount
EmailSystem::EmailSystem() : emailCount(0) {}

// Helper function to split a string by a delimiter
void EmailSystem::split(const char* s, char delimiter, char parts[][256], int& partCount) {
    char* token;
    char* str = strdup(s);
    token = strtok(str, &delimiter);

    partCount = 0;
    while (token != nullptr && partCount < 6) {
        strncpy(parts[partCount], token, 256);
        partCount++;
        token = strtok(nullptr, &delimiter);
    }
    free(str);
}

// Load emails from file
void EmailSystem::loadEmailsFromFile(const char* filename) {
    std::ifstream file(filename);
    char line[256];
    
    while (file.getline(line, 256)) {
        char parts[6][256];
        int partCount = 0;
        split(line, ';', parts, partCount);

        if (partCount == 6 && emailCount < 100) {
            strncpy(emails[emailCount].sender, parts[0], 256);
            strncpy(emails[emailCount].recipient, parts[1], 256);
            strncpy(emails[emailCount].subject, parts[2], 256);
            strncpy(emails[emailCount].content, parts[3], 256);
            emails[emailCount].priority = atoi(parts[4]);
            strncpy(emails[emailCount].folder, parts[5], 256);
            emailCount++;
        }
    }
    file.close();
}

// Save emails to file
void EmailSystem::saveEmailsToFile(const char* filename) {
    std::ofstream file(filename);
    
    for (int i = 0; i < emailCount; i++) {
        file << emails[i].sender << ";"
             << emails[i].recipient << ";"
             << emails[i].subject << ";"
             << emails[i].content << ";"
             << emails[i].priority << ";"
             << emails[i].folder << "\n";
    }
    file.close();
}

// Add email to inbox
void EmailSystem::addEmailToInbox() {
    if (emailCount >= 100) {
        std::cout << "Email storage is full.\n";
        return;
    }

    Email email;
    std::cout << "Enter sender: ";
    std::cin.getline(email.sender, 256);
    std::cout << "Enter recipient: ";
    std::cin.getline(email.recipient, 256);
    std::cout << "Enter subject: ";
    std::cin.getline(email.subject, 256);
    std::cout << "Enter content: ";
    std::cin.getline(email.content, 256);
    std::cout << "Enter priority (1 - Low, 2 - Medium, 3 - High): ";
    std::cin >> email.priority;
    std::cin.ignore();  // Clear the newline character left by std::cin

    strncpy(email.folder, "inbox", 256);
    emails[emailCount] = email;
    emailCount++;

    saveEmailsToFile("Emails.txt");  // Save to file after adding
}

// Add email to outbox
void EmailSystem::addEmailToOutbox() {
    if (emailCount >= 100) {
        std::cout << "Email storage is full.\n";
        return;
    }

    Email email;
    std::cout << "Enter sender: ";
    std::cin.getline(email.sender, 256);
    std::cout << "Enter recipient: ";
    std::cin.getline(email.recipient, 256);
    std::cout << "Enter subject: ";
    std::cin.getline(email.subject, 256);
    std::cout << "Enter content: ";
    std::cin.getline(email.content, 256);
    std::cout << "Enter priority (1 - Low, 2 - Medium, 3 - High): ";
    std::cin >> email.priority;
    std::cin.ignore();  // Clear the newline character left by std::cin

    strncpy(email.folder, "outbox", 256);
    emails[emailCount] = email;
    emailCount++;

    saveEmailsToFile("Emails.txt");  // Save to file after adding
}

// Display emails from inbox or outbox
void EmailSystem::displayEmails(const char* folder) {
    bool found = false;
    for (int i = 0; i < emailCount; i++) {
        if (strcmp(emails[i].folder, folder) == 0) {
            std::cout << "Sender: " << emails[i].sender << "\n";
            std::cout << "Subject: " << emails[i].subject << "\n";
            std::cout << "Priority: " << emails[i].priority << "\n";
            std::cout << "Content: " << emails[i].content << "\n\n";
            found = true;
        }
    }
    if (!found) {
        std::cout << "No emails in the " << folder << ".\n";
    }
}

// Search for emails by a keyword
void EmailSystem::searchEmail() {
    char keyword[256];
    std::cout << "Enter keyword to search: ";
    std::cin.getline(keyword, 256);

    bool found = false;
    for (int i = 0; i < emailCount; i++) {
        if (strstr(emails[i].subject, keyword) != nullptr || strstr(emails[i].content, keyword) != nullptr) {
            std::cout << "Email found:\n";
            std::cout << "Sender: " << emails[i].sender << "\n";
            std::cout << "Subject: " << emails[i].subject << "\n";
            std::cout << "Content: " << emails[i].content << "\n\n";
            found = true;
        }
    }
    if (!found) {
        std::cout << "No emails found matching the search criteria.\n";
    }
}

// Detect spam emails based on keywords
void EmailSystem::detectSpam() {
    bool spamFound = false;
    const char* spamKeywords[5] = {"win", "free", "click here", "congratulations", "limited-time offer"};

    for (int i = 0; i < emailCount; i++) {
        for (int j = 0; j < 5; j++) {
            if (strstr(emails[i].content, spamKeywords[j]) != nullptr || strstr(emails[i].subject, spamKeywords[j]) != nullptr) {
                std::cout << "Spam detected in email from: " << emails[i].sender << "\n";
                std::cout << "Subject: " << emails[i].subject << "\n\n";
                spamFound = true;
                break;
            }
        }
    }
    if (!spamFound) {
        std::cout << "No spam detected.\n";
    }
}

// Prioritize emails by priority
void EmailSystem::prioritizeEmails() {
    for (int i = 0; i < emailCount - 1; i++) {
        for (int j = i + 1; j < emailCount; j++) {
            if (emails[i].priority > emails[j].priority) {
                Email temp = emails[i];
                emails[i] = emails[j];
                emails[j] = temp;
            }
        }
    }

    std::cout << "Emails have been prioritized by their priority number.\n";
    saveEmailsToFile("Emails.txt");  // Save the updated list of emails after prioritizing
}
