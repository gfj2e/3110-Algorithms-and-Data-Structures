// If Late, give pass #, describe reason

// Author: Garrett Johnson
// Project Description: Project 4
#include <assert.h>
#include "flightMap.h"
using namespace std;

int main(void) {

    FlightMapClass flightMap;               // Create a FlightMapClass object

    ifstream fileCities("cities.dat");      // Open the cities.dat and flights.dat files to read into the object

    ifstream fileFlights("flights.dat");

    assert(fileCities);                     // Check that the files are valid
    assert(fileFlights);

    flightMap.ReadCities(fileCities);       // Read the info into the flightMap
    flightMap.BuildMap(fileFlights);

    fileCities.close();
    fileFlights.close();

    ifstream requests("requests.dat");              // Open the requests file
    assert(requests);                               // Check if file is valid 
    string origin, destination;                     // Read the origin and destination 
    while (requests >> origin >> destination) {     // Read in data into FindPath function
        flightMap.FindPath(origin, destination);
    }

    requests.close();
    
    return 0;
}