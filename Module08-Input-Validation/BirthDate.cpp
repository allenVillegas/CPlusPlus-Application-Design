#include <iostream>
#include <string>
#include <cctype>

// Rejects negatives ("-5"), decimals ("3.5"), letters ("abc")
bool isWholeNumber(const std::string& text) 
{
    for (char c : text) 
    {
        if (!isdigit(static_cast<unsigned char>(c))) return false;
    }
    return true;
}

// Keeps asking until user enters valid input within specific range
int getValidNumber(const std::string& prompt, int min, int max, const std::string& rangeHint) 
{
    while (true) 
    {
        std::cout << prompt;
        std::string line;
        if (!std::getline(std::cin, line)) 
        {
            std::cout << "\nInput ended. Exiting.\n";
          //  exit(1);
        }

        // Check for empty input, negative numbers, decimals, non-digit characters
        if (line.empty()) 
        {
            std::cout << "Error: Input cannot be empty. Please enter a number.\n";
            continue;
        }
        if (line[0] == '-') 
        {
            std::cout << "Error: Negative numbers are not allowed.\n";
            continue;
        }
        if (line.find('.') != std::string::npos) 
        {
            std::cout << "Error: Decimals are not allowed. Please enter a whole number.\n";
            continue;
        }
        if (!isWholeNumber(line)) 
        {
            std::cout << "Error: Please enter digits only (no letters or symbols).\n";
            continue;
        }

        // Convert to integer and check range
        int value = stoi(line);
        if (value < min || value > max) 
        {
            std::cout << "Error: " << rangeHint << "\n";
            continue;
        }
        return value;
    }
}

// leap year if divisible by 4, except century years,
// must also be divisible by 400 (2000 is leap year, 1900 is not)
bool isLeapYear(int year) 
{
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

// Maximum days for a month:
// February = 29 leap year, otherwise 28,
// April/June/September/November = 30, others = 31.
int maxDaysInMonth(int month, int year) 
{
    switch (month) 
    {
        case 2:
            return isLeapYear(year) ? 29 : 28;
        case 4:
        case 6:
        case 9:
        case 11:
            return 30;
        default:
            return 31;
    }
}

// Main program
int main() 
{
    std::cout << "=== Birth Date Entry ===\n";

    int year = getValidNumber("Enter birth year (1900-2026): ", 1900, 2026,
                              "Year must be between 1900 and 2026.");

    int month = getValidNumber("Enter birth month (1-12): ", 1, 12,
                               "Month must be between 1 and 12.");

    int maxDay = maxDaysInMonth(month, year);
    std::string dayHint = "Day must be between 1 and " + std::to_string(maxDay) +
                          " for this month.";

    int day = getValidNumber("Enter birth day (1-" + std::to_string(maxDay) + "): ",
                             1, maxDay, dayHint);

    std::cout << "\nYour birth date is: " << month << "/" << day << "/" << year << "\n";

    return 0;
}