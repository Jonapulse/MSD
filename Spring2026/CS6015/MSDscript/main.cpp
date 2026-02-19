#include <iostream>
#include "cmdline.h"
#include "parse.hpp"

/**
* \mainpage MSDScript
* \author Jon Pulsipher
* \date 02-03-2026
*/

int main(int argc, char* argv[]){
	//TEMP: Getting parsing working


	//Expr *e = parse_str("   123");
	//Expr *e = parse_str("123*432");
	//Expr *e = parse_str("123+123");
	Expr *e = parse_str("123 + 345 * 325 * 4444 + 322");
	//Expr *e = parse_expr(std::cin);
	e->printExpr(std::cout);
	std::cout << "\n";
	std::cout << "Value: " << e->interp() << '\n';
	
	//use_arguments(argc, argv);
	return 0;
}
