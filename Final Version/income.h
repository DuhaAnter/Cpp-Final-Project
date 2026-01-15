// income.h
#ifndef INCOME_H
#define INCOME_H
#include <string>

using namespace std;


//A way to organize data (struct = the blueprint)
struct Income
{
    int id;
    double amount;
    string date;
    string source;

};

const int MAX_INCOMES = 1000;  //const is safe in header
// Declaration (extern) for global variables // we made this so we can use them in both main.cpp and income.cpp
extern Income incomes[MAX_INCOMES];
extern int incomeCount;



// Declarations of functions

int readFromFile(Income *incomes, int &countRead, string &message);
void addIncome();
void updateIncome();
void viewIncomes(const Income incomes[], int incomeCount);
void deleteIncome();
int saveToFile();

#endif
