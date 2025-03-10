// If Late, give pass #, describe reason
// Use pass #1, I made a mistake in my code and forgot the overloaded assignment operator for
// the flightRec struct. I also forgot my project description. I added those

// Author: Garrett Johnson
// Project Description: Project 3 is about reading in cities and flights from a file and building a
// a flight map in table form. Precursor to project 4

#include <assert.h>
#include "flightMap.h"
#include "type.h"
using namespace std;

int main(void) {

    FlightMapClass flightMap;               // Create a FlightMapClass object

    ifstream fileCities("cities.dat");      // Open the cities.dat and flights.dat files to read into the object

    ifstream fileFlights("flights.dat");

    assert(fileCities);                     // Check that the files are valid
    assert(fileFlights);

    flightMap.readCities(fileCities);       // Read the info into the flightMap
    flightMap.readFlightInfo(fileFlights);

    fileCities.close();
    fileFlights.close();


    cout << flightMap;                      // Print out the flightMap table 
    
    return 0;
}