#include  "utility.h"
#include <sstream>


void printMenu();
int getChoice();
void executeChoice(int choice,System& airports, vector<string> paths);
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void getInputFromUser(vector<string>& words, string message);

void printAirportsArv();
void printAirportSchedule(System& airports, vector<string> paths);
void printAllAircraftsFlights(System& airports);
bool checkIfAllAircraftsInDB(System& airports, vector<string>& missing_names, int numOfCodesRecieved, vector<string> codesRecievedVec);
void printSingleAircraftFlights(string& icao24, System& airports);







