#pragma once
#include "./missions/missions.h"
#include <csignal>

// struct SignalHandlerData
// {
//     System* airportsPtr = nullptr;

//     // Signal handler function
//     static void handleSignal(int signal)
//     {
//         cout << "Recived SIGINT.. cleaning up :)";
//         gracfulExit(airportsPtr);
//     }
// };
struct SignalHandlerData
{
    System* airportsPtr = nullptr;


    // Signal handler function
    static void handleSignalWrapper(int signal)
    {
        SignalHandlerData* data = reinterpret_cast<SignalHandlerData*>(signal);
        if (data != nullptr && signal == SIGINT)
        {
            handleSignal(signal, data);
        }
    }

    // Signal handler function
    static void handleSignal(int signal, SignalHandlerData* data)
    {
        cout << "Received SIGINT.. cleaning up :)" << endl;
        if (data != nullptr && signal == SIGINT)
        {
            gracefulExit(*(data->airportsPtr));
        }
    }
};
//  SignalHandlerData* handlerData = static_cast<SignalHandlerData*>(data);

void printMenu();
int getChoice();

void sendChoiceToParent(int choice,System& airports, vector<string> paths);



void unzipDB(const string& zipFilePath, const string& destinationPath);

