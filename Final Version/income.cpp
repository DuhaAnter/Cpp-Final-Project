#include <iostream>
#include <fstream>
#include <iomanip>  // for std::setw and std::left
#include "income.h"
//C++ has a tool called string stream that treats a string like a mini-file. You can "read" from it just like cin.
#include<sstream>
using namespace std;



// i will send the address of the place where this fun store what it did read
int readFromFile(Income *incomes, int &countRead, string &message)
{
    //1.
    ifstream readFile;
    //2.
    readFile.open("income.txt");

    if(readFile.fail())
    {
        message = "Error opening the file";
        return 0; // false
    }

    string fileLine;


    // i will use countRead as index

    while(getline(readFile, fileLine)) // is true
    {
        //cout << fileLine << endl;
        stringstream ss(fileLine);

        // Variables to hold each piece
        string idStr, source, amountStr, date;

        // Extract pieces using | as delimiter
        getline(ss, idStr, '|');    // Gets "1"
        getline(ss, source, '|');   // Gets "salary"
        getline(ss, amountStr, '|'); // Gets "10000"
        getline(ss, date, '|');     // Gets "15jan2026"

        //  Convert strings to appropriate types
        int id = stoi(idStr);           // "1" → 1
        double amount = stod(amountStr); // "10000" → 10000.0

        // Now store in  struct
        incomes[ countRead].id = id;
        incomes[ countRead].source =source;
        incomes[ countRead].amount = amount;
        incomes[ countRead].date = date;
        countRead++;

    }
    //cout<<countRead;
    message = "SUCCESS";
    return 1; //true
}


int saveToFile()
{
    ofstream writeFile("income.txt");

    if (writeFile.fail())
    {
        cout << "Error: Could not open file for writing!\n";
        return 0;
    }

    for (int i = 0; i < incomeCount; i++)
    {
        writeFile << incomes[i].id << "|"
                  << incomes[i].source << "|"
                  << fixed << setprecision(2) << incomes[i].amount << "|"
                  << incomes[i].date << "\n";
    }

    writeFile.close();

    cout << "Data saved successfully on hard disk(" << incomeCount << " records).\n";
    return 1;
}
/////////////////////////////////////////////////////////////////////////////////////////////


void viewIncomes(const Income incomes[], int incomeCount)
{
    if (incomeCount == 0)
    {
        cout << "\nNo incomes recorded yet.\n\n";
        return;
    }


    cout << "\n";
    cout << "============================================================\n";
    cout << "                     All Incomes\n";
    cout << "============================================================\n";

    // Table header with alignment
    cout << left
         << setw(6)  << "ID"
         << setw(20) << "Source"
         << setw(15) << "Amount (EGP)"
         << "Date\n";
    cout << "------------------------------------------------------------\n";

    // ───────────────────────────────────────────────────────────────
    // Print each income record
    // ───────────────────────────────────────────────────────────────
    for (int i = 0; i < incomeCount; i++)
    {
        cout << left
             << setw(6)  << incomes[i].id
             << setw(20) << incomes[i].source
             << setw(15) << fixed << setprecision(2) << incomes[i].amount
             << incomes[i].date
             << '\n';
    }

    cout << "------------------------------------------------------------\n";
}
/////////////////////////////////////////////////////////////////////////////////////////////////
void addIncome()
{
    // Check if array is full
    if (incomeCount >= MAX_INCOMES)
    {
        cout << "\nSorry, maximum number of income records reached ("
             << MAX_INCOMES << "). Cannot add more.\n\n";
        return;
    }



    cout << "\n=== Add New Income ===\n";

    Income newIncome;

    // 1. Automatically assign next ID
    if (incomeCount == 0)
    {
        newIncome.id = 1;
    }
    else
    {
        // Find the highest existing ID + 1
        int maxId = 0;
        for (int i = 0; i < incomeCount; i++)
        {
            if (incomes[i].id > maxId)
            {
                maxId = incomes[i].id;
            }
        }
        newIncome.id = maxId + 1;
    }

    // 2. Get amount (with validation)
    cout << "Amount (EGP): ";
    while (!(cin >> newIncome.amount) || newIncome.amount <= 0)
    {
        cout << "Please enter a positive number: ";
        cin.clear();
        cin.ignore(INT_MAX , '\n');
    }

    // Clear leftover newline before getline
    cin.ignore(INT_MAX , '\n');

    // 3. Get source (can be any text)
    cout << "Source (e.g. Salary): ";
    getline(cin, newIncome.source);

    // 4. Get date (simple text input)
    cout << "Date (e.g.15/01/2026) please DO NOT MISS WITH THE FORMAT: ";
    getline(cin, newIncome.date);

    // 5. Store in array
    incomes[incomeCount] = newIncome;
    incomeCount++;

    cout << "\nIncome added successfully!\n";
    cout << "ID: " << newIncome.id
         << " | " << newIncome.source
         << " | " << newIncome.amount
         << " EGP | " << newIncome.date << "\n\n";

         saveToFile();

}
/////////////////////////////////////////////////////////////////////////////////////////////
void updateIncome()
{
    if (incomeCount == 0)
    {
        cout << "\nNo incomes to update. Please add some first.\n\n";
        return;
    }

    // Show current list so user can see IDs easily
    cout << "\nCurrent Incomes:\n";
    viewIncomes(incomes, incomeCount);

    cout << "\n=== Update Income ===\n";

    int idToUpdate;
    cout << "Enter the ID of the income you want to update: ";
    cin >> idToUpdate;

    // Find the income with this ID
    int index = -1;
    for (int i = 0; i < incomeCount; i++)
    {
        if (incomes[i].id == idToUpdate)
        {
            index = i;
            break;
        }
    }

    if (index == -1)
    {
        cout << "Error: No income found with ID " << idToUpdate << "!\n\n";
        return;
    }

    // Show the current record
    cout << "\nCurrent record:\n";
    cout << "ID: " << incomes[index].id << "\n";
    cout << "Source: " << incomes[index].source << "\n";
    cout << "Amount: " << incomes[index].amount << " EGP\n";
    cout << "Date: " << incomes[index].date << "\n\n";

    // Menu for what to update
    cout << "What would you like to update?\n";
    cout << "1. Amount\n";
    cout << "2. Source\n";
    cout << "3. Date\n";
    cout << "4. Cancel (go back)\n";
    cout << "Your choice (1-4): ";

    int choice;
    cin >> choice;


    // Clear leftover newline
    cin.ignore(INT_MAX , '\n');


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
                cin.ignore(INT_MAX , '\n');
            }
            incomes[index].amount = newAmount;
            cout << "Amount updated successfully!\n";
            break;
        }

        case 2: // Update source
        {
            string newSource;
            cout << "New source: ";
            getline(cin, newSource);
            if (!newSource.empty())
            {
                incomes[index].source = newSource;
                cout << "Source updated successfully!\n";
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
            cout << "New date (e.g. 15/01/2026): ";
            getline(cin, newDate);
            if (!newDate.empty())
            {
                incomes[index].date = newDate;
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
    cout << "ID: " << incomes[index].id << "\n";
    cout << "Source: " << incomes[index].source << "\n";
    cout << "Amount: " << incomes[index].amount << " EGP\n";
    cout << "Date: " << incomes[index].date << "\n\n";


     saveToFile();
}
/////////////////////////////////////////////////////////////////////////////////
void deleteIncome()
{
    if (incomeCount == 0)
    {
        cout << "\nNo incomes to delete. The list is empty.\n\n";
        return;
    }

    // Show current list so user can see IDs easily
    cout << "\nCurrent Incomes:\n";
    viewIncomes(incomes, incomeCount);

    cout << "\n=== Delete Income ===\n";

    int idToDelete;
    cout << "Enter the ID of the income you want to delete: ";
    cin >> idToDelete;

    // Find the index of the income with this ID
    int index = -1;
    for (int i = 0; i < incomeCount; i++)
    {
        if (incomes[i].id == idToDelete)
        {
            index = i;
            break;
        }
    }

    if (index == -1)
    {
        cout << "\nError: No income found with ID " << idToDelete << "!\n\n";
        return;
    }

    // Show the record that will be deleted
    cout << "\nYou are about to delete this record:\n";
    cout << "ID: " << incomes[index].id << "\n";
    cout << "Source: " << incomes[index].source << "\n";
    cout << "Amount: " << incomes[index].amount << " EGP\n";
    cout << "Date: " << incomes[index].date << "\n\n";

    // Confirmation
    cout << "Are you sure you want to delete this income? (y/n): ";
    char confirm;
    cin >> confirm;

    if (confirm != 'y' && confirm != 'Y')
    {
        cout << "Deletion cancelled.\n\n";
        return;
    }

    // Shift all elements after index one position left
    for (int i = index; i < incomeCount - 1; i++)
    {
        incomes[i] = incomes[i + 1];
    }

    // Decrease the count
    incomeCount--;

    cout << "\nIncome with ID " << idToDelete << " deleted successfully!\n";
    cout << "Now you have " << incomeCount << " income records.\n\n";


    saveToFile();
}
///////////////////////////////////////////////////////////////////////////////
