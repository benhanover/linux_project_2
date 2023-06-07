#pragma once
#include "./missions/missions.h"
#include <csignal>
#include <unistd.h>
#define READ_END 0
#define WRITE_END 1
const int BUFFER_SIZE = 100000;


void runChildProcess(int* parentToChild,int* childToParent, System& airports);
void runParentProcess(int* parentToChild,int* childToParent, pid_t pid);
void handleSIGINT(int signalNumber);
void printMenu();
int getChoice();
void execute(System& airports);
void executeChoice(int choice,System& airports);
void unzipDB(const string& zipFilePath, const string& destinationPath);
void getInputForChoice(int choice, vector<string>& codeNames);
void getDataAndSendToParent(int choice,System& airports, vector<string> codeNames);
