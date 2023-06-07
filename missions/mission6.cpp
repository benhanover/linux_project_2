#include "./missions.h"

//Child process runs this function.
//In "runChildProcess" function we redirected standard input to the read end of parent-to-child pipe,
//so "cout" in this function prints the massage to the "childToParent" pipe,
//then the parent process will read from the pipe and print it to the screen.

void printChildProcessPid()
{
    int childProcessPid = getpid();
    string messagePidOfChildProcess = "The child process Pid is " + childProcessPid;
    cout << messagePidOfChildProcess << endl;
}