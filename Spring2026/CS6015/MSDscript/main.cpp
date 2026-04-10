#include <iostream>
#include "cmdline.h"
#include "parse.hpp"

/**
* \mainpage MSDScript
* \author Jon Pulsipher
* \date 02-03-2026
*/

int main(int argc, char* argv[]){
	try{
		run_mode_t run_mode = use_arguments(argc, argv);
		switch(run_mode)
		{
			case(run_mode_t::do_interp):
			{ //Braces included for scoping repeated var names
				// std::cout << "Write an expression to interpret: ";
				PTR(Expr) parsedExpr = parse_expr(std::cin);
				std::cout << parsedExpr->interp(Env::empty)->to_string() << '\n';
			}
				break;
			case(run_mode_t::do_print):
			{
				// std::cout << "Write an expression to print: ";
				PTR(Expr) parsedExpr = parse_expr(std::cin);
				std::cout << parsedExpr->to_string() << '\n';
			}
				break;
			case(run_mode_t::do_pretty_print):
			{
				// std::cout << "Write an expression to pretty print: ";
				PTR(Expr) parsedExpr = parse_expr(std::cin);
				std::cout << parsedExpr->to_pretty_string() << '\n';
			}
				break;
			case(run_mode_t::do_nothing):
				break;
		}
		return 0;
	} catch (std::runtime_error exn){
		std::cerr << exn.what() << "\n";
    	return 1;
	}
}
