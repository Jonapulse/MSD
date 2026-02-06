#include <iostream>   // For std::cout
#include <unistd.h>   // For fork()
#include <sys/types.h> // For pid_t
#include <cstdio>     // For perror()
#include <cstdlib>    // For exit()
using namespace std;

int main(int argc, char const *argv[])
{
    if(argc != 2)
    {
        std::cout << "Give me args to print!";
        exit(1l);
    }


    int fildes[2];
    int rc = pipe(fildes); //fildes already a pointer
    int writeFd = fildes[0];
    int readFd = fildes[1];

    pid_t c_pid = fork();

    if(c_pid == -1){
        perror("fork failed!");
        exit(1);
    }
    else if (c_pid > 0) { //parent process
        cout << "Parent\n";
        int status;

        string msg = argv[1];
        int write_len = msg.length() + 1;
        cout << "What is len before we send?: " << write_len << " from msg " << msg;
        write(writeFd, &write_len, 4);
        write(writeFd, msg.c_str(), write_len);

        cout << "parent done sending message.\n";
        waitpid(c_pid, &status, 0);
        cout << "parent done waiting for child to DIE.\n";
        //signal()

        bool done = false;
        while(!done){
            string newMsg;
            getline(stdin, newMsg);
        }
        exit(0);
    } else { //child process
        int length = 0;
        read(readFd, &length, 4);
        cout << "child thinks length is: " << length << "\n";
        char msg[length];
        read(readFd, msg, length);
        cout << "child got message: " << msg << "\n";
        exit(0);
    }
    return 0;
}
