#include <iostream>
#include "cmdline.h"
#include "parse.hpp"

/**
* \mainpage MSDScript
* \author Jon Pulsipher
* \date 02-03-2026
*/

int main(int argc, char* argv[]){
	run_mode_t run_mode = use_arguments(argc, argv);
	switch(run_mode)
	{
		case(run_mode_t::do_interp):
		{ //Braces included for scoping repeated var names
			std::cout << "Write an expression to interpret: ";
			Expr* parsedExpr = parse_expr(std::cin);
			std::cout << parsedExpr->interp() << '\n';
		}
			break;
		case(run_mode_t::do_print):
		{
			std::cout << "Write an expression to print: ";
			Expr* parsedExpr = parse_expr(std::cin);
			parsedExpr->printExpr(std::cout);
			std::cout <<"\n";
		}
			break;
		case(run_mode_t::do_pretty_print):
		{
			std::cout << "Write an expression to pretty print: ";
			Expr* parsedExpr = parse_expr(std::cin);
			parsedExpr->pretty_print(std::cout);
			std::cout <<"\n";
		}
			break;
		case(run_mode_t::do_nothing):
			break;
	}
	return 0;
}
