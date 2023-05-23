#include "./missions.h"

void printAirportsArv(System& airports, vector<string> paths)
{
    vector<string> airportsCodeNames;
    getInputFromUser(airportsCodeNames, "Insert airports ICOA code names to print arrivals:");
    vector<string> missing_names;

    bool allInDB = false;
    int numOfCodes = airportsCodeNames.size();
    allInDB = airports.checkIfAllInDbAndUpdateMissing(missing_names, airportsCodeNames);
    
    if (!allInDB)
         notAllInDB(missing_names, airports);
    else
         cout << "All in DB. Printing as asked." << endl;
    
    
    string curAirportName;
    
    for(int i = 0; i < numOfCodes; i++)
    {
         curAirportName = airportsCodeNames[i]; 
         printSingleAirportArv(airports,curAirportName);
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



