#include "./missions.h"

void printAllAircraftsFlights(System& airports, vector<string> aircraftsNames)
{
    vector<string> missing_names;
    bool allInDB = false;
    int aircraftsNamesSize = aircraftsNames.size();
    allInDB = checkIfAllAircraftsInDB(airports, missing_names, aircraftsNames);

   if (!allInDB) //This function will print the massages to the "childToParen" pipe and than the parent process will print it to the screen
    {
        cout << "Not all ICOA code names inserted exist in current database." << endl;
        cout << "These names doesn't exist in the database:" << endl;
        for (int i = 0; i < missing_names.size(); i++)
            cout << missing_names[i] << ' ';
        cout << endl;
    }
    
    string curAircraft;
    for(int i = 0; i < aircraftsNamesSize; i++)
    {
       curAircraft = aircraftsNames[i];
  
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
