#include <iostream>
#include <string>
#include "dataFunction.h"

void addData(int rank[], std::string name[], std::string platform[], int& size)
{
    std::cout << "Enter rank for record " << size << ": ";
    std::cin >> rank[size];
    std::cin.ignore();

    std::cout << "Enter name for record " << size << ": ";
    std::getline(std::cin, name[size]);

    std::cout << "Enter platform for record " << size << ": ";
    std::getline(std::cin, platform[size]);

    size++;
}

void displayData(int rank[], std::string name[], std::string platform[], int size)
{
    std::cout << "\n[Data Set]\n";
    for (int i = 0; i < size; i++)
    {
        std::cout << "Record " << i << ": " 
                  << rank[i] << " - " 
                  << name[i] << " - " 
                  << platform[i] << "\n";
    }
}

int calculateResult(int rank[], int size)
{
    if (size == 0) return 0; // Avoid division by zero
    
    int sum = 0;
    for (int i = 0; i < size; i++)
    {
        sum += rank[i];
    }
    return sum / size; // Return the average rank
}