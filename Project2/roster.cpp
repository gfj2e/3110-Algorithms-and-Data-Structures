#include "roster.h"

/*
Constructor that gives the roster object a name with the courseName parameter
and initalizes the studentNum variable to 0
*/
Roster::Roster(string courseName) {
    this->courseName = courseName;      // Uses this pointer to assign objects courseName with the parameter
    studentNum = 0;
}

/*
A file reading method that takes in a filename string and reads student objects 
into the Roster array of students 
*/
void Roster::readStudentRecord(string filename) {
    ifstream file (filename);

    if (!file) {
        cerr << "File opening failed!\n";
        exit(EXIT_FAILURE);
    }

    string line;
    getline(file, line);                        // Discard the header line
    getline(file, line);
    while (getline(file, line)) {
        istringstream iss(line);                // iss stream object to read in student information into student array
        iss >> students[studentNum];
        students[studentNum].ComputeTotal();    // Compute the total score 
        students[studentNum].ComputeGrade();    // and grade for that student object
        studentNum++;
    }
    file.close();
}

// A int getter that will return the number of students in a roster
int Roster::GetStudentCount() const { 
    return studentNum; 
}

/*
A bool function that will return true if a student id is found within a student object
and return false if otherwise
*/
bool Roster::isValid(string id) const {
    for (int student = 0; student < studentNum; student++) {    
        if (id == students[student].getID()) {
            return true;
        }
    }
    return false;
}

/*
A void function that will display the info of a student found within the student
array in the Roster object
*/
void Roster::ShowOneStudent(string id) const {
    for (int student = 0; student < studentNum; student++) {        // If student is found within the array
        if (id == students[student].getID()) {                     
            students[student].DisplayInfo();                        // Display the students info
            return;                                                 // Return when that student is found
        }
    }
}

/*
An ostream overloaded operator that will display the contents of the roster in grid format with headers
for the scores, will return os object reference
*/
ostream & operator << (ostream &os, const Roster &oneClass) {
    cout << right << setw(12) << "Class ID" << setw(13) << "Name" << setw(8)
    << "CLA" << setw(8) << "OLA" << setw(8) << "Quiz" << setw(11) << "Homework" 
    << setw(6) << "Exam" << setw(9) << "Bonus" << "\n\n";
    for (int student = 0; student < oneClass.studentNum; student++) {           // Loop to display the student scores
        cout << oneClass.students[student];
    }
    return os;
}