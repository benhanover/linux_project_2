#include "./missions.h"


//string getNewNameFromDBorRerunScript(string missing_name, vector<string>& paths, System& airports);
void printFullAirportSchedule(string& IcoaCode, System& airports);
int compare2Flights(FlightInfo* f1, FlightInfo* f2);


void printAirportSchedule(System& airports, vector<string> paths)
{
    vector<string> airportsNames;
    getInputFromUser(airportsNames, "Insert airports names to print the full airport schedule:");
    vector<string> missing_names;

    bool allInDB = false;
    int airportNamesSize = airportsNames.size();
    allInDB = airports.checkIfAllInDbAndUpdateMissing(missing_names, airportsNames);


    if (!allInDB)
    {
        cout << "Not all ICOA code names inserted exist in current database." << endl;
        cout << "Displaying data of airports that exist." << endl ;
    }
        // notAllInDB(missing_names, airports);
    else
         cout << "All in DB, printing as asked." << endl;

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



/* string getNewNameFromDBorRerunScript(string missing_name, vector<string>& paths,System& airports)
 {
    int option;
    string wantedName;
    cout << "The first ICOA code name inserted (" << missing_name << ") doesn't exist in current database." << endl;
    cout << "Please choose one of the following options:" << endl;
    cout << "Press 1 to run script with this name to try download info to database." << endl;
    cout << "Press 2 to choose code name that exist in the database." << endl;
    cin >> option;

    fs::path currentPath = fs::current_path();
    string projectPath = currentPath;
    string airportName = " " + missing_name;
   
    if (option == 1)        
    {
       system(((projectPath + "/flightScanner.sh ") += airportName).c_str());
       return "";
    }
    else
    {
        cout << "This is a list of names that exist in the database:" << endl;
        for (int i=0; i < paths.size(); i += 2)
            cout << airports.getAirportNameFromPath(paths[i]) << "  ";
        cout << endl << "Please choose only 1 name from this list." << endl;
        cin >> wantedName;
        return wantedName;
    }
}*/
