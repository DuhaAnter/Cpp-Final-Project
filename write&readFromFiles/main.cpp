#include <iostream>
#include <fstream> // read & write  library
using namespace std;

int main()
{
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
    return 0;
}
