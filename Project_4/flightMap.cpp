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
void FlightMapClass::ReadCities(ifstream &file) {
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
void FlightMapClass::BuildMap(ifstream &file) {
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
        flightMap[ReturnCityIndex(origin)].push_back(flight);   //  Find the origin city and push back the flight
        visited.push_back(false);
    }

    for (int i = 0; i < numCities; i++) {                       // Sort the flight map
        flightMap[i].sort();
    }
}

/*
Similar to the overloaded operator membner function, this displays the flights in table format
*/ 

void FlightMapClass::DisplayMap() {
    cout << left << setw(35) << "Origin" << setw(15) << "Destination" << setw(8) << "Flight" << "Price" <<'\n';
    cout << "===============================================================\n";

    for (int i = 0; i < numCities; i++) {                 // Iterate over the cities
        string origin = "From " + cities[i] + " to: ";    // Create a string with origin city

        if (!flightMap[i].empty()) {                      // If empty print out the origin and set spacing for destination flight
            cout << left << setw(35) << origin;
        } else {
            cout << origin << "\n";                            // If not, do newline character
        }

        bool firstFlightPrinted = false;                    // If first flight is printed
        for (const auto &flight : flightMap[i]) {           // Iterate over the flights in each flightMap index
            if (!firstFlightPrinted) {                      // If first flight hasn't been printed then print out the first flight with the spacing 
                cout << left << flight;   
                firstFlightPrinted = true;
            } else {
               cout << setw(35) << "" << flight;              // Then space it out differently with the second line and so on
            }
        }
    }
}

// A linear seearch function to find the index of a city
int FlightMapClass::ReturnCityIndex(const string city) const {
    for (int i = 0; i < numCities; i++) {
        if (city == cities.at(i)) {
            return i;
        }
    }
    return -1;
}

// Bool function to check if a city passed into the function is in the cities vector
bool FlightMapClass::CheckCity(string cityName) const {
    for (int i = 0; i < numCities; i++) {
        if (cityName == cities.at(i)) {             // If the city is found in the cities array 
            return true;                            // Return true
        }
    }
    return false;                                   // Otherwise return false
}

// A void function to display all the cities in the cities array
void FlightMapClass::DisplayAllCities() const {
    for (int i = 0; i < numCities; i++) {
        cout << cities.at(i) << "\n";
    }
}

// A void function that sets a city to visited in the bool visited array
void FlightMapClass::MarkVisited(int city) {
    visited.at(city) = true;                    // Set corresponding city index to true
}

// A void function that sets the whole visited array to false
void FlightMapClass::UnvisitAll() {             
    for (int i = 0; i < numCities; i++) {
        visited.at(i) = false;                  // Loop through each index and set it to false
    }
}

// Bool to check if a city has been visited
bool FlightMapClass::IsVisited(int city) const {
    if (visited.at(city)) {                         // If city has been visited
        return true;                                // return true
    }
    return false;                                   // Otherwise return false
}

/*
A bool function that gets the next next unvisited city. Iterates through a list of flights
originating from the specified city and checks if there is any destination that has not been visited.
If next city is found, return true, if not, return false
*/
bool FlightMapClass::GetNextCity(string fromCity, string &nextCity) {
    int cityIndex = ReturnCityIndex(fromCity);
    if (cityIndex == -1) {
        return false;                           // If from city not found, return false                             
    }           

    for (const auto &flight : flightMap[cityIndex]) {               // Iterate throough cities and find next adjacent flight
        int nextCityIndex = ReturnCityIndex(flight.destination);
        if (nextCityIndex != -1 && !IsVisited(nextCityIndex)) {
            nextCity = flight.destination;
            return true;
        }
    }
    return false;                                                   // If not found, return false
}

// Get the city name of a city at a index
string FlightMapClass::GetCityName(int cityNumber) const {
    return cities.at(cityNumber);
}

/*
The FindPath function finds a path from an origin city to a destination city using depth
first search approach. It uses a stack to keep track of the cities visited during the 
search and ensures that each city is visited only once. If path is found, prints flight iternary
cost of the flights. If no path is found, print no path between specified cities
*/
void FlightMapClass::FindPath(string originCity, string destinationCity) {
    stack<string> stack;                                    // Keep track of cities visited
    string top, next;                                       // Store current current city and next city
    bool found = false;                                     // Bool variable to determine if next city is found
    int origin = ReturnCityIndex(originCity);               // Get index of origin city
    int destination = ReturnCityIndex(destinationCity);     // Get index of destination city

    // Check if the origin city is not found
    if (origin == -1) {
        cout << "Sorry, BlueSky does not serve " << originCity << ".";
        return;                                                         // Jump out of function
    }
    if (destination == -1) {
        cout << "Sorry, BlueSky does not serve " << destinationCity << ".";
        return;
    }

    UnvisitAll();                                       // Set visited all to false

    stack.push(originCity);                             // Push origin city onto stack
    MarkVisited(origin);                                // Mark visited the origin
    top = stack.top();                                  // Set top of stack to origin city

    // Loop until stack is empty or destination city is found
    while (!stack.empty() && top != destinationCity) {  
        found = GetNextCity(top, next);     // Find next adjacent city
        if (!found) {                       // If no next city is found, pop the current city from the stack
            stack.pop();                    
        } else {                                    // If next city is found, then push the next city onto the stack
            stack.push(next);
            int nextNum = ReturnCityIndex(next);    // Get the index of the next city
            MarkVisited(nextNum);                   // Mark visited the next next
        }
        if (!stack.empty()) {                       // Update the top of the stack
            top = stack.top();
        }
    }

    // Print path not found if the stack is empty
    if (stack.empty()) {
        cout << "Request is to fly from " << originCity << " to " << destinationCity << "\n";
        cout << "Sorry, BlueSky airline does not fly from " << originCity << " to " << destinationCity << ".\n\n";
        return;
    }
    
    std::stack<string> reverseStack;    // Store path in reverse order
    while (!stack.empty()) {            // Psuh the stack onto the reverse stack
        reverseStack.push(stack.top());
        stack.pop();
    }

    cout << "Request is to fly from " << originCity << " to " << destinationCity << "\n";
    cout << "BlueSky airline serves between these two cities.\n";
    cout << "The flight itinerary is: \n";

    // Print the header
    cout << left << setw(10) << "Flight#" 
    << setw(15) << "From" << setw(15) 
    << "To" << setw(15) << "Cost" << "\n";

    int costTotal = 0;                                  // Total the cost of the path
    originCity = reverseStack.top();                    // Set origin city to top of the stack
    reverseStack.pop();                                 // Pop the revserse stack
    
    while (!reverseStack.empty()) {                     // Loop until reverse stack is empty
        origin = ReturnCityIndex(originCity);           // Get index of origin city
        next = reverseStack.top();                      // Get next city from top of reverse stack
        for (const auto &flight : flightMap[origin]) {  // Iterate over flights from origin
            if (next == flight.destination) {           // If next city is destination
                cout << left << setw(10) << flight.flightNum    // Print out the flight details
                << setw(15) << originCity << setw(15) << next 
                << "$" << flight.price << "\n";
                costTotal += flight.price;                      // Add to total cost
            }
        }
        originCity = next;                                      // Update origin city to next city
        reverseStack.pop();                                     // Pop reverseStack
    }
    cout << setw(33) << " " << setw(7) << "Total:" << "$" << costTotal; // Print the total cost of flights
    cout << "\n\n";
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