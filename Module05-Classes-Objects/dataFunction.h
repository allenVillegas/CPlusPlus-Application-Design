#ifndef DATAFUNCTION_H
#define DATAFUNCTION_H
    
#include <string>

void addData(int rank[], std::string name[], std::string platform[], int& size);
void displayData(int rank[], std::string name[], std::string platform[], int size);
int calculateResult(int rank[], int size);

#endif