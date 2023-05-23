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

//--------------------------mission 4------------------------------
void refreshDataBase(System& airports, vector<string>paths);
