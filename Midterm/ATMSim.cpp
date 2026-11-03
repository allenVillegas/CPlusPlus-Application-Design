#include <cstdint>
#include <cstdio>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>


// Constants for the ATM simulation
const int MAX_ACCOUNTS = 100;
const int HISTORY_SIZE = 5;
const int MAX_PIN_ATTEMPTS = 3;
const double WITHDRAW_LIMIT = 500.00;
const char* const ACCOUNTS_FILE = "accounts.txt";
const char* const LOG_FILE = "transactions.txt";


// Provides 2 decimal places for money amounts
std::string money(double amount) 
{
    std::ostringstream out;
    out << "$" << std::fixed << std::setprecision(2) << amount;
    return out.str();
}

// Reads invalid input then reprompts until valid
std::string readLine(const std::string& prompt) 
{
    std::cout << prompt << std::flush;
    std::string line;
    if (!std::getline(std::cin, line)) throw std::runtime_error("input closed");
    return line;
}

// Invalidates non-integer input
bool readInt(const std::string& prompt, int& out) 
{
    std::istringstream in(readLine(prompt));
    in >> out;
    if (in.fail() || !in.eof()) 
    {
        std::cout << "  Please enter a whole number.\n";
        return false;
    }
    return true;
}

// Invalidates negative or zero amounts
bool readAmount(const std::string& prompt, double& out) 
{
    std::istringstream in(readLine(prompt));
    in >> out;
    if (in.fail() || !in.eof() || out <= 0.0) 
    {
        std::cout << "  Please enter a positive amount.\n";
        return false;
    }
    return true;
}


// Class 1: Account
class Account 
{
private:
    int32_t accountNumber; // exactly 4 bytes
    int16_t pin; // 4-digit PIN fits in 2 bytes (max 9999)
    std::string  ownerName;
    double  balance;
    std::string  history[HISTORY_SIZE]; // array: most recent transactions
    int historyCount;

public:
// Initial constructor
    Account() : accountNumber(0), pin(0), balance(0.0), historyCount(0) {}
// Constructor with parameters
    Account(int number, int pinCode, const std::string& name, double startBalance) : 
            accountNumber(number), pin(static_cast<int16_t>(pinCode)), ownerName(name),
            balance(startBalance), historyCount(0) {}
// Accessor methods
    int getNumber() const 
    { 
        return accountNumber;
    }
    int getPin() const 
    { 
        return pin; 
    }
    double getBalance() const 
    { 
        return balance; 
    }
    const std::string& getName() const 
    { 
        return ownerName; 
    }

    bool checkPin(int attempt) const 
    { 
        return attempt == pin; 
    }
// Deposits any amount
    void deposit(double amount) 
    {
        balance += amount;
        addHistory("Deposit: +" + money(amount));
    }
// Withdraws sufficient funds
    bool withdraw(double amount) 
    {
        if (amount > balance) return false;
        balance -= amount;
        addHistory("Withdrawal: -" + money(amount));
        return true;
    }

    // Changes balance without overwriting history
    void adjustBalance(double delta) 
    { 
        balance += delta; 
    }
// Adds new entry to session history
    void addHistory(const std::string& entry) 
    {
        if (historyCount == HISTORY_SIZE) 
        {          // shift array left
            for (int i = 1; i < HISTORY_SIZE; i++) history[i - 1] = history[i];
            historyCount--;
        }
        history[historyCount++] = entry;
    }
// Prints session history
    void printHistory() const 
    {
        std::cout << "\n--- Recent activity (this session) ---\n";
        if (historyCount == 0) std::cout << "  (no transactions yet)\n";
        for (int i = historyCount - 1; i >= 0; i--)
            std::cout << "  " << history[i] << "\n";
    }
};


// Class 2: Bank
class Bank 
{
private:
    Account accounts[MAX_ACCOUNTS];   // fixed-size array
    int count;

    // Insertion sort: binary search requires sorted data
    void sortAccounts() 
    {
        for (int i = 1; i < count; i++) 
        {
            Account key = accounts[i];
            int j = i - 1;
            while (j >= 0 && accounts[j].getNumber() > key.getNumber()) 
            {
                accounts[j + 1] = accounts[j];
                j--;
            }
            accounts[j + 1] = key;
        }
    }
// Creates default accounts.txt file with sample data
    bool createDefaultFile() const
    {
        std::ofstream out(ACCOUNTS_FILE);
        if (!out) return false;
        out << "# number pin balance name\n"
            << "1001 1234 2500.50 Alice Johnson\n"
            << "1002 4321 150.00 Bob Smith\n"
            << "1003 1111 10200.75 Carla Gomez\n"
            << "1004 9999 0.00 David Lee\n";
        return static_cast<bool>(out);
    }
// Sorts accounts array by account number (ascending)
public:
    Bank() : count(0) {}

    int size() const 
    { 
        return count; 
    }

    // Reads ACCOUNTS_FILE into array
    bool readAccountsFile()
    {
        std::ifstream in(ACCOUNTS_FILE);
        if (!in) return false;
// Skip comment lines and read valid account lines
        count = 0;
        bool firstLine = true;
        std::string line;
        while (std::getline(in, line) && count < MAX_ACCOUNTS)
        {
            std::istringstream fields(line);
            int number, pinCode;
            double bal;
            if (!(fields >> number >> pinCode >> bal)) 
            {
                continue; // bad line
            }
            std::string name;
            std::getline(fields, name); // rest = name
            accounts[count++] = Account(number, pinCode, name, bal);
        }
        sortAccounts();
        return true;
    }
// Loads accounts from file, or creates default if missing or invalid
    bool load()
    {
        bool opened = readAccountsFile();

        if (opened && count > 0) return true; // normal case

        // File is missing, empty, or has no valid lines: rebuild sample data
        if (!opened)
        {
            std::cout << "No " << ACCOUNTS_FILE << " found - creating sample data.\n";
        }
        else
        {
            // Keep copy of unreadable file - rename to .bak
            std::string backup = std::string(ACCOUNTS_FILE) + ".bak";
            std::rename(ACCOUNTS_FILE, backup.c_str());
            std::cout << ACCOUNTS_FILE << " had no valid accounts (expected lines like "
                      << "\"1001 1234 2500.50 Alice Johnson\").\n"
                      << "Old file saved as " << backup << "; creating sample data.\n";
        }
// Create new accounts.txt with sample data
        if (!createDefaultFile())
        {
            std::cerr << "Cannot write " << ACCOUNTS_FILE
                      << " in the current folder (is it read-only?).\n";
            return false;
        }
        readAccountsFile();
        return count > 0;
    }
// Saves current accounts array to ACCOUNTS_FILE
    bool save() const 
    {
        std::ofstream out(ACCOUNTS_FILE);
        if (!out) return false;
        out << "# number pin balance name\n";
        for (int i = 0; i < count; i++) 
        {
            out << accounts[i].getNumber() << " "
                << accounts[i].getPin() << " "
                << std::fixed << std::setprecision(2) << accounts[i].getBalance() << " "
                << accounts[i].getName() << "\n";
        }
        return true;
    }

    // Binary search on the sorted array data
    Account* findAccount(int number) 
    {
        int low = 0, high = count - 1;
        while (low <= high) 
        {
            int mid = low + (high - low) / 2;
            int midNumber = accounts[mid].getNumber();
            if (midNumber == number) return &accounts[mid];
            if (midNumber < number)  low  = mid + 1;
            else                     high = mid - 1;
        }
        return nullptr; // not pointed to any account if not found
    }
};


// Class 3: ATM
class ATM 
{
private:
    Bank& bank;
    Account* current; // points at logged-in account (nullptr if none)

    void logTransaction(const std::string& text) const 
    {
        std::ofstream log(LOG_FILE, std::ios::app);   // append mode
        if (log) log << text << "\n";
    }
// Saves current account data to ACCOUNTS_FILE
    void persist() const 
    {
        if (!bank.save()) std::cout << "  Warning: could not save " << ACCOUNTS_FILE << "\n";
    }
// Prompts for account number and PIN
    bool login() 
    {
        int number;
        if (!readInt("Account number: ", number)) return false;

        current = bank.findAccount(number); // binary search
        if (current == nullptr) 
        {
            std::cout << "  Account not found.\n";
            return false;
        }
// Prompt for PIN with limited attempts
        for (int attempt = 1; attempt <= MAX_PIN_ATTEMPTS; attempt++) 
        {
            int pin;
            if (!readInt("PIN: ", pin)) 
            { 
                attempt--; continue; 
            }
            if (current->checkPin(pin)) 
            {
                std::cout << "\nWelcome, " << (current->getName()) << "!\n";
                logTransaction("LOGIN account " + std::to_string(number));
                return true;
            }
            std::cout << "  Incorrect PIN (" << (MAX_PIN_ATTEMPTS - attempt)
                      << " attempts left).\n";
        }
        std::cout << "  Too many failed attempts. Card retained.\n";
        logTransaction("LOCKOUT account " + std::to_string(number));
        current = nullptr;
        return false;
    }
// Prompts for deposit amount and updates balance
    void doDeposit() 
    {
        double amount;
        if (!readAmount("Deposit amount: $", amount)) 
        {
            return;
        }
        current->deposit(amount);
        logTransaction("DEPOSIT " + money(amount) + " account " + std::to_string(current->getNumber()));
        persist();
        std::cout << "  Deposited " << money(amount) << ". New balance: "
                  << money(current->getBalance()) << "\n";
    }
// Prompts for withdraw amount and updates balance
    void doWithdraw() 
    {
        double amount;
        if (!readAmount("Withdraw amount: $", amount)) 
        {
            return;
        }
        if (amount > WITHDRAW_LIMIT) 
        {
            std::cout << "  Limit per transaction is " << money(WITHDRAW_LIMIT) << ".\n";
            return;
        }
        if (!current->withdraw(amount)) 
        {
            std::cout << "  Insufficient funds.\n";
            return;
        }
        logTransaction("WITHDRAW " + money(amount) + " account " + std::to_string(current->getNumber()));
        persist();
        std::cout << "  Please take your cash. New balance: "
                  << money(current->getBalance()) << "\n";
    }
// Prompts for target account number and transfer amount, updates both accounts
    void doTransfer() 
    {
        int targetNumber;
        double amount;
        if (!readInt("Transfer to account number: ", targetNumber)) return;
// Find target account using binary search
        Account* target = bank.findAccount(targetNumber); // second pointer
        if (target == nullptr)   
        { 
            std::cout << "  Destination account not found.\n"; return; 
        }
        if (target == current)   
        { 
            std::cout << "  Cannot transfer to the same account.\n"; return; 
        }
        if (!readAmount("Transfer amount: $", amount)) return;

        if (amount > current->getBalance()) 
        {
            std::cout << "  Insufficient funds.\n";
            return;
        }
        current->adjustBalance(-amount);
        target->adjustBalance(amount);
        current->addHistory("Transfer out to " + std::to_string(target->getNumber()) + " " + money(amount));
        target->addHistory("Transfer in from " + std::to_string(current->getNumber()) + " " + money(amount));
// Log transfer in transactions.txt
        logTransaction("TRANSFER " + money(amount) + " from " + std::to_string(current->getNumber())
                       + " to " + std::to_string(target->getNumber()));
        persist();
        std::cout << "  Transferred " << money(amount) << " to " << target->getName()
                  << ". New balance: " << money(current->getBalance()) << "\n";
    }
// Displays main menu
    void sessionMenu() 
    {
        bool active = true;
        while (active) 
        {
            std::cout << "\n===== MAIN MENU =====\n"
                      << "1. Check balance\n"
                      << "2. Deposit\n"
                      << "3. Withdraw\n"
                      << "4. Transfer\n"
                      << "5. Recent activity\n"
                      << "6. Log out\n";
            int choice;
            if (!readInt("Choice: ", choice)) continue;
// Handle user choice
            switch (choice) 
            {
                case 1: 
                    std::cout << "  Balance: " << money(current->getBalance()) << "\n"; 
                    break;
                case 2: 
                    doDeposit();
                    break;
                case 3: 
                    doWithdraw(); 
                    break;
                case 4: 
                    doTransfer(); 
                    break;
                case 5: 
                    current->printHistory(); 
                    break;
                case 6: 
                    active = false; 
                    break;
                default:
                    std::cout << "  Invalid choice.\n";
            }
        }
        logTransaction("LOGOUT account " + std::to_string(current->getNumber()));
        std::cout << "Goodbye, " << current->getName() << ". Please take your card.\n";
        current = nullptr;
    }
// Public interface
public:
    explicit ATM(Bank& b) : bank(b), current(nullptr) {}
// Displays sizes of data types used in this program
    static void showDataSizes() 
    {
        std::cout << "\n--- Data types used in this program (bytes) ---\n"
                  << "  char      : " << sizeof(char)     << "  (single character)\n"
                  << "  bool      : " << sizeof(bool)     << "  (flags)\n"
                  << "  int16_t   : " << sizeof(int16_t)  << "  (PIN, max 32767)\n"
                  << "  int32_t   : " << sizeof(int32_t)  << "  (account number)\n"
                  << "  int       : " << sizeof(int)      << "  (menu choices, counters)\n"
                  << "  long long : " << sizeof(long long)<< "  (cents arithmetic)\n"
                  << "  double    : " << sizeof(double)   << "  (balances)\n"
                  << "  pointer   : " << sizeof(Account*) << "  (Account*)\n"
                  << "  Account   : " << sizeof(Account)  << "  (whole object, includes strings + history array)\n"
                  << "  int32_t range: " << INT32_MIN << " to " << INT32_MAX << "\n";
    }
// Main loop: displays menu and handles user input
    void run() 
    {
        bool running = true;
        while (running) 
        {
            std::cout << "\n=========== ATM ===========\n"
                      << "1. Insert card (log in)\n"
                      << "2. Show data type sizes\n"
                      << "3. Exit\n";
            int choice;
            if (!readInt("Choice: ", choice)) continue;

            switch (choice) 
            {
                case 1:
                    if (login()) sessionMenu();
                    break;
                case 2: 
                    showDataSizes(); break;
                case 3: 
                    running = false; break;
                default: 
                    std::cout << "  Invalid choice.\n";
            }
        }
    }
};

// Main program
int main() 
{
    Bank bank;
    if (!bank.load()) 
    {
        std::cerr << "Could not load account data.\n";
        return 1;
    }
    std::cout << "Loaded " << bank.size() << " accounts from " << ACCOUNTS_FILE << ".\n";

    ATM atm(bank);
    try 
    {
        atm.run();
    } 
    catch (const std::runtime_error&) 
    {
        std::cout << "\nInput closed. Exiting.\n";
    }
    bank.save();
    std::cout << "Thank you for banking with us.\n";
    return 0;
}