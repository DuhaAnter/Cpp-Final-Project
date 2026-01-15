#include <iostream>
#include <limits>
using namespace std;

void clearInput() // if user enters anything but what we want
{
    cin.clear();
    cin.ignore(INT_MAX, '\n');
}

int readChoice(int min, int max)
{
    int choice;
    while (true)
    {
        cout << "choose from (" << min << "-" << max << "): ";
        if (cin >> choice && choice >= min && choice <= max)
        {
            // valid choice
            return choice;
        }
        cout << "Invalid choice! Please enter number between " << min << " and " << max << ".\n";
        clearInput();
    }
}

void incomeMenu()
{
    while(true)
    {

    cout << "\n=== Income Management ===\n";
    cout << "1. Add new income\n";
    cout << "2. Update income\n";
    cout << "3. View all incomes\n";
    cout << "4. Delete income\n";
    cout << "5. Back\n";

    int choice = readChoice(1,5);
    if (choice == 5) return;

    cout << "\nYou selected: ";
    switch (choice)
    {
    case 1:
        cout << "Add income\n";
        break;
    case 2:
        cout << "Update income\n";
        break;
    case 3:
        cout << "View incomes\n";
        break;
    case 4:
        cout << "Delete income\n";
        break;
    }
    // Here you can call another function or just wait
    cout << "\nPress Enter to continue...";
    cin.get();         // this one eats the leftover Enter → finishes immediately
    cin.get();         // this one waits for the real new Enter from the user


    }//end of while
}
//////////////////////////////////////////////////////////////////////////
void expenseMenu()
{
    while(true)
    {

    cout << "\n=== Expense Management ===\n";
    cout << "1. Add new Expense\n";
    cout << "2. Update Expense\n";
    cout << "3. View all Expenses\n";
    cout << "4. Delete Expense\n";
    cout << "5. Back\n";

    int choice = readChoice(1,5);
    if (choice == 5) return;

    cout << "\nYou selected: ";
    switch (choice)
    {
    case 1:
        cout << "Add Expense\n";
        break;
    case 2:
        cout << "Update Expense\n";
        break;
    case 3:
        cout << "View Expenses\n";
        break;
    case 4:
        cout << "Delete Expense\n";
        break;
    }
    // Here you can call another function or just wait
    cout << "\nPress Enter to continue...";
    cin.get();         // this one eats the leftover Enter → finishes immediately
    cin.get();         // this one waits for the real new Enter from the user


    }//end of while
}
///////////////////////////////////////////////////////////////
int main()
{
    cout << "Welcome to Personal Finance Manager\n\n";

    while (true)
    {
        cout << "1. Income Management\n";
        cout << "2. Expense Management\n";
        cout << "3. Budget Management\n";
        cout << "4. Reports\n";
        cout << "0. Exit\n";

        int choice = readChoice(0,4);

        if (choice == 0)
        {
            cout << "\nGoodbye! Have a nice day \n";
            break;
        }

        switch (choice)
        {
        case 1:
            incomeMenu();
            break;
        case 2:
            expenseMenu();
            break;
        case 3:
            cout << "Budget - coming soon\n";
            break;
        case 4:
            cout << "Reports - coming soon\n";
            break;
        }
    }

    return 0;
}
