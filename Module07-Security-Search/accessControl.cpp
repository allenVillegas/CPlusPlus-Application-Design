#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

// Store record information
struct Record 
{
    int id;
    std::string name;
    double grade;
};

// Sort records by ID
void sortRecords(std::vector<Record>& records) 
{
    std::sort(records.begin(), records.end(),
        [](const Record& a, const Record& b) 
        {
            return a.id < b.id;
        });
}

// Display all records
void displayRecords(const std::vector<Record>& records) 
{
    if (records.empty()) 
    {
        std::cout << "No records available.\n";
        return;
    }

    std::cout << "\n--- Student Records ---\n";

    for (const Record& record : records) 
    {
        std::cout << "ID: " << record.id
                  << " | Name: " << record.name
                  << " | Grade: " << record.grade << '\n';
    }
}

// Binary search by ID
int binarySearch(const std::vector<Record>& records, int targetID) 
{
    int size = records.size();
    int low = 0;
    int high = size - 1;

    while (low <= high) 
    {
        int mid = low + (high - low) / 2;

        if (records[mid].id == targetID) 
        {
            return mid;
        }
        else if (records[mid].id < targetID) 
        {
            low = mid + 1;
        }
        else 
        {
            high = mid - 1;
        }
    }

    return -1;
}

// Add a record (Admin only)
void addRecord(std::vector<Record>& records, bool isAdmin) 
{
    if (!isAdmin) 
    {
        std::cout << "Access denied. Admin only.\n";
        return;
    }

    Record newRecord;

    std::cout << "Enter student ID: ";
    std::cin >> newRecord.id;

    // Prevent duplicate IDs
    if (binarySearch(records, newRecord.id) != -1) 
    {
        std::cout << "A record with that ID already exists.\n";
        return;
    }

    std::cout << "Enter student name: ";
    std::getline(std::cin >> std::ws, newRecord.name);

    std::cout << "Enter student grade: ";
    std::cin >> newRecord.grade;

    records.push_back(newRecord);
    sortRecords(records);

    std::cout << "Record added successfully.\n";
}

// Edit a record (Admin only)
void editRecord(std::vector<Record>& records, bool isAdmin) 
{
    if (!isAdmin) 
    {
        std::cout << "Access denied. Admin only.\n";
        return;
    }

    int id;
    std::cout << "Enter the ID to edit: ";
    std::cin >> id;

    int index = binarySearch(records, id);

    if (index == -1) 
    {
        std::cout << "Record not found.\n";
        return;
    }

    std::cout << "Enter new name: ";
    std::getline(std::cin >> std::ws, records[index].name);

    std::cout << "Enter new grade: ";
    std::cin >> records[index].grade;

    std::cout << "Record updated successfully.\n";
}

// Delete a record (Admin only)
void deleteRecord(std::vector<Record>& records, bool isAdmin) 
{
    if (!isAdmin) 
    {
        std::cout << "Access denied. Admin only.\n";
        return;
    }

    int id;
    std::cout << "Enter the ID to delete: ";
    std::cin >> id;

    int index = binarySearch(records, id);

    if (index == -1) 
    {
        std::cout << "Record not found.\n";
        return;
    }

    records.erase(records.begin() + index);
    std::cout << "Record deleted successfully.\n";
}

// Search for a record (Both roles)
void searchRecord(const std::vector<Record>& records) 
{
    int id;

    std::cout << "Enter the ID to search for: ";
    std::cin >> id;

    int index = binarySearch(records, id);

    if (index == -1) 
    {
        std::cout << "Record not found.\n";
    }
    else 
    {
        std::cout << "\nRecord found:\n"
                  << "ID: " << records[index].id << '\n'
                  << "Name: " << records[index].name << '\n'
                  << "Grade: " << records[index].grade << '\n';
    }
}

int main() 
{
    std::vector<Record> records = 
    {
        {105, "Alice", 92.5},
        {101, "Bob", 85.0},
        {110, "Charlie", 78.5}
    };

    sortRecords(records);

    bool isAdmin = false;   // true = Admin, false = Regular User

    int roleChoice;
    std::cout << "\nSelect user role:\n"
              << "1. Admin\n"
              << "2. Regular User\n"
              << "Choice: ";
    std::cin >> roleChoice;

    if (roleChoice == 1) 
    {
        isAdmin = true;
    }
    else if (roleChoice == 2) 
    {
        isAdmin = false;
    }
    else 
    {
        std::cout << "Invalid role selection.\n";
        return 1;
    }

    int choice;

    do 
    {
        std::cout << "\n--- Student Record Management ---\n"
                  << "1. View records\n"
                  << "2. Search record by ID\n"
                  << "3. Add record (Admin only)\n"
                  << "4. Edit record (Admin only)\n"
                  << "5. Delete record (Admin only)\n"
                  << "0. Exit\n"
                  << "Choice: ";
        std::cin >> choice;

        switch (choice) 
        {
            case 1:
                displayRecords(records);
                break;

            case 2:
                searchRecord(records);
                break;

            case 3:
                addRecord(records, isAdmin);
                break;

            case 4:
                editRecord(records, isAdmin);
                break;

            case 5:
                deleteRecord(records, isAdmin);
                break;

            case 0:
                std::cout << "Exiting program.\n";
                break;

            default:
                std::cout << "Invalid choice.\n";
        }

    } 
    while (choice != 0);

    return 0;
}