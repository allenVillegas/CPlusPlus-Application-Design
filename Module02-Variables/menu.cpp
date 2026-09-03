#include <iostream>

int main()
{
    int choice;

    // Main menu loop
    do
    {
        // Display main menu
        std::cout << "\n[ Main Menu ]"
                  << "\n\n1. [ Start ]"
                  << "\n2. [ Tutorial ]"
                  << "\n3. [ Settings ]"
                  << "\n4. [ About ]"
                  << "\n5. [ Exit ]"
                  << "\n\nEnter your choice: ";

        if (!(std::cin >> choice)) // Check for invalid input
        {
            std::cout << "\nInvalid input!"
                      << "\nPlease enter a number between 1 and 5...\n";
            std::cin.clear(); // Clear error flag
            std::cin.ignore(1000, '\n'); // Discard invalid input
            
            continue; // Restart loop
        }

        // Get user's choice
        switch (choice)
        {
        case 1:
            std::cout << "\nStarting the program...\n"
                      << "Hello World!\n";
            break;
        case 2:
            std::cout << "\nOpening tutorial...\n"
                      << "Enter any option to see its function!\n";
            break;
        case 3:
            std::cout << "\nOpening settings...\n"
                      << "Settings are not available yet :(\n";
            break;
        case 4:
            std::cout << "\nAbout this program...\n"
                      << "This is a simple C++ program that demonstrates a menu system.\n";
            break;
        case 5:
            std::cout << "\nExiting the program...\n"
                      << "Goodbye!\n";
            break;
        default:    
            std::cout << "\nInvalid choice!"
                      <<  "\nPlease try again...\n";
        }
    
    } while (choice != 5);

    return 0;
}