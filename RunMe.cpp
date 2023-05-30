#include "./RunMe.h"

int main()
{
    System airports;
    vector<string> paths;

    paths.reserve(10);
    airports.getAllPaths(paths);
    airports.load_db(paths);

    execute(airports, paths);

    return 1;
}
//---------------------------------functions------------------------------------
void execute(System& airports, vector<string> paths)
{
    int choice;
    int parentToChild[2];  // Pipe for parent to child communication
    int childToParent[2];  // Pipe for child to parent communication

    if (pipe(parentToChild) == -1 || pipe(childToParent) == -1) {
        cerr << "Pipe creation failed." << endl;
        return;
    }

    pid_t pid = fork();

    if (pid < 0)
    {
        cout << "Error forking process" << endl;
        return;
    }

    else if (pid > 0) // Parent process
    {
        close(parentToChild[READ_END]);  // Close unused read end of parent-to-child pipe
        close(childToParent[WRITE_END]);  // Close unused write end of child-to-parent pipe

        while (true) 
        {
            choice = getChoice();

            // Send the choice to the child process
            write(parentToChild[WRITE_END], &choice, sizeof(choice));

            if (choice == 7)
            {
                break; // End the loop if the user chooses option 7 to exit
            }

            // Wait for child process to finish
            int status;
            waitpid(pid, &status, 0);

            char buffer[BUFFER_SIZE];
            memset(buffer, 0, sizeof(buffer));
            ssize_t bytesRead = read(childToParent[0], buffer, sizeof(buffer) - 1);

            //Print the data that received from the child 
            cout.write(buffer, bytesRead);
            cout << endl;
        }
        close(parentToChild[WRITE_END]);
        close(childToParent[READ_END]); 
    }

    else // Child process
    {
        close(parentToChild[WRITE_END]);  // Close unused write end of parent-to-child pipe
        close(childToParent[READ_END]);  // Close unused read end of child-to-parent pipe
        int choice;
        while (true) 
        {
            ssize_t bytesRead = read(parentToChild[0], &choice, sizeof(choice));
            if(bytesRead <=0) //end of data
                break;

            executeChoice(choice,airports, paths);
        }
        close(parentToChild[READ_END]); // Close the read end of parent-to-child pipe
        close(childToParent[WRITE_END]); // Close the write end of child-to-parent pipe
    }
}



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
    char choice;
    bool flag = true;
    printMenu();
    cin >> choice;
    cin.ignore(); // Ignore any leftover newline characters from previous input
    
    while(flag)
    {
        if(choice > '0' && choice < '8')
            return choice - '0';
        else
        {   
            cout << "Invalid choice, please choose again!" << endl;
            printMenu();
            cin >> choice;
            cin.ignore(); // Ignore any leftover newline characters from previous input
        }
    }
    return choice;

}

void executeChoice(int choice,System& airports, vector<string> paths)
{
    switch(choice)
    {
        case 1: printAirportsArv(airports, paths);
        break;
        case 2: printAirportSchedule(airports, paths);
        break;
        case 3:printAllAircraftsFlights(airports);
        break;
        case 4: refreshDataBase(airports, paths);
        break;
        case 5:
        break;
        case 6:
        break;
        case 7:
        break;
    }
}


