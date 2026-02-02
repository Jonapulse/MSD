#include <iostream>   // For std::cout
#include <unistd.h>   // For fork()
#include <sys/types.h> // For pid_t
#include <cstdio>     // For perror()
#include <cstdlib>    // For exit()

int main(int argc, char const *argv[])
{
    pid_t c_pid = fork();

    if(c_pid == -1){
        perror("fork failed!");
        exit(1);
    }
    else if (c_pid > 0) { //parent process
        std::cout << "parent\n";
        int status;
        waitpid(c_pid, &status, 0);
        std::cout << "hi checking that we waited.\n";
        exit(0);
    } else { //child process
        std::cout << "child\n";
        exit(0);
    }
    return 0;
}
