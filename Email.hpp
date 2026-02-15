#ifndef EMAIL_HPP
#define EMAIL_HPP

#define MAX_STRING_LENGTH 100  // Define the max length for strings

// Email structure without built-in containers (like std::string)
struct Email {
    char sender[MAX_STRING_LENGTH];
    char recipient[MAX_STRING_LENGTH];
    char subject[MAX_STRING_LENGTH];
    char content[MAX_STRING_LENGTH];
    int priority;
    char folder[MAX_STRING_LENGTH]; // "inbox" or "outbox"
};

#endif
