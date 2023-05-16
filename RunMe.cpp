#include "RunMe.h"

int main(int argc, char* argv[])
{
    System airports;
    int choice;
    choice = getChoice();

    while (choice != 7) 
    {
        executeChoice(choice);
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
    while(flag)
    {
        if(choice > 0 && choice < 8)
            return choice;
        else
        {
            cout << "Wrong choice, please choose again!" << endl;
            printMenu();
            cin >> choice;
        }
    }
}

void executeChoice(int choice)
{
    switch(choice)
    {
        case 1: printAirportsArv();
        break;
        case 2:
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


void printAirportsArv()
{

}