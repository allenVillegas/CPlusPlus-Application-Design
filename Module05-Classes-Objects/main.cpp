#include <iostream>
#include <string>
#include "dataFunction.h"

int main() 
{
    int rank[10] = {1, 2, 3};
    std::string name[10] = {"Arthur", "John", "Jack"};
    std::string platform[10] = {"PC", "Playstation", "Mobile"};

    int size = 3;

    displayData(rank, name, platform, size);
    addData(rank, name, platform, size);

    std::cout << "\n[Updated Data Set]\n";
    displayData(rank, name, platform, size);

    int average = calculateResult(rank, size);
    std::cout << "Average rank: " << average << "\n";

    return 0;
}