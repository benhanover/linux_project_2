#pragma once
#include "./missions/missions.h"
#include <csignal>

void handleSIGINT(int signalNumber);

void printMenu();
int getChoice();

void sendChoiceToParent(int choice,System& airports, vector<string> paths);



void unzipDB(const string& zipFilePath, const string& destinationPath);

