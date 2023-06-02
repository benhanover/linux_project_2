#pragma once
#include "./missions/missions.h"
#define READ_END 0
#define WRITE_END 1

char StdOut[4096] = {0};
char StdErr[4096] = {0};
const int BUFFER_SIZE = 10000;

void printMenu();
int getChoice();
void execute(System& airports, vector<string> paths);
void executeChoice(int choice,System& airports, vector<string> paths);


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////






