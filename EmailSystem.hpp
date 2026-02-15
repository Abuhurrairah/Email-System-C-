#ifndef EMAILSYSTEM_HPP
#define EMAILSYSTEM_HPP

class EmailSystem {
private:
    struct Email {
        char sender[256];
        char recipient[256];
        char subject[256];
        char content[256];
        int priority;
        char folder[256];
    };
    
    Email emails[100];  // Array to hold up to 100 emails
    int emailCount;  // Tracks the number of emails

public:
    EmailSystem();  // Constructor to initialize emailCount
    void loadEmailsFromFile(const char* filename);
    void saveEmailsToFile(const char* filename);
    void addEmailToInbox();
    void addEmailToOutbox();
    void displayEmails(const char* folder);
    void searchEmail();
    void detectSpam();
    void prioritizeEmails();

private:
    void split(const char* s, char delimiter, char parts[][256], int& partCount);
};

#endif // EMAILSYSTEM_HPP
