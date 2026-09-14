# include <iostream>
# include <string>

int main ()
{
    std::string name = "Clyde";
    int age = 24;
    int id = 9341;
    double score = 63.4;
    char classification = 'D';
    bool subject = true;

    std::cout << "\n[Examination Results]\n" 
         << "Subject Name: " << name << "\n"
         << "Subject Age: " << age << "\n"
         << "Subject ID: " << id << "\n"
         << "Subject Score: " << score << "%\n"
         << "Subject Classification: " << classification << "\n"
         << "Subject to termination: " << subject << "\n";

              return 0;
}