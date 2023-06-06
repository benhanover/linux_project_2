#include "./missions.h"



//take sentence from user for example "this is a senetence" break it down into array of words that combine the sentence - "this", "is" "a" "sentence"
//*********  handle no input or wrong code names *********
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


/*void notAllInDB(vector<string>& missing_names, System& airports)
{
    int option;

    cout << "Not all ICOA code names inserted exist in current database." << endl;
    cout << "These names doesn't exist in the database:" << endl;
    for (int i = 0; i < missing_names.size(); i++)
    cout << missing_names[i] << ' ';
    cout << endl;
    
    cout << "You have 2 options" << endl;
    cout << "Press 1 to run script with these names to try download info to database." << endl;
    cout << "Press 2 to display data of airports that already exist." << endl ;
    cin >> option;

    if (option == 2)
        return;
    // real names /  not real names

    string projectPath = fs::current_path().parent_path();
    string airportNames = "";
    for (auto &name : missing_names)
        airportNames += name += " ";

    system(((projectPath + "/flightScanner.sh ") += airportNames).c_str());
    
    for (auto& name : missing_names)
    {
        string command = "mv ";
        command += name += " ../";
        system(command.c_str());
    }

    airports.deleteAll();

    vector<string> paths;
    paths.reserve(10);
    airports.getAllPaths(paths);
    airports.load_db(paths);
}*/