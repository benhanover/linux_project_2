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
        cout << "Pipe creation failed." << endl;
        return;
    }

    pid_t pid = fork();

    if (pid == -1)
    {
        cout << "Error forking process" << endl;
        return;
    }

    else if (pid == 0) // Child process
    {
        close(parentToChild[WRITE_END]);  // Close unused write end of parent-to-child pipe
        close(childToParent[READ_END]);  // Close unused read end of child-to-parent pipe

        dup2(parentToChild[READ_END], STDIN_FILENO);    // Redirect standard input to the read end of parent-to-child pipe
        dup2(childToParent[WRITE_END], STDOUT_FILENO);   // Redirect standard output to the write end of child-to-parent pipe

        close(parentToChild[READ_END]);  // Close read end of parent-to-child pipe
        close(childToParent[WRITE_END]);  // Close write end of child-to-parent pipe

        while (true) 
        {
            ssize_t bytesRead = read(STDIN_FILENO, &choice, sizeof(choice));
            if (bytesRead <= 0) // End of data
                break;

            if (choice == 7)
            {
                break; // End the loop if the user chooses option 7 to exit
            }
            // Execute the choice in the child process
            //executeChoice(choice, airports, paths);
            //executeChoice(choice, airports, paths);
            //write(STDOUT_FILENO, result.c_str(), result.length());
            string result = "Process child worked !\n";
            write(STDOUT_FILENO, result.c_str(), result.length());
        }
        // // // Close the duplicated standard input and output
        close(STDIN_FILENO);   // Close standard input
        close(STDOUT_FILENO);  // Close standard output
    }

    else // Parent process
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

            // Read the output of the child process
            char buffer[BUFFER_SIZE];
            ssize_t bytesRead = read(childToParent[0], buffer, BUFFER_SIZE - 1);
            if (bytesRead > 0) 
            {
                buffer[bytesRead] = '\0';  //if there is any more things in the buffer it clean them.
                cout << "Output from child process:\n" << buffer << endl;
            }
        }
        close(parentToChild[WRITE_END]);
        close(childToParent[READ_END]);

        // Wait for the child process to exit
        int status;
        waitpid(pid, &status, 0);
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


