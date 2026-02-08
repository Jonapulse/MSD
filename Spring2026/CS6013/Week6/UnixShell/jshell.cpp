#include "jshell.hpp"
#include "shelpers.hpp"
#include <vector>
using namespace std;

void runShell(){
    while(true){
        cout << "(>'-')> ";
        string command_str;
        cin >> command_str;

        vector<Command> commands = getCommands(tokenize(command_str));
        for(Command comm : commands){
            int rc = fork();
            if(rc == 0){ 
                //Child forks and executes
                 //
                if(comm.inputFd != STDIN_FILENO)
                    dup2(STDIN_FILENO, comm.inputFd);
                if(comm.outputFd != STDOUT_FILENO)
                    dup2(STDOUT_FILENO, comm.outputFd);
                
                execvp(comm.execName.c_str(), const_cast<char**>(comm.argv.data()));

            }
            else 
            {
                //Parent waits for child to die
                 //
                int status;
                waitpid(rc, &status, 0); 
                if(status != 0)
                {
                    string errorStr = "Error while running " + comm.execName + " with status code " + to_string(status);
                    perror(errorStr.c_str());
                    //TODO: Clean up open file descriptors
                }
            }
        }
    }
}

