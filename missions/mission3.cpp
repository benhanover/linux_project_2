#include "./missions.h"

void printAllAircraftsFlights(System& airports)
{
    vector<string> paths;
    paths.reserve(10);
    vector<string> wantedCodes;
    wantedCodes.reserve(20);
    vector<string> missing_names;
    missing_names.reserve(20);
    int numOfCodes;
   
    getInputFromUser(wantedCodes,"Please enter icao24 codes of aircrafts, in order to see their schedule.");

    bool allInDB = false;
    allInDB = checkIfAllAircraftsInDB(airports,missing_names,wantedCodes);
    
    if (!allInDB)
        cout << "Not all aircrafts in database. Printing only those that exist." << endl;
    
    string curAircraft;

    numOfCodes = wantedCodes.size();
    for(int i = 0; i < numOfCodes; i++)
    {
       curAircraft = wantedCodes[i];
  
        if (find(missing_names.begin(), missing_names.end(), curAircraft) != missing_names.end())
            continue;      
       else 
        printSingleAircraftFlights(curAircraft,airports);
    }

}

bool checkIfAllAircraftsInDB(System& airports, vector<string>& missing_names, vector<string> codesRecievedVec)
{
    int numOfCodesRecieved = codesRecievedVec.size();

    for (int i = 0; i < numOfCodesRecieved; i++)
    {   
        string aircraft = codesRecievedVec[i];
        bool existInDB = airports.isAircraftInDB(aircraft);
        if(!existInDB)
            missing_names.push_back(aircraft);
    }

    if (missing_names.empty())
        return true; //no missing names, all arguments in DB
    else 
        return false;

}



void printSingleAircraftFlights(string& icao24, System& airports)
{
    string aircraftName;
    vector<SingleAirport*> airportsVector = airports.getAirportsVector();

    cout << "Printing schedule for " << icao24 << ":" << endl;

    for(auto& airport: airportsVector)
    {
        for (auto& flightInfo: airport->getArivals())
        {
            if(flightInfo->getAircraftName() == icao24)
            {
                cout << icao24 << " departed from  " << flightInfo->getEstDepartureAirport() << " at " << flightInfo->getFirstSeen() <<  " arrived in " 
                  << flightInfo->getEstArrivalAirport() << " at " <<flightInfo->getLastSeen() << endl;
            }
        }
        for (auto& flightInfo: airport->getDepartures())
        {
            if(flightInfo->getAircraftName() == icao24)
            {
                cout << flightInfo->getAircraftName() << " departed from  " << flightInfo->getEstDepartureAirport() << " at " << flightInfo->getFirstSeen() <<  " arrived in " 
                    << flightInfo->getEstArrivalAirport() << " at " <<flightInfo->getLastSeen() << endl;
            }
        }
    }
    cout << endl;
}