// If Late, give pass #, describe reason

// Author: Garrett Johnson
// Project Description: This project is similar to project 1, but will use
// classes instead of structs to read in and handle data from a student roster
// read from a file

#include <iostream>
#include <fstream>
#include "student.h"
#include "roster.h"
using namespace std;

void ProcessStudentID(const Roster &roster);        

int main() {
    string className = "CSCI 3110";                                     
    Roster roster(className);                                           // Create a roster object with the name CSCI 3110

    roster.readStudentRecord("grades.dat");                             // Read a file using the readStudentRecord method from roster.h

    cout << "Here is the information for the " << roster.GetStudentCount() 
    << " students in Class " << className << "\n" << roster << "\n";                         // Display the roster object in grid format

    ProcessStudentID(roster);                                                       // Use function to ask for user 

    return 0;
}

/*
Function to ask user for data to display the information of one student from the roster
Uses a while loop to continually ask for input until a correct student id is entered
Then use that ShowOneStudent method to display the information of that student
*/
void ProcessStudentID(const Roster &roster) {    
    string id;
    cout << "Enter a valid class ID: ";             // Have the user enter in class ID for student
    cin >> id;

    while(!roster.isValid(id)) {                    // While loop to keep the input process on repeat till correct class ID entered
        cout << "\n";
        cout << "Enter a valid class ID: ";
        cin >> id;
    }
    roster.ShowOneStudent(id);
}