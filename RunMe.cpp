#include "./RunMe.h"

System airports;
int main()
{
    int choice;
    string projectPath = fs::current_path().parent_path()/"DB";
    string DBZipPath = fs::current_path().parent_path()/"DB.zip";

    unzipDB(DBZipPath, projectPath);

    signal(SIGINT, handleSIGINT);

    execute(airports);

    return 1;
}
//---------------------------------functions------------------------------------
void execute(System& airports)
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
        runChildProcess(parentToChild, childToParent, airports);
    }

    else // Parent process
    {
        runParentProcess(parentToChild, childToParent, pid);
    }
}


void runChildProcess(int* parentToChild,int* childToParent, System& airports)
{
    vector<string> paths;
    paths.reserve(10);
    airports.getAllPaths(paths);
    airports.load_db(paths); //loading data to child process
    
    close(parentToChild[WRITE_END]);  // Close unused write end of parent-to-child pipe
    close(childToParent[READ_END]);  // Close unused read end of child-to-parent pipe

    dup2(parentToChild[READ_END], STDIN_FILENO);    // Redirect standard input to the read end of parent-to-child pipe
    dup2(childToParent[WRITE_END], STDOUT_FILENO);   // Redirect standard output to the write end of child-to-parent pipe
    
    close(parentToChild[READ_END]);  // Close read end of parent-to-child pipe
    close(childToParent[WRITE_END]);  // Close write end of child-to-parent pipe
    
    while (true) 
    {
        int choice, vectorSize;
        vector<string> codeNames;
        ssize_t bytesRead = read(STDIN_FILENO, &choice, sizeof(choice));
        
        if(choice > 0 && choice < 4)
        {
            bytesRead = read(STDIN_FILENO, &vectorSize, sizeof(vectorSize));
            codeNames.reserve(vectorSize);
            for (int i = 0; i < vectorSize; ++i)
            {
                int nameSize;
                read(STDIN_FILENO, &nameSize, sizeof(nameSize));
                string name;
                char c;
                for (int j = 0 ; j < nameSize; j++)
                {
                    ssize_t bytesRead = read(STDIN_FILENO, &c, sizeof(c));
                    name += c;
                }
                codeNames.push_back(name);
            }
        }
        getDataAndSendToParent(choice,airports,codeNames);
        cout << "^"; //^ signal for parent - end of data
    }
    // // // Close the duplicated standard input and output
    close(STDIN_FILENO);   // Close standard input
    close(STDOUT_FILENO);  // Close standard output

}

void runParentProcess(int* parentToChild,int* childToParent, pid_t pid)
{
        close(parentToChild[READ_END]);  // Close unused read end of parent-to-child pipe
        close(childToParent[WRITE_END]);  // Close unused write end of child-to-parent pipe
        
        while (true) 
        {
            int choice, vectorSize;
            /* vector<string> codeNames;
            choice = getChoice();
            getInputForChoice(choice, codeNames);
            if (choice != 6 && choice != 7)
                write(parentToChild[WRITE_END], &choice, sizeof(choice));
            if(choice > 0 && choice < 4)
            {
                vectorSize = codeNames.size();
                write(parentToChild[WRITE_END], &vectorSize, sizeof(vectorSize));
                for (const auto& name : codeNames)
                {
                    int nameSize = name.size() + 1;
                    write(parentToChild[WRITE_END], &nameSize, sizeof(nameSize));  // Include null terminator
                    write(parentToChild[WRITE_END], name.c_str(), nameSize);  // Include null terminator
                }
            } */
            
            if (choice == 6)
            {
                cout << "The child process Pid is: " << pid << endl;
                continue;
            }   
        
            if (choice == 7)
            {
                gracefulExit(airports);
                break;
            }
            
        }
        close(parentToChild[WRITE_END]);
        close(childToParent[READ_END]);

        // Wait for the child process to exit
        int status;
        waitpid(pid, &status, 0);
}

void getInputForChoice(int choice, vector<string>& codeNames)
{
    switch(choice)
    {
        case 1: getInputFromUser(codeNames, "Insert airports ICOA code names to print arrivals:");
        break;
        case 2: getInputFromUser(codeNames, "Insert airports names to print the full airport schedule:");
        break;
        case 3: getInputFromUser(codeNames,"Please enter icao24 codes of aircrafts, in order to see their schedule.");
        break;
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

void getDataAndSendToParent(int choice,System& airports, vector<string> codeNames)
{
    switch(choice)
    {
        case 1: printAirportsArv(airports, codeNames);
        break;
        case 2: printAirportSchedule(airports, codeNames);
        break;
        case 3: printAllAircraftsFlights(airports);
        break;
        case 4: refreshDataBase(airports);
        break;
        case 5: zipDataBase(airports);
        break;
    }
}


void unzipDB(const string& zipFilePath, const string& destinationPath)
{
    zip_t *archive = zip_open(zipFilePath.c_str(), ZIP_RDONLY, nullptr);
    if (archive == nullptr)
    {
        cerr << "Failed to open the ZIP file: " << zip_strerror(archive) << endl;
        return;
    }

    filesystem::path absDestinationPath = filesystem::absolute(destinationPath);

    // Create the destination directory manually
    filesystem::create_directory(absDestinationPath);


    int numEntries = zip_get_num_entries(archive, ZIP_FL_UNCHANGED);
    for (int i = 0; i < numEntries; ++i)
    {
        zip_stat_t entryStats;
        if (zip_stat_index(archive, i, ZIP_FL_UNCHANGED, &entryStats) != 0)
        {
            cerr << "Failed to retrieve the ZIP entry information at index " << i << endl;
            continue;
        }

        string entryName = entryStats.name;
        filesystem::path entryPath = absDestinationPath / entryName;

        if (entryStats.name[strlen(entryStats.name) - 1] == '/')
        {
            // Entry is a directory
            filesystem::create_directories(entryPath);
        }
        else
        {
            // Entry is a file
            zip_file_t *file = zip_fopen_index(archive, i, ZIP_FL_UNCHANGED);
            if (file == nullptr)
            {
                cerr << "Failed to open the ZIP file entry: " << entryName << endl;
                continue;
            }

            ofstream outputFile(entryPath.string(), ios::binary);
            if (!outputFile)
            {
                cerr << "Failed to create the output file: " << entryPath << endl;
                continue;
            }

            char buffer[1024];
            zip_int64_t bytesRead;
            while ((bytesRead = zip_fread(file, buffer, sizeof(buffer))) > 0)
            {
                outputFile.write(buffer, bytesRead);
            }

            outputFile.close();
            zip_fclose(file);
        }
    }

    //making the scripts executable
    string flightScannerScriptPath = destinationPath + "/flightScanner.sh";
    string command = "chmod +x " + flightScannerScriptPath;
    system(command.c_str());
    
    string cleanScriptPath = destinationPath + "/clean.sh";
    command = "chmod +x " + cleanScriptPath;
    system(command.c_str());

    zip_close(archive);
    cout << "Successfully unzipped the directory." << endl;
}

void handleSIGINT(int signalNumber)
{
    cout << "You sent SIGINT signal... exiting gracefully :)" << endl;
    gracefulExit(airports);
    exit(signalNumber);
}
