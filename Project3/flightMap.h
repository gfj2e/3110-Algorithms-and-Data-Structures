#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <string>
#include <sstream>
#include <iomanip>
#include <algorithm>
using namespace std;

#ifndef FLIGHTMAPCLASS_H
#define FLIGHTMAPCLASS_H

#include "type.h"

using namespace std;

class FlightMapClass
{
	public:
		//constructors and destructor
		FlightMapClass();
		FlightMapClass(const FlightMapClass &rhs);
		~FlightMapClass();

		//FlightMapClass operations:
		
		//Read cities from a data file
		//Pre-condition: Input stream is provided
		//Post-condition: Data file is read
		//				  Cities are in ascending order
		void readCities(ifstream &file);

		//Reads flight information and build the adjacency list
		//Pre-condition: list of the flight information is provided
		//Post-condition: Flight map is built
		void readFlightInfo(ifstream &file);
		
		//Displays the flight map in a formatted table
	    // using overloaded << opererator
		//Pre-condition: none
		//Post-condition: Flight map is displayed
		friend ostream &operator<<(ostream &os, const FlightMapClass &map);

	private:
		int returnCityIndex(const string city) const;
		//number of cities
		int numCities;
   		//vector of cities
		vector<string> cities;
       	//flight map
		list<flightRec> *flightMap;
};

#endif
