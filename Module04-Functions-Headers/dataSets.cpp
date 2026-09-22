#include <iostream>

int main()
{
    int rank[5] = { 1, 2, 3, 4, 5 };

    std::string name[5] = { "Wii Sports", "Super Mario Bros.", "Mario Kart Wii", "Wii Sports Resort", "Pokemon Red/Pokemon Blue" };
    std::string platform[5] = { "Wii", "NES", "Wii", "Wii", "GB" };

    std::cout << "\n[Data Set]\n";
    for (int i = 0; i < 5; i++)
    {
        std::cout << "Record " << i << ": " << rank[i] << " - " << name[i] << " - " << platform[i] << "\n";
    }

    int* ptr = &rank[2];
    std::cout << "\nValue accessed through pointer: " << *ptr << "\n";

    return 0;
}