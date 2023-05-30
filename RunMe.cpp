#include "./RunMe.h"

int main()
{

    // Set up the signal handler


    System airports;
    int choice;
    string projectPath = fs::current_path().parent_path()/"DB";
    string DBZipPath = fs::current_path().parent_path()/"DB.zip";

    unzipDB(DBZipPath, projectPath);

    vector<string> paths;
    paths.reserve(10);
    airports.getAllPaths(paths);
    airports.load_db(paths);

    SignalHandlerData test;
    test.airportsPtr = &airports;
    // Set up the signal handler with the wrapper function
    signal(SIGINT, SignalHandlerData::handleSignalWrapper);


    choice = getChoice();
    while (true) 
    {
        sendChoiceToParent(choice,airports, paths);
        if (choice == 7)
            break;
        choice = getChoice();
    }
    return 1;
}
//---------------------------------functions------------------------------------
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
            cout << "Wrong choice, please choose again!" << endl;
            printMenu();
            cin >> choice;
            cin.ignore(); // Ignore any leftover newline characters from previous input
        }
    }
    return choice;

}

void sendChoiceToParent(int choice,System& airports, vector<string> paths)
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
        case 5: zipDataBase(airports);
        break;
        case 6:
        break;
        case 7: gracefulExit(airports);
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
    std::filesystem::create_directory(absDestinationPath);


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

    zip_close(archive);
    cout << "Successfully unzipped the directory." << endl;
}



