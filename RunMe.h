#pragma once
#include "./missions/missions.h"
#include <csignal>
#define READ_END 0
#define WRITE_END 1
char StdOut[4096] = {0};
char StdErr[4096] = {0};
const int BUFFER_SIZE = 10000;
const int MAX_NAME_LENGTH = 5;

void runChildProcess(int* parentToChild,int* childToParent, vector<string> paths, System& airports);
void runParentProcess(int* parentToChild,int* childToParent, pid_t pid);
void handleSIGINT(int signalNumber);
void printMenu();
int getChoice();
void execute(System& airports, vector<string> paths);
void executeChoice(int choice,System& airports, vector<string> paths);
void unzipDB(const string& zipFilePath, const string& destinationPath);
void getInputForChoice(int choice, vector<string>& codeNames);
void getDataAndSendToParent(int choice,System& airports, vector<string> codeNames);









