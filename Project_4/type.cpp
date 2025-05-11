#include "type.h"

// Compare the destination with right hand destination
bool flightRec::operator < (const flightRec &rhs) const {
    return destination < rhs.destination;
}

flightRec& flightRec::operator = (const flightRec &rhs) {
    if (this != &rhs) {
        origin = rhs.origin;
        flightNum = rhs.flightNum;
        destination = rhs.destination;
        price = rhs.price;
    }

    return (*this);
}

// Return true if two flights share the same origin and  destination
bool flightRec::operator == (const flightRec &rhs) const {
    if (origin == rhs.origin && destination == rhs.destination) {
        return true;
    }
    return false;
}

// Overloaded operator to print out the destination, flight, and price of a flight
ostream& operator << (ostream &os, const flightRec &f) {
    os << setw(15) << f.destination << setw(7) << f.flightNum << " $" << f.price << "\n";
    return os;
}