#include <iostream>
#include "cmdline.h"
#include "parse.hpp"

/**
* \mainpage MSDScript
* \author Jon Pulsipher
* \date 02-03-2026
*/

int main(int argc, char* argv[]){
	// //TEMP: Getting parsing working
	// Expr *e = parse_str(" -53");
	// e->printExpr(std::cout);
	// std::cout << "\n";
	// std::cout << "Value: " << e->interp() << '\n';
	
	use_arguments(argc, argv);
	return 0;
}
