/**
 * \file cmdline.cpp
 * \brief interprets command line args and executes appropriately. Responds to: "--help" and "--test"
 */

#include <iostream>
#include "cmdline.h"
#define CATCH_CONFIG_RUNNER
#include "catch.h"

/**
 * \brief Prints out text in response to arguments. Placeholder for later functionality (I think...)
 * 
 * \param int argc - number of arguments
 * \param int argc - list of arguments as char*s
 */
void use_arguments(int argc, char* argv[]){
    if(argc == 1)
    {
        std::cout << "No arguments. Send in arguments to test cmdline!\n";
        exit(0);
    }

	bool testsSeen = false;

	for(int i = 1 ; i < argc; i++){
		if(strcmp(argv[i], "--help") == 0)
		{
			std::cout << "use --test pass tests, but only once or you'll fail!\n";
			exit(0);
		}
		else if (strcmp(argv[i], "--test") == 0)
		{
			if(testsSeen){
				std::cerr << "Illegal use of --test more than once!\n";
				exit(1);
			}
			testsSeen = true;
			if(Catch::Session().run(1, argv) != 0){
				exit(1);
			}
		} else
		{
			std::cerr << "Use of unknown arg: " << argv[i] << "\n";
			exit(1);
		}
		
	}
}