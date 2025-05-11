#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <string>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <stack>
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
		void ReadCities(ifstream &file);

		//Reads flight information and build the adjacency list
		//Pre-condition: list of the flight information is provided
		//Post-condition: Flight map is built
		void BuildMap(ifstream &file);

		void DisplayMap();
		// Displays the flight map in a formatted table
		// Pre-condition: none
		// Post-condition: Flight map is displayed

		// Check whether a city is in the cities that EastWest airline serves.
		// Pre-condition: cityNumber to be checked is provided
		// Post-condition: return true if the city is in the cities array
		//              otherwise return false
		bool CheckCity(string cityName) const;

		void DisplayAllCities() const;
		// Displays all cities

		void MarkVisited(int city);
 		// Marks a city as visited
		// Pre-condition: city to be marked as visited is provided
		// Post-condition: a city is marked as visited

		void UnvisitAll();
		// Clears marks on all cities
		// Pre-condition: there are > 0 cities in a cities array
		// Post-condition: all cities marked as unvisited

		bool IsVisited(int city) const;
		// Determines whether a city was visited
		// Pre-condition: city is provided
		// Post-condition: return true if city has been visited
		//              otherwise return false

		bool GetNextCity(string fromCity, string &nextCity);
		// Determines the next unvisited city, if any,
		// that is adjacent to a given city.
		// success indicates whether an unvisited adjacent city was found
		// Pre-condition: topCity and nextCity provided
		// Post-condition: return true if an unvisited adjacent city was found
		//              otherwise return false

		string GetCityName(int cityNumber) const;
		// returns the name of a city given its corresponding index
		// Pre-condition: number of a city is provided
		// Post-condition: returns the city's name

		void FindPath(string originCity, string destinationCity);
		// Determines whether a sequence of flights between two cities exists.
		// Pre-condition: originCity and destinationCity are the origin and destination city, respectively
		// Post-condition: returns true if a sequence of flights exists
		//              from origin to destination; otherwise return false.
		//              Cities visited during the search are marked as visited
		//              in the flight map.

		int ReturnCityIndex(const string city) const;
		//Displays the flight map in a formatted table
	    // using overloaded << opererator
		//Pre-condition: none
		//Post-condition: Flight map is displayed
		
		friend ostream &operator<<(ostream &os, const FlightMapClass &map);

	private:
		//number of cities
		int numCities;
   		//vector of cities
		vector<string> cities;
       	//flight map
		list<flightRec> *flightMap;

		vector<bool> visited;	// newly added for this part: to check if a city has been visited before
};

#endif
