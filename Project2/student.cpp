#include "student.h"

/*
Default constructor that will initialize various Student object variables to placeholder values
*/
Student::Student() {
    id = " ";                       // Empty string
    name = " ";                     // Empty string
    score[CATEGORY_NUM] = {0};      // Initialize the array to all 0s
    total = 0;                      
    letterGrade = 'A';              // Default grade is 0
}

/*
Copy Constructor that will copy the contents of a previous object into a brand new
object that was created previously. Uses the enum for loop demonstrated
during lecture to assign the scores from previous object to the new object
*/
Student::Student(const Student &s) {
    id = s.id;
    name = s.name;
    ScoreType scoreIdx;
    for (scoreIdx = CLA; scoreIdx <= BONUS; scoreIdx = static_cast<ScoreType>(scoreIdx + 1)) {
        score[scoreIdx] = s.score[scoreIdx];
    }
    total = s.total;
    letterGrade = s.letterGrade;
}

/*
Overloaded assignment operator that will assign the contents of one previously created object to the destination
object that was also previously created, different from the constructor in that a new object
is not being created
*/
Student& Student::operator = (const Student &s) { 
    id = s.id;      // Assign values from right hand side to the destination object
    name = s.name;
    ScoreType scoreIdx;
    for (scoreIdx = CLA; scoreIdx <= BONUS; scoreIdx = static_cast<ScoreType>(scoreIdx + 1)) {
        score[scoreIdx] = s.score[scoreIdx];
    }
    total = s.total;
    letterGrade = s.letterGrade;
    return *this;                   // Return a this pointer to that object 
}

// This string getter function returns the student id of a student object 
string Student::getID() const {
    return id; 
}

/* 
This setter sets the id of a student using this pointer that points to the id being set
and sets it to the string parameter being passed into the function
*/
void Student::setID(string id) {
    this->id = id;
}

/*
This function is uses a enum for loop to iterate through a students grade 
and uses that grade to add to a private member variable called total
Total is the sum of all scores
*/
void Student::ComputeTotal() {
    ScoreType scoreIdx;
    for (scoreIdx = CLA; scoreIdx <= BONUS; scoreIdx = static_cast<ScoreType>(scoreIdx + 1)) {
        total += score[scoreIdx];
    }
}

// A int getter that returns the total score of a student, used in Roster readStudentRecord
int Student::GetTotal() const { 
    return total;
}

/*
A method to compute the grades of a student with a total to a letter grade 
Uses a if else chain to determine the letter grade, used in
readStudentRecord
*/
void Student::ComputeGrade() {
    if (total >= 90) {
        letterGrade = letterGrade;
    } else if (total >= 80) {
        letterGrade = 'B';
    } else if (total >= 70) {
        letterGrade = 'C';
    } else if (total >= 60) {
        letterGrade = 'D';
    } else {
        letterGrade = 'F';
    }
}

// A char getter function that returns a student's letter grade
char Student::GetGrade() const { 
    return letterGrade; 
}

/*
A setter that will change a students score, takes a ScoreType enum name
and a score value to change the students score to
*/
void Student::changeScore( ScoreType scoreName, int scoreValue) { 
    score[scoreName] = scoreValue;     
}

/*
A int getter function that will return a specific score determined by the 
enum value that was passed by the parameter 
*/
int Student::getScore( ScoreType scoreName) const { 
    return score[scoreName];     
}

/*
This method will display the information of a student object such as name,
scores, tota, and the letter grade
*/
void Student::DisplayInfo() const {
    cout << "Name : " << name << "\n"               // Name
    << "CLA : " << score[CLA] << "\n"               // CLA Score
    << "OLA : " << score[OLA] << "\n"               // OLA Score
    << "Quiz : " << score[QUIZ] << "\n"             // Quiz Score
    << "Exam : " << score[EXAM] << "\n"             // Exam Score
    << "Bonus : " << score[BONUS] << "\n"           // Bonus Score
    << "-------------------------------\n"         
    << "Total Score : " << total << "\n"            // Total score
    << "Final Grade : " << letterGrade << "\n";     // Final grade score
}

/*
Overload ostream operator to display the information of a student 
one line, excludes the grade and total variables.
*/
ostream & operator << (ostream &myout, const Student &s) {
    cout << right << setw(10) << s.id << setw(15) << s.name << setw(8);
    for (int score = 0; score < Student::CATEGORY_NUM; score++) {           // Uses static constant CATEGORY_NUM
        cout << s.score[score] << setw(8);
    }
    cout << "\n";
    return myout;
}

/*
Overloaded istream operator to read data into a student object from a file
Reads in information such as id, name, and scores
*/
istream & operator >> (istream &myin, Student &s) {
    myin >> s.id >> s.name;
    for (int score = 0; score < Student::CATEGORY_NUM; score++) {           // Uses static constant CATEGORY_NUM
        myin >> s.score[score];
    }
    return myin;
}