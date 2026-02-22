/**
 * \file run_msdscript.cpp
 * \brief combined run_msdscript.cpp/run_msdscript2.cpp from 6015 canvas files. 
 * Compares random --interp/--print for one filepath, or --interp between diff implementations for two filepaths.
 */

#include <iostream>
#include <stdlib.h>
#include "exec.h"

static std::string random_expr_string();
std::string generateVarName();
std::string generateNum();

int main(int argc, char **argv) {

    //set random seed for test generation
    srand(clock());

    if(argc == 2) {//For one argument, we compare the path's --interp and --print
        const char * const interp_argv[] = { "msdscript", "--interp" };
        const char * const print_argv[] = { "msdscript", "--print" };
        for (int i = 0; i < 100; i++) {
            std::string in = random_expr_string();
            std::cout << "Trying"<< in << "\n";
            
            ExecResult interp_result = exec_program(2, interp_argv, in);
            ExecResult print_result = exec_program(2, print_argv, in);

            ExecResult interp_again_result = exec_program(2, interp_argv, print_result.out);

            if (interp_again_result.out != interp_result.out)
                throw std::runtime_error("different result for printed");
            
        }
    } 
    else if (argc == 3)
    {
        const char * const interp1_argv[] = { "msdscript", "--interp" };
        const char * const interp2_argv[] = { "msdscript2", "--interp" };
        for (int i = 0; i < 100; i++) {
            std::string in = random_expr_string();
            std::cout << "Trying"<< in << "\n";
            
            ExecResult interp1_result = exec_program(2, interp1_argv, in);
            ExecResult interp2_result = exec_program(2, interp2_argv, in);

            if (interp1_result.out != interp2_result.out)
            throw std::runtime_error("different results");
        }
    } else
    {
        std::cout << "run_msdscript_test must run with 1 or 2 filepath args.";
        return 1;
    }

    return 0;
}

std::string random_expr_string() {
    //Recurse 40% of the time
    bool shouldRecurse = rand() % 10 < 4;

    if(shouldRecurse)
    {
        //Do add/mult 70%, else let
        bool doAddMult = rand() % 10 < 7;
        if(doAddMult){
            std::string op = rand() % 10 < 5 ? "+" : "*";
            return random_expr_string() + op + random_expr_string();
        }
        else
        {
            //To assure meaningful let expressions, we guarantee the lhs of let will contain the same var name +/* an expression.
            std::string varName = generateVarName();
            std::string letExpr = "_let " + varName + "=" + generateNum() + "_in ";
            std::string op = rand()%10 < 5 ? "+" : "*";
            letExpr += varName + op + random_expr_string();
            return letExpr;
        }
    } else
    {
        bool doNum = rand() % 10 < 7;
        if(doNum){
            return std::to_string(rand());
        } else
        {
            return generateVarName();
        }
    }
    //singular - path for num
    if ((rand() % 10) < 6)
        return std::to_string(rand());
    else
        return random_expr_string() + "+" + random_expr_string();
}

/**
 * We're allowing any number. For more readable content limiting 1 digit is an option.
 */
std::string generateNum()
{
    return std::to_string(rand());
}

/**
 * Normally we generate x or y. Occasionally we generate random strings of lowercase
 */
std::string generateVarName()
{
    bool doSimple = rand() % 10 < 7;
    if(doSimple)
    {
        return rand() % 10 < 5 ? "x" : "y";
    }
    else
    {
        std::string word = "";
        for (int i = rand() % 5 + 1; i-- > 0; )
            word += 97 + rand() % 26;
        return word;
    }
}