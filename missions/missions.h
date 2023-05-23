#pragma once
#include "../utilities/utility.h"
#include <sstream>


//--------------------------functions------------------------------
void getInputFromUser(vector<string>& words, string message);
void notAllInDB(vector<string>& missing_names, System& airports);

//--------------------------mission 1------------------------------

void printSingleAirportArv(System& airports,string& IcoaCode);
void printAirportsArv(System& airports, vector<string> paths);
//--------------------------mission 2------------------------------

void printAirportSchedule(System& airports, vector<string> paths);

//--------------------------mission 3------------------------------
//mission 3
void printAllAircraftsFlights(System& airports);
bool checkIfAllAircraftsInDB(System& airports, vector<string>& missing_names, vector<string> codesRecievedVec);
void printSingleAircraftFlights(string& icao24, System& airports);

//--------------------------mission 4------------------------------
void refreshDataBase(System& airports, vector<string>paths);
