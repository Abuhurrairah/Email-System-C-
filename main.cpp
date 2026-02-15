#include <iostream>
#include "EmailSystem.hpp"

int main() {
    EmailSystem emailSystem;
    emailSystem.loadEmailsFromFile("Emails.txt");
    
    // Menu logic for interaction with the email system
    while (true) {
        std::cout << "\nEmail System Menu:\n";
        std::cout << "1. Add Email to Inbox\n";
        std::cout << "2. Add Email to Outbox\n";
        std::cout << "3. Display Inbox\n";
        std::cout << "4. Display Outbox\n";
        std::cout << "5. Search Email\n";
        std::cout << "6. Detect Spam\n";
        std::cout << "7. Prioritize Emails\n";
        std::cout << "8. Exit\n";
        std::cout << "Enter your choice: ";
        
        int choice;
        std::cin >> choice;
        std::cin.ignore();  // Ignore leftover newline
        
        switch (choice) {
            case 1:
                emailSystem.addEmailToInbox();
                break;
            case 2:
                emailSystem.addEmailToOutbox();
                break;
            case 3:
                emailSystem.displayEmails("inbox");
                break;
            case 4:
                emailSystem.displayEmails("outbox");
                break;
            case 5:
                emailSystem.searchEmail();
                break;
            case 6:
                emailSystem.detectSpam();
                break;
            case 7:
                emailSystem.prioritizeEmails();
                break;
            case 8:
                emailSystem.saveEmailsToFile("Emails.txt");
                std::cout << "Exiting...\n";
                return 0;
            default:
                std::cout << "Invalid choice, please try again.\n";
        }
    }

    return 0;
}
