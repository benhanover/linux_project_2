#include "RunMe.h"

int main()
{
    System airports;
    int choice;

    vector<string> paths;
    // paths.reserve(10);
    // airports.getAllPaths(paths);

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
    int choice;
    bool flag = true;
    printMenu();
    cin >> choice;
    cin.ignore(); // Ignore any leftover newline characters from previous input
    
    while(flag)
    {
        if(choice > 0 && choice < 8)
            return choice;
        else
        {
            cout << "Wrong choice, please choose again!" << endl;
            printMenu();
            cin >> choice;
            cin.ignore(); // Ignore any leftover newline characters from previous input
        }
    }
}

void executeChoice(int choice,System& airports, vector<string> paths)
{
    switch(choice)
    {
        case 1: printAirportsArv(airports, paths);
        break;
        case 2: printAirportSchedule(airports, paths);
        break;
        case 3:
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


void printAirportsArv(System& airports, vector<string> paths)
{
    vector<string> airportsCodeNames;
    getInputFromUser(airportsCodeNames, "Insert airports ICOA code names to print arrivals:");



}

//take sentence from user for example "this is a seneteence" break it down into array of words that combine the sentence - "this", "is" "a" "sentence"
void getInputFromUser(vector<string>& words, string message)
{
    cout << message << endl;
    string line;
    getline(cin, line);

    istringstream iss(line);
    string code;
    while (iss >> code)
        words.push_back(code);
}

void printAirportSchedule(System& airports, vector<string> paths)
{

}