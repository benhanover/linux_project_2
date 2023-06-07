#include "./missions.h"

//The child process runs these functions.
//In "runChildProcess" function we redirected standard input to the read end of parent-to-child pipe,
//so "cout" in these functions will print the massages to the "childToParent" pipe,
//then the parent process will read from the pipe and print it to the screen.

void printAirportSchedule(System& airports, vector<string> airportsNames)
{
    vector<string> missing_names;
    bool allInDB = false;
    int airportNamesSize = airportsNames.size();
    allInDB = airports.checkIfAllInDbAndUpdateMissing(missing_names, airportsNames);

   if (!allInDB)
    {
        cout << "Not all ICOA code names inserted exist in current database." << endl;
        cout << "These names doesn't exist in the database:" << endl;
        for (int i = 0; i < missing_names.size(); i++)
            cout << missing_names[i] << ' ';
        cout << endl;
    }

    string curAirportName;
    
    for(int i = 0; i < airportNamesSize; i++)
    {
        curAirportName = airportsNames[i]; 
        printFullAirportSchedule(curAirportName,airports);
    }
}

void printFullAirportSchedule(string& IcoaCode, System& airports)
{
    bool exist = airports.isAirportExist(IcoaCode);

    if (exist)
    {
        int index = airports.getAirportIndexByName(IcoaCode);
        vector<FlightInfo*> combine;
        vector<SingleAirport*> airportsVector = airports.getAirportsVector();

        combine.reserve(airportsVector[index]->getArivals().size() + airportsVector[index]->getDepartures().size());

        for(auto& flightInfo: airportsVector[index]->getArivals())
            combine.push_back(flightInfo);
            
        for(auto& flightInfo: airportsVector[index]->getDepartures())
            combine.push_back(flightInfo);

        sort(combine.begin(), combine.end(), compare2Flights);

        for (auto& flightInfo: combine)
        {
            if (flightInfo->getArvOrDpt() == 'a') 
                cout << "Flight #" << flightInfo->getCallsign() << " arriving from " << flightInfo->getEstDepartureAirport() << " at " << flightInfo->getLastSeen() << endl;
            else
                cout << "Flight #" << flightInfo->getCallsign() << " departing to " << flightInfo->getEstDepartureAirport() << " at " << flightInfo->getFirstSeen() << endl;
        }
    }
}

int compare2Flights(FlightInfo* f1, FlightInfo* f2)
{
    char f1ArvOrDpt = f1->getArvOrDpt();
    char f2ArvOrDpt = f2->getArvOrDpt();

    if (f1ArvOrDpt == 'a' && f2ArvOrDpt =='a')
        return (stoi(f1->getLastSeen()) < stoi(f2->getLastSeen())); //comparing 2 arrivals

    else if (f1ArvOrDpt == 'd' && f2ArvOrDpt =='d')
        return (stoi(f1->getFirstSeen()) < stoi(f2->getFirstSeen())); //comparing 2 departures
    
    else if (f1ArvOrDpt == 'a' && f2ArvOrDpt =='d')
        return (stoi(f1->getLastSeen()) < stoi(f2->getFirstSeen())); //comparing arrival(f1) and departure(f2)   
    
    else 
        return (stoi(f1->getFirstSeen()) < stoi(f2->getLastSeen())); //comparing departure(f1) and arrival(f2)
}

