#include "./RunMe.h"

int main()
{
    System airports;
    int choice;

    vector<string> paths;
    paths.reserve(10);
    airports.getAllPaths(paths);
    airports.load_db(paths);

    choice = getChoice();
    while (choice != 7) 
    {
        executeChoice(choice,airports, paths);
        choice = getChoice();
    }
    return 1;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void printMenu()
{
    cout << "*************************************" << endl;
    cout << "1 - Fetch Airports incoming Flights." << endl;
    cout << "2 - Fetch airports full flights schedule." << endl;
    cout << "3 - Fetch aircraft full flights schedule." << endl;
    cout << "4 - Update DB." << endl;
    cout << "5 - Zip DB files." << endl;
    cout << "6 - Get child process PID." << endl;
    cout << "7 - Exit." << endl;
    cout << "Please make your choice <1, 2, 3, 4, 5, 6, 7>:" << endl;
}

int getChoice()
{
    char choice;
    bool flag = true;
    printMenu();
    cin >> choice;
    cin.ignore(); // Ignore any leftover newline characters from previous input
    
    while(flag)
    {
        if(choice > '0' && choice < '8')
            return choice - '0';
        else
        {   
            cout << "Wrong choice, please choose again!" << endl;
            printMenu();
            cin >> choice;
            cin.ignore(); // Ignore any leftover newline characters from previous input
        }
    }
    return choice;

}

void executeChoice(int choice,System& airports, vector<string> paths)
{
    switch(choice)
    {
        case 1: printAirportsArv(airports, paths);
        break;
        case 2: printAirportSchedule(airports, paths);
        break;
        case 3:printAllAircraftsFlights(airports);
        break;
        case 4:
        break;
        case 5:
        break;
        case 6:
        break;
        case 7:
        break;
    }
}


void printAirportsArv()
{
    vector<string> airportsCodeNames;
    getInputFromUser(airportsCodeNames, "Insert airports ICOA code names to print arrivals:");

}


void printAirportSchedule(System& airports, vector<string> paths)
{

}


void printAllAircraftsFlights(System& airports)
{
    vector<string> paths;
    paths.reserve(10);
    vector<string> wantedCodes;
    wantedCodes.reserve(20);
    vector<string> missing_names;
    missing_names.reserve(20);
    int numOfCodes;
   
   
    /*cout << "How many icao24 code you want to enter?" << endl;
    cin >> numOfCodes;
    
    while (numOfCodes <= 0)
    {
        cout << "The number you entered is not valid." << endl;
        cout << "How many icao24 code you want to enter?" << endl;
        cin >> numOfCodes;
    }
    
    wantedCodes.reserve(numOfCodes);
    cout << "Please enter icao24 codes." << numOfCodes << " codes." << endl;*/
  
    getInputFromUser(wantedCodes,"Please enter icao24 codes.");

    airports.getAllPaths(paths);
    bool allInDB = false;
    airports.load_db(paths);

    allInDB = checkIfAllAircraftsInDB(airports,missing_names,numOfCodes,wantedCodes);
    
    if (!allInDB)
        cout << "Not all aircrafts in database. Printing only those that exist." << endl;
    
    string curAircraft;
    for(int i = 0; i < numOfCodes; i++)
    {
       curAircraft = wantedCodes[i];
       if (find(missing_names.begin(), missing_names.end(), curAircraft) != missing_names.end())
            continue;// The current name is missing.
       else 
        printSingleAircraftFlights(curAircraft,airports);
    }

}

bool checkIfAllAircraftsInDB(System& airports, vector<string>& missing_names, int numOfCodesRecieved, vector<string> codesRecievedVec)
{
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
}
