#include <iostream>
#include <fstream>
//C++ has a tool called string stream that treats a string like a mini-file. You can "read" from it just like cin.
#include<sstream>
using namespace std;
//A way to organize data (struct = the blueprint)
struct Income
{
    int id;
    double amount;
    string date;
    string source;

};

int main()
{
    Income inc1;
    inc1.amount=14000;
    inc1.date ="15jan2026";
    inc1.source="salary";
    inc1.id=2;

    //1.
    ofstream file ;
    //2.
    file.open("income.txt",ofstream::app);
    //3.did it worked?
    if(file.fail())
    {
        cout << "Error opening the file ";
        return 1;
    }

    /*
    //4.if no . write in it
    file << inc1.id << "|" <<inc1.source<<"|"<<inc1.amount<<"|"<<inc1.date<<endl;
    */
    //5.
    file.close();
////////////////////////////////////////////////////read//////////////////////////////

    ifstream readfromFile;

    readfromFile.open("income.txt");
    if(readfromFile.fail())
    {
        cout<<"Error opening the file";
        return 1; // terminate program
    }
    string fileLine;

    getline(readfromFile,fileLine);
    if(readfromFile.fail())
    {
        cout<<"Error Reading from the file";
        return 1;
    }

    /*
    // 1. The string you read from file
    string fileLine = "3|salary|15000|15jan2026";
    */
// 2. Create string stream
    stringstream ss(fileLine);

// 3. Variables to hold each piece
    string idStr, source, amountStr, date;

// 4. Extract pieces using | as delimiter
    getline(ss, idStr, '|');    // Gets "1"
    getline(ss, source, '|');   // Gets "salary"
    getline(ss, amountStr, '|'); // Gets "10000"
    getline(ss, date, '|');     // Gets "15jan2026"

// 5. Convert strings to appropriate types
    int id = stoi(idStr);           // "1" → 1
    double amount = stod(amountStr); // "10000" → 10000.0

// 6. Now store in  struct
    Income income;
    income.id = id;
    income.source = source;
    income.amount = amount;
    income.date = date;

    cout<<income.source;
    return 0;
}
