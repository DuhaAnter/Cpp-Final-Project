// expense.h
#ifndef EXPENSE_H
#define EXPENSE_H

#include <string>

using namespace std;

const int MAX_EXPENSES = 1000;

struct Expense
{
    int id;
    double amount;
    string category;
    string date;
};

// Global variables (declared here with extern, defined in expense.cpp)
extern Expense expenses[MAX_EXPENSES];
extern int expenseCount;

// Function declarations
int readExpensesFromFile(Expense *expenses, int& count, string& message);
int saveExpensesToFile();

void addExpense();
void viewExpenses(const Expense expenses[], int expenseCount);
void updateExpense();
void deleteExpense();



#endif // EXPENSE_H
