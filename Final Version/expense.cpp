// expense.cpp
#include "expense.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>  // for std::setw and std::left


using namespace std;


// Read all expenses from expense.txt

int readExpensesFromFile(Expense *expenses, int& count, string& message)
{
    ifstream file("expense.txt");
    if (file.fail())
    {
        message = "Error opening the file";
        return 0;
    }

    count = 0;
    string line;

    while (getline(file, line))
    {
        stringstream ss(line);
        string idStr, category, amountStr, date;

       getline(ss, idStr, '|') ;
        getline(ss, category, '|') ;
        getline(ss, amountStr, '|') ;
        getline(ss, date, '|');



            int id = stoi(idStr);
            double amount = stod(amountStr);

            expenses[count].id = id;
            expenses[count].category = category;
            expenses[count].amount = amount;
            expenses[count].date = date;
            count++;
    }

    file.close();
    message = (count == 0) ? "No expenses found" : "Expenses loaded successfully";
    return 1;
}


// Save all current expenses to expense.txt

int saveExpensesToFile()
{
    ofstream file("expense.txt");
    if (file.fail())
    {
        cout << "Error: Could not open expense.txt for writing!\n";
        return 0;
    }



    for (int i = 0; i < expenseCount; i++)
    {
        file << expenses[i].id << "|"
             << expenses[i].category << "|"
             << fixed << setprecision(2) << expenses[i].amount << "|"
             << expenses[i].date << "\n";
    }

    file.close();
    cout << "Data saved successfully on hard disk(" << expenseCount << " records).\n";
    return 1;
}


/////////////////////////////////////////////////////////////////////////////////

void addExpense()
{
        // Check if array is full
    if (expenseCount >= MAX_EXPENSES)
    {
        cout << "\nSorry, maximum number of expense records reached ("
             << MAX_EXPENSES << "). Cannot add more.\n\n";
        return;
    }

    cout << "\n=== Add New Expense ===\n";

    Expense newExpense;

    // 1. Automatically assign next ID
    if (expenseCount == 0)
    {
        newExpense.id = 1;
    }
    else
    {
        // Find the highest existing ID + 1
        int maxId = 0;
        for (int i = 0; i < expenseCount; i++)
        {
            if (expenses[i].id > maxId)
            {
                maxId = expenses[i].id;
            }
        }
        newExpense.id = maxId + 1;
    }

    // 2. Get amount (with validation)
    cout << "Amount (EGP): ";
    while (!(cin >> newExpense.amount) || newExpense.amount <= 0)
    {
        cout << "Please enter a positive number: ";
        cin.clear();
        cin.ignore(INT_MAX, '\n');
    }

    // Clear leftover newline before getline
    cin.ignore(INT_MAX, '\n');

    // 3. Get category
    cout << "Category (e.g. Food, Transport, Bills, Entertainment): ";
    getline(cin, newExpense.category);

    // 4. Get date
    cout << "Date ((e.g.15/01/2026) please DO NOT MISS WITH THE FORMAT): ";
    getline(cin, newExpense.date);

    // 5. Store in array
    expenses[expenseCount] = newExpense;
    expenseCount++;

    cout << "\nExpense added successfully!\n";
    cout << "ID: " << newExpense.id
         << " | " << newExpense.category
         << " | " << newExpense.amount
         << " EGP | " << newExpense.date << "\n\n";


    saveExpensesToFile();
}

/////////////////////////////////////////////////////////////////////////
void viewExpenses(const Expense expenses[], int expenseCount)
{
    // If no expenses yet
    if (expenseCount == 0)
    {
        cout << "\nNo expenses recorded yet.\n\n";
        return;
    }


    cout << "\n";
    cout << "==========================================================\n";
    cout << "                     All Expenses\n";
    cout << "==========================================================\n";

    // Table header
    cout << left
         << setw(6)  << "ID"
         << setw(20) << "Category"
         << setw(15) << "Amount (EGP)"
         << "Date\n";
    cout << "----------------------------------------------------------\n";


    for (int i = 0; i < expenseCount; i++)
    {
        cout << left
             << setw(6)  << expenses[i].id
             << setw(20) << expenses[i].category
             << setw(15) << fixed << setprecision(2) << expenses[i].amount
             << expenses[i].date
             << '\n';
    }

    cout << "----------------------------------------------------------\n";



}

/////////////////////////////////////////////////////////////////////////
void updateExpense()
{
    if (expenseCount == 0)
    {
        cout << "\nNo expenses to update. Please add some first.\n\n";
        return;
    }

    // Show current list so user can see IDs easily
    cout << "\nCurrent Expenses:\n";
    viewExpenses(expenses, expenseCount);

    cout << "\n=== Update Expense ===\n";

    int idToUpdate;
    cout << "Enter the ID of the expense you want to update: ";
    cin >> idToUpdate;

    // Find the expense with this ID
    int index = -1;
    for (int i = 0; i < expenseCount; i++)
    {
        if (expenses[i].id == idToUpdate)
        {
            index = i;
            break;
        }
    }

    if (index == -1)
    {
        cout << "\nError: No expense found with ID " << idToUpdate << "!\n\n";
        return;
    }

    // Show current record
    cout << "\nCurrent record:\n";
    cout << "ID: " << expenses[index].id << "\n";
    cout << "Category: " << expenses[index].category << "\n";
    cout << "Amount: " << expenses[index].amount << " EGP\n";
    cout << "Date: " << expenses[index].date << "\n\n";

    // Choose what to update
    cout << "What would you like to update?\n";
    cout << "1. Amount\n";
    cout << "2. Category\n";
    cout << "3. Date\n";
    cout << "4. Cancel (go back)\n";
    cout << "Your choice (1-4): ";

    int choice;
    cin >> choice;

    // Clear leftover newline
    cin.ignore(INT_MAX, '\n');

    switch (choice)
    {
        case 1: // Update amount
        {
            double newAmount;
            cout << "New amount (EGP): ";
            while (!(cin >> newAmount) || newAmount <= 0)
            {
                cout << "Please enter a positive number: ";
                cin.clear();
                cin.ignore(INT_MAX, '\n');
            }
            expenses[index].amount = newAmount;
            cout << "Amount updated successfully!\n";
            break;
        }

        case 2: // Update category
        {
            string newCategory;
            cout << "New category: ";
            getline(cin, newCategory);
            if (!newCategory.empty())
            {
                expenses[index].category = newCategory;
                cout << "Category updated successfully!\n";
            }
            else
            {
                cout << "No change (empty input).\n";
            }
            break;
        }

        case 3: // Update date
        {
            string newDate;
            cout << "New date (e.g. 15jan2026 or 2026-01-15): ";
            getline(cin, newDate);
            if (!newDate.empty())
            {
                expenses[index].date = newDate;
                cout << "Date updated successfully!\n";
            }
            else
            {
                cout << "No change (empty input).\n";
            }
            break;
        }

        case 4:
            cout << "Update cancelled.\n";
            return;

        default:
            cout << "Invalid choice! Update cancelled.\n";
            return;
    }

    // Show updated record
    cout << "\nUpdated record:\n";
    cout << "ID: " << expenses[index].id << "\n";
    cout << "Category: " << expenses[index].category << "\n";
    cout << "Amount: " << expenses[index].amount << " EGP\n";
    cout << "Date: " << expenses[index].date << "\n\n";


    saveExpensesToFile();
}

////////////////////////////////////////////////////////
void deleteExpense()
{
    if (expenseCount == 0)
    {
        cout << "\nNo expenses to delete. The list is empty.\n\n";
        return;
    }

    // Show current list so user can see IDs easily
    cout << "\nCurrent Expenses:\n";
    viewExpenses(expenses, expenseCount);

    cout << "\n=== Delete Expense ===\n";

    int idToDelete;
    cout << "Enter the ID of the expense you want to delete: ";
    cin >> idToDelete;

    // Find the index of the expense with this ID
    int index = -1;
    for (int i = 0; i < expenseCount; i++)
    {
        if (expenses[i].id == idToDelete)
        {
            index = i;
            break;
        }
    }

    if (index == -1)
    {
        cout << "\nError: No expense found with ID " << idToDelete << "!\n\n";
        return;
    }

    // Show the record that will be deleted
    cout << "\nYou are about to delete this record:\n";
    cout << "ID: " << expenses[index].id << "\n";
    cout << "Category: " << expenses[index].category << "\n";
    cout << "Amount: " << expenses[index].amount << " EGP\n";
    cout << "Date: " << expenses[index].date << "\n\n";

    // Confirmation
    cout << "Are you sure you want to delete this expense? (y/n): ";
    char confirm;
    cin >> confirm;

    if (confirm != 'y' && confirm != 'Y')
    {
        cout << "Deletion cancelled.\n\n";
        return;
    }

    // Shift all elements after index one position left
    for (int i = index; i < expenseCount - 1; i++)
    {
        expenses[i] = expenses[i + 1];
    }

    // Decrease the count
    expenseCount--;

    cout << "\nExpense with ID " << idToDelete << " deleted successfully!\n";
    cout << "Now you have " << expenseCount << " expense records.\n\n";


     saveExpensesToFile();
}

/////////////////////////////////////////////////////////////////////
