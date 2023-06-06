#include "./missions.h"

void printAirportsArv(System& airports, vector<string> airportsCodeNames)
{
    vector<string> missing_names;
    bool allInDB = false;
    int numOfCodes = airportsCodeNames.size();
    allInDB = airports.checkIfAllInDbAndUpdateMissing(missing_names, airportsCodeNames);
    
    if (!allInDB)
    {
        cout << "Not all ICOA code names inserted exist in current database." << endl; //!!!!return bullian to the parent and make a switch case that print a note to the screen according to the problem
        cout << "These names doesn't exist in the database:" << endl;
        for (int i = 0; i < missing_names.size(); i++)
            cout << missing_names[i] << ' ';
        cout << endl;
        //return "";
    }
       
    string curAirportName;
    string output;
    for(int i = 0; i < numOfCodes; i++)
    {
        curAirportName = airportsCodeNames[i]; 
        //output += printSingleAirportArv(airports, curAirportName);
        printSingleAirportArv(airports, curAirportName);
    }
    
    //cout << output;
}


void printSingleAirportArv(System& airports,string& IcoaCode)
{
    bool exist = airports.isAirportExist(IcoaCode);

    if (exist)
    {
        int airportIndex = airports.getAirportIndexByName(IcoaCode);
        vector<SingleAirport*> airportsVector = airports.getAirportsVector();
        //stringstream output;
        cout << "Printing schedule for " << IcoaCode << ":" << endl;
        for (auto& flightInfo: airportsVector[airportIndex]->getArivals())
        {
            cout << "Flight #" << flightInfo->getCallsign() << " arriving from " << flightInfo->getEstDepartureAirport() << ", tookoff at " << flightInfo->getFirstSeen() <<  " landed at " << flightInfo->getLastSeen() << endl;
        }
        cout << "\n\n";
        //return output.str();
    }
    //return ""; // Return an empty string if the airport does not exist
}



