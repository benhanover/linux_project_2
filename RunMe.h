#pragma once
#include  "utility.h"
#include <sstream>


void printMenu();
int getChoice();

void executeChoice(int choice,System& airports, vector<string> paths);


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void printAirportsArv(System& airports, vector<string> paths);
void getInputFromUser(vector<string>& words, string message);
void printAirportSchedule(System& airports, vector<string> paths);






