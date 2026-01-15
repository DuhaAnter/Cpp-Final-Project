#include <iostream>
#include <fstream> // read & write  library
using namespace std;

int main()
{
    /*


    // create the ofstream object

    ofstream outFile;

    // open file.txt using the append flag (ofstream::app)so content will be appended to the
    // end of any existing content in file.txt
    // if i did not use it . every time will overwrite everything in the file

    outFile.open("file.txt", ofstream::app); // if the file doesn't exist . it will be created.

    // check if the file failed to open

    if (outFile.fail())
    {
        cout << "Error opening file." << endl;
        return 1; // program failed
    }

    // we use the stream insertion operator to write to the file, as we do
    // when we use cout

    outFile << "I hope u find peace" << endl;


    double x = 4.5;
    int y = 10;
    string z = "soon";

    // we can output the content of variables into the file we opened
    outFile << x << endl;
    outFile << y << endl;
    outFile << z << endl;

    // close the file, as a best practice when we are done with it (freeing memory)
    outFile.close();


    */
////////////////////////////////////READ FROM FILE/////////////////////////////////////////////////
// NOTE : u have to  know the order of the variables in the file so u can read them using the correct data types otherwise it won't work.

    // create an ifstream object
    ifstream readFile;


    readFile.open("file.txt");

    // if file.txt fails to open, fail() will return true, and we'll exit
    // gracefully by telling the user what went wrong and exiting with status 1
    // which is a signal to the shell that something wen't wrong in the execution
    // of our program
    if (readFile.fail())
    {
        cout << "Error opening file." << endl;
        return 1; //terminate program
    }



    string line;
    // If the file contents are:
    // This is a string.
    //
    // Then if we use the stream extraction operator (>>), only the keyword "This"
    // will be stored into line... because the operator will stop at the first
    // whitespace character.  We can use getline() to read in the entire line
    // including spaces, because it will stop at the first newline in the file.
    //
    getline(readFile, line);
    cout << line << endl;


    double x=0;

    readFile >> x;

    cout<<x<<endl;


     // variable to store number in the file
    int number = 0;

    // read in the number
    readFile >> number;
    //check if it's read
    if (readFile.fail())
    {
        cout << "Error file format incorrect." << endl;
        return 1;
    }

    cout<<number;


    return 0;
}
