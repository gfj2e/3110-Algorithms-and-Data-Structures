

#ifndef Type_H
#define Type_H
#include <iostream>
#include <iomanip>
using namespace std;

//define struct flightRec
struct flightRec {
	string origin;
	int flightNum;
	string destination;
	int price;
	
	bool operator < (const flightRec &rhs) const;
	//overloaded < operator for flightRec
	//this function compares the destinations between two flightRec

	flightRec & operator = (const flightRec &rhs);
	// Overloaded = operator for flightRec
	// This function assigns a flightRec object to another flightRec object
	
	bool operator == (const flightRec &rhs) const;
	//overloaded == operator for flightRec
	//this function compares the origins and destinations between two flightRec
	
	friend ostream& operator << (ostream &os, const flightRec &f);
	//overloaded output operator for flightRec struct
};

#endif