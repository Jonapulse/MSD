//////////////////////////////////////////////////////////////////////////////////
//
// Jon Pulsipher - 6013, A3 Shell. Feb, 2026.
//
//////////////////////////////////////////////////////////////////////////////////

#include "jshell.hpp"
#include "shelpers.hpp"
#include <vector>
using namespace std;

void runShell(){
    while(true){
        //Clean up any background processes that have ended
        int status;
        waitpid(-1, &status, WNOHANG);

        cout << "(>'-')> " << flush;
        string command_str;
        
        if(!getline(cin, command_str)){
            cout << "\nExiting shell";
            return;
        }

        vector<string> tokens = tokenize(command_str);
        vector<Command> commands = getCommands(tokens);

        if(commands.empty() || commands[0].execName.empty()){
            continue;
        }

        vector<pid_t> pids;

        for(Command comm : commands){
            if(comm.execName == "exit")
            {
                cout << "Exiting shell...\n";
                return;
            }

            if(comm.execName == "cd"){
                const char *path;
                if(comm.argv.size() < 3){ //[exec name, "cd"]
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

                //Clean up fids this child isn't using
                for(Command& other : commands)
                {
                    if(other.inputFd != STDIN_FILENO &&
                       other.inputFd != comm.inputFd){
                        close(other.inputFd);
                    }
                    if(other.outputFd != STDOUT_FILENO &&
                       other.outputFd != comm.outputFd){
                        close(other.outputFd);
                    }
                }

                execvp(comm.execName.c_str(), const_cast<char**>(comm.argv.data()));
                //If execvp fails to switch process
                perror("execvp failed");
                exit(EXIT_FAILURE);
                
            }
            else 
            {
                pids.push_back(rc);

                if(comm.inputFd != STDIN_FILENO)
                    close(comm.inputFd);
                if(comm.outputFd != STDOUT_FILENO)
                    close(comm.outputFd);
            }
        }

        if(!commands.empty() && !commands.back().background){
            for(pid_t pid : pids){
                int status;
                if(waitpid(pid, &status, 0) == -1){
                    perror("waitpid failed");
                }
            }
        }
    }
}

