#include "flightMap.h"

// Initialize numCities to 0 and set dynamically allocated flightMap to nullptr 
FlightMapClass::FlightMapClass() : numCities(0), flightMap(nullptr) {}

/*
Copy Constructor for the FlightMapClass that copies over data from one FlightMapClass object
to a new one that is initialized. Will copy numCities and cities vector and then allocate 
a new list and copy it from the old one to the new one.
*/
FlightMapClass::FlightMapClass(const FlightMapClass &rhs) {
    numCities = rhs.numCities;
    cities = rhs.cities;
    flightMap = new list<flightRec>[numCities];
    for (int i = 0; i < numCities; i++) {                   // Iterate over the flightMap and copy the list to the new object
        flightMap[i] = rhs.flightMap[i];
    }
}

/*
A function to read over the cities.dat file then create create the vector of cities
with that data and then sort it alphabetically with the sort function using begin()
and end(), then dynamically allocate the flightMap with the numCities incremented
*/
void FlightMapClass::readCities(ifstream &file) {
    string city;
    file >> numCities;                          // Read the numCities from file stream
    while (file >> city) {
        cities.push_back(city);                 // Read cities and then push back onto vector
    }
    sort(cities.begin(), cities.end());         // Sort alphabetically
    flightMap = new list<flightRec>[numCities]; // Dynamically allocate the list 
}

/*
A file reading function for reading the flights into the flightMap list and then
sorting them into alphabetical order to match the cities vector. Create the flightRec
struct object and then read information from the file with the iss stream. Then find 
the matching city from the vector and push back the flight. After list is created, then 
sort alphabetically with the .sort() method with < overloaded operator
*/
void FlightMapClass::readFlightInfo(ifstream &file) {
    flightRec flight;                                           // Create flight record struct, initialize its variables
    string str, origin, destination;
    int flightNum, price;
    while (getline(file, str)) {                                // Read the file into the flight record structs
        istringstream iss(str);
        iss >> flightNum >> origin >> destination >> price;
        flight.flightNum = flightNum;
        flight.origin = origin;
        flight.destination = destination;
        flight.price = price;
        flightMap[returnCityIndex(origin)].push_back(flight);   //  Find the origin city and push back the flight
    }

    for (int i = 0; i < numCities; i++) {                       // Sort the flight map
        flightMap[i].sort();
    }
}

// A linear seearch function to find the index of a city
int FlightMapClass::returnCityIndex(const string city) const {
    for (int i = 0; i < numCities; i++) {
        if (city == cities.at(i)) {
            return i;
        }
    }
    return -1;
}

/*
An << overloaded operator function that will format the table to print out the flights. Sets the 
header for the origin, destination, flight, and price. The function then iterates over the cities
and then prints out all the flights contained in each list section a city points to for its 
destination. 
*/
ostream &operator<<(ostream &os, const FlightMapClass &map) {
    os << left << setw(35) << "Origin" << setw(15) << "Destination" << setw(8) << "Flight" << "Price" <<'\n';
    os << "===============================================================\n";

    for (int i = 0; i < map.numCities; i++) {                 // Iterate over the cities
        string origin = "From " + map.cities[i] + " to: ";    // Create a string with origin city

        if (!map.flightMap[i].empty()) {                      // If empty print out the origin and set spacing for destination flight
            os << left << setw(35) << origin;
        } else {
            os << origin << "\n";                            // If not, do newline character
        }

        bool firstFlightPrinted = false;                    // If first flight is printed
        for (const auto &flight : map.flightMap[i]) {       // Iterate over the flights in each flightMap index
            if (!firstFlightPrinted) {                      // If first flight hasn't been printed then print out the first flight with the spacing 
                os << left << flight;   
                firstFlightPrinted = true;
            } else {
               os << setw(35) << "" << flight;              // Then space it out differently with the second line and so on
            }
        }
    }

    return os;
}

// Deallocates the flightMap list
FlightMapClass::~FlightMapClass() {
    delete[] flightMap;
}