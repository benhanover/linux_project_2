#include "./missions.h"
 
 //The child process runs these functions.
 //In "runChildProcess" function we redirected standard input to the read end of parent-to-child pipe,
 //so "cout" in these functions will print the massages to the "childToParent" pipe,
 //then the parent process will read from the pipe and print it to the screen.

void printAirportsArv(System& airports, vector<string> airportsCodeNames)
{
    vector<string> missing_names;
    bool allInDB = false;
    int numOfCodes = airportsCodeNames.size();
    allInDB = airports.checkIfAllInDbAndUpdateMissing(missing_names, airportsCodeNames);
    
    if (!allInDB)
    {
        cout << "Not all ICOA code names inserted exist in current database." << endl; 
        cout << "These names doesn't exist in the database:" << endl;
        for (int i = 0; i < missing_names.size(); i++)
            cout << missing_names[i] << ' ';
        cout << endl;
    }
       
    string curAirportName;
    for(int i = 0; i < numOfCodes; i++)
    {
        curAirportName = airportsCodeNames[i]; 
        printSingleAirportArv(airports, curAirportName);
    }
 
}


void printSingleAirportArv(System& airports,string& IcoaCode)
{
    bool exist = airports.isAirportExist(IcoaCode);

    if (exist)
    {
        int airportIndex = airports.getAirportIndexByName(IcoaCode);
        vector<SingleAirport*> airportsVector = airports.getAirportsVector();
        cout << "Printing schedule for " << IcoaCode << ":" << endl;
        for (auto& flightInfo: airportsVector[airportIndex]->getArivals())
        {
            cout << "Flight #" << flightInfo->getCallsign() << " arriving from " << flightInfo->getEstDepartureAirport() << ", tookoff at " << flightInfo->getFirstSeen() <<  " landed at " << flightInfo->getLastSeen() << endl;
        }
        cout << "\n\n";
    }
}



