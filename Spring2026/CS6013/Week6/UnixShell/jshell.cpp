#include "jshell.hpp"
#include "shelpers.hpp"
#include <vector>
using namespace std;

void runShell(string test_str = ""){
    while(true){
        cout << "(>'-')> ";
        string command_str;
        if(test_str == "")
            getline(cin, command_str);
        else 
            command_str = test_str;

        vector<string> tokens = tokenize(command_str);
        vector<Command> commands = getCommands(tokens);
        for(Command comm : commands){
            if(comm.execName == "exit")
            {
                cout << "Exiting shell...\n";
                return;
            }

            int rc = fork();
            if(rc == 0){ 
                //Child forks and executes
                 //
                if(comm.inputFd != STDIN_FILENO){
                    dup2(comm.inputFd, STDIN_FILENO);
                    close(comm.inputFd); //You haven't tested dup and close yet. This is what ai summary told you to do for a different request.
                }
                if(comm.outputFd != STDOUT_FILENO){
                    dup2(comm.outputFd, STDOUT_FILENO);
                    close(comm.outputFd); //You haven't tested dup and close yet. This is what ai summary told you to do for a different request.
                }

                execvp(comm.execName.c_str(), const_cast<char**>(comm.argv.data()));
                
            }
            else 
            {
                //Parent waits for child to die
                 //
                int status;
                pid_t terminated_pid = waitpid(rc, &status, 0); 
                if(terminated_pid == -1)
                {
                    perror("waitPid failed");
                    exit(EXIT_FAILURE);
                }
                //TODO: clean up open file descriptors
            }
        }
        if(test_str != "")
            break;
    }
}

