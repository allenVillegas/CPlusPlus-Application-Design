#include <iostream>
#include <string>

class Player
{
    private:
        std::string name;
        int health;
        int level;
        std::string weapon;

// Constructor
    public:
        Player(std::string playerName, int playerHealth, int playerLevel, std::string playerWeapon)
        {
            name = playerName;
            health = playerHealth;
            level = playerLevel;
            weapon = playerWeapon;
        }

// Member function 1
    void displayPlayerInfo()
    {
        std::cout << "\nPlayer Name: " << name << "\n"
                  << "Health: " << health << "\n"
                  << "Level: " << level << "\n"
                  << "Weapon: " << weapon << "\n";
    }

// Member function 2
    void levelUp()
    {
        level++;
    }

// Getter
    int getHealth()
    {
        return health;
    }
};

int main()
{
    Player player1("Wizard", 75, 12, "Magic Staff");
    Player player2("Knight", 100, 15, "Sword");

    player1.displayPlayerInfo();
    player2.displayPlayerInfo();

    return 0;
}