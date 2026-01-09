#include <iostream>
#include "cmdline.h"

bool testsSeen = false;

/**
 * Prints out text in response to arguments. Placeholder for later functionality (I think...)
 * 
 * @param int argc - number of arguments
 * @param int argc - list of arguments as char*s
 */
void use_arguments(int argc, char* argv[]){
    if(argc == 1)
    {
        std::cout << "No arguments. Send in arguments to test cmdline!";
        exit(0);
    }

	for(int i = 1 ; i < argc; i++){
		if(strcmp(argv[i], "--help") == 0)
		{
			std::cout << "use --test pass tests, but only once or you'll fail!";
			exit(0);
		}
		else if (strcmp(argv[i], "--test") == 0)
		{
			if(!testsSeen){
				std::cout << "Tests passed\n";
				testsSeen = true;
			} else
			{
				std::cerr << "Illegal use of --test more than once!\n";
				exit(1);
			}
		} else
		{
			std::cerr << "Use of unknown arg: " << argv[i];
			exit(1);
		}
		
	}
}