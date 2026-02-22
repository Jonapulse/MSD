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

            if(comm.execName == "cd"){
                const char *path;
                if(comm.argv.size() <= 3){ //[exec name, "cd", nullptr]
                    path = getenv("HOME");
                }
                else{
                    path = comm.argv[1];
                }

                if(chdir(path) != 0)
                {
                    perror("error changing directory");
                }
                continue;
            }

            int rc = fork();
            if(rc == 0){ 
                //Child forks and executes
                 //
                if(comm.inputFd != STDIN_FILENO){
                    dup2(comm.inputFd, STDIN_FILENO);
                    close(comm.inputFd); 
                }
                if(comm.outputFd != STDOUT_FILENO){
                    dup2(comm.outputFd, STDOUT_FILENO);
                    close(comm.outputFd);
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

                if(comm.inputFd != STDIN_FILENO)
                    close(comm.inputFd);
                if(comm.outputFd != STDOUT_FILENO)
                    close(comm.outputFd);
            }
        }
        if(test_str != "")
            break;
    }
}

