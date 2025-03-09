/* 
 PROGRAMMER: Garrett Johnson
 Date: 01/24/2025
 Program Description: This program will read a data file containing students and their
 various information such as ID, name, and grades. The data will be stored into a array
 of structs called StudentType, with variable name roster and will use different functions
 that will display data of the students and sort      
*/ 

#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <cassert>
#include <algorithm>
#include "type.h"
using namespace std;

const int MAX_NUM = 100;                                                            // Maximum number of students that can be in an array

int ReadFile(ifstream &file, StudentType roster[]);                                 // This is for reading the file into the array and returning the number of students in the array
void PrintStudentRecords(const StudentType roster[], int maxIndex);                 // This takes the students from the roster and prints out their information in graph form
void PrintStudentInfo(const StudentType roster[], int maxIndex);                    // Asks the user for specific student record and then prints out that student's information
void Sort(StudentType roster[], int maxIndex);                                      // This uses selection sorting to sort the students in alphabetical order
int SearchStudentIndex(const StudentType roster[], int maxIndex, const string ID);  // Returns the index of a valid student entered, return -1 if not valid


int main() {
    StudentType roster[MAX_NUM] {};             // Define a StudentType array to hold information about them
    ifstream file;                              // Create file object

    file.open("grades.dat");                    // Open the file for reading

    assert(file);                               // Use C assert for checking if file was opened

    int maxIndex = ReadFile(file, roster);      // Read the file and return the maximum index in the array

    PrintStudentRecords(roster, maxIndex);      // Print the records of the students in chart format

    PrintStudentInfo(roster, maxIndex);         // Find a student by asking user for studentID

    Sort(roster, maxIndex);                     // Selection sorting for organizing the chart in alphabetical order

    PrintStudentRecords(roster, maxIndex);      // Print the sorted roster
    
    file.close();                               // Close the file

    return 0;                                   // Terminate program
}

/*
Description: A function that takes a file object and reads the student information
into the array. It is an int function return so the max size of the 
array can be indexed into a variable in main. Uses iss stream to read in each line
into respective StudentType members
Pre: File must be opened correctly for usage
Post: Roster array will have students stored and the max size of the array will be returned
in a variable in main
*/
int ReadFile(ifstream &file, StudentType roster[]) {
    int i;                 // index variable
    string line;    
    getline(file, line);  // Skip header
    while (i < MAX_NUM && getline(file, line)) {                        // This loop checks to make sure the max number of students is not exceeded when reading into the array
        StudentType student;                                            // Create temp student struct to store information into it
        istringstream iss(line);
        iss >> student.studentID >> student.studentName >>              // iss stream reads each part of a string into the StudentType member variables
        student.claScore >> student.olaScore >> student.quizScore >>
        student.homeworkScore >> student.examScore >> student.bonusPoints;
        roster[i] = student;
        i++;
    }

    return i;                                                           // Return size of array
}

/*
Description: A function that takes the roster array and size and prints out each student
in a chart format. Uses setw for spacing and loops through each StudentType struct and
prints out their member variables.
Pre: File needs to be opened correctly and size of the array indexed
Post: The StudentType array will have its contents printed out in chart format
*/
void PrintStudentRecords(const StudentType roster[], int maxIndex) {
    cout << "Here is the information of the " << maxIndex << " students:\n\n";              // Formatting the header part
    cout << left << setw(10) << "ClassID" << setw(15) << "Name" << setw(8) << "CLA"
    << setw(8) << "OLA" << setw(8) << "Quiz" << setw(13) << "Homework" << setw(8) 
    << "Exam" << setw(8) << "Bonus" << "\n\n";

    for (int i = 0; i < maxIndex; i++) {                                                    // Loop that loops through each StudentType struct and prints out its members
        cout << left << setw(10) << roster[i].studentID
        << setw(15) << roster[i].studentName << setw(8) << roster[i].claScore
        << setw(8) << roster[i].olaScore
        << setw(8) << roster[i].quizScore
        << setw(13) << roster[i].homeworkScore
        << setw(8) << roster[i].examScore
        << setw(8) << roster[i].bonusPoints
        << "\n";
    }
    cout << "\n\n";
}

/*
Description: This function will search for a specific student in the roster array and 
print out its respective information entered in by the user. It uses SearchStudentIndex function to find a 
valid student index and returns that index for printing, if not found then continually
asks for a valid class ID.
Pre: Roster must be read in correcly and size returned
Post: Information of that student will be printed
*/
void PrintStudentInfo(const StudentType roster[], int maxIndex) {
    int i;                                                                          // Index value that will be used in the linear search function SearchStudentIndex
    string classID;                         
    cout << "Enter a valid Class ID: ";                                             // Have user enter class ID
    cin >> classID;
    cout << "\n";

    while ((i = SearchStudentIndex(roster, maxIndex, classID)) == -1) {             // If value returned by SearchStudentIndex is -1 then repeat the input
        cout << "Enter a valid Class ID: ";
        cin >> classID;
        cout << "\n";
    }
    
    cout << "Information for student with ID: " << roster[i].studentID << "\n";     // The value returned index returned by SearchStudentIndex is used to print out the member variables
    cout << "Name: " << roster[i].studentName << "\n";
    cout << "CLA: " << roster[i].claScore << "\n";
    cout << "OLA: " << roster[i].olaScore << "\n";
    cout << "Quiz: " << roster[i].quizScore << "\n";
    cout << "Homework: " << roster[i].homeworkScore << "\n";
    cout << "Exam: " << roster[i].examScore << "\n";
    cout << "Bonus: " << roster[i].bonusPoints << "\n\n";
}

/*
Description: This is a selection sort function for sorting the roster array in alphabetical order
Pre: Roster must be read into as well as the size of it returned
Post: The array will now be returned in alphabetical order
*/
void Sort(StudentType roster[], int maxIndex) {
    int minIndex;           // Index of the minimum value in the unsorted array 
    string minValue;        // The string with lowest value

    cout << "Sorting student records by name. . .\n\n";

    // Outer loop to iterate over each element in the array
    for (int start = 0; start < (maxIndex - 1); start++) {
        minIndex = start;                                   // Minimum value at start of array
        minValue = roster[start].studentName;               // Initialize minValue with current starting element's name
        // Inner loop to find the minimumn element in the unsorted part of the array
        for (int i = (start + 1); i < maxIndex; i++) {
            if (roster[i].studentName < minValue) {
                minValue = roster[i].studentName;       // minValue now has new minimum value
                minIndex = i;                           // Update minIndex with index of minimum value
            }
        }
        swap(roster[minIndex], roster[start]);          // Swap found minimum element with the first element of the array 
    }
}

/*
Description: SearchStudentIndex function will search for a valid string ID in a 
StudentType array and return the index of that student with the valid string ID. Will return
-1 if the string ID was not found in the StudentType array
Pre: Roster has to be read into, a size of the array needs to be returned, and a string ID passed into the function
Post: Index of the student in the roster will be returned if found, return -1 if not found
*/
int SearchStudentIndex(const StudentType roster[], int maxIndex, const string ID) {
    for (int i = 0; i < maxIndex; i++) {
        if (roster[i].studentID == ID) {    // If ID passed from function equals to ID of a studentID in the roster array, return that index
            return i;
        }
    }
    return -1;                              // Return -1 if not found
}
