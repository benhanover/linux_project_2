#include "./missions.h"

//Child process runs this function.
//In "runChildProcess" function we redirected standard input to the read end of parent-to-child pipe,
//so "cout" from this function prints the massage to the "childToParent" pipe,
//then the parent process will read from the pipe and print it to the screen.


void gracefulExit(System& airports)
{
    zipDataBase(airports);
    
    fs::path buildPath = fs::current_path();
    fs::path projectPath = fs::current_path().parent_path();
    string s_projectPath = projectPath;
    string s_buildPath = buildPath;

    if (chdir(s_projectPath.c_str()) != 0) {
        std::cout << "Failed to change directory.\n";
    }

    system("rm -r DB");


    if (chdir(buildPath.c_str()) != 0) {
        std::cout << "Failed to change directory.\n";
    }

    airports.deleteAll(); //free all allocated memory
}