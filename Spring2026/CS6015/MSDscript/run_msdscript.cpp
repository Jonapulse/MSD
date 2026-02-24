/**
 * \file run_msdscript.cpp
 * \brief combined run_msdscript.cpp/run_msdscript2.cpp from 6015 canvas files. 
 * Compares random --interp/--print for one filepath, or --interp between diff implementations for two filepaths.
 */

#include <iostream>
#include <sstream>
#include <stdlib.h>
#include "exec.h"

static std::string random_expr_string();
std::string generateVarName();
std::string generateNum();
void print_differences(ExecResult prog1, ExecResult prog2);

int main(int argc, char **argv) {

    //set random seed for test generation
    srand(clock());

    if(argc == 2) {//For one argument, we compare the path's --interp and --print
        const char * const interp_argv[] = {argv[1], "--interp" };
        const char * const print_argv[] = {argv[1], "--print" };
        int passCount = 0; 
        for (int i = 0; i < 100; i++) {
            std::string in = random_expr_string();
        
            ExecResult interp_result = exec_program(2, interp_argv, in);
            ExecResult print_result = exec_program(2, print_argv, in);

            ExecResult interp_again_result = exec_program(2, interp_argv, print_result.out);

            if (interp_again_result.out != interp_result.out)
                std::cout << "mismatch - a: " << interp_result.out << " vs " << interp_again_result.out << std::endl;
            else if(interp_result.exit_code == 0)
                passCount++;
        }
        std::cout << "Self-test completed for " << argv[1] << " with " << passCount << " matching and returning with success exit code out of " << 100 << std::endl;
    } 
    else if (argc == 3)
    {
        const char * const interp1_argv[] = { argv[1], "--interp" };
        const char * const interp2_argv[] = { argv[2], "--interp" };
        int mismatchCount = 0;
        for (int i = 0; i < 100; i++) {
            std::string in = random_expr_string();
            
            ExecResult interp1_result = exec_program(2, interp1_argv, in);
            ExecResult interp2_result = exec_program(2, interp2_argv, in);

            if(interp1_result.exit_code != interp2_result.exit_code){
                mismatchCount++;
                std::cout << "Exit Code mismatch for input " << in 
                << "\n\tProg1: " << interp1_result.exit_code << " with err " << interp1_result.err 
                << "\tProg2: " << interp2_result.exit_code << " with err " << interp2_result.err << '\n';
            }
            else
            {
                if(interp1_result.out != interp2_result.out){
                    mismatchCount++;
                    std::cout <<"Mismatch for input: " << in
                    << "\n\tProg1: " << interp1_result.out
                    << "\tProg2: " << interp2_result.out << '\n';
                }
            }
        }
        std::cout << "Comparison of interp for " << argv[1] << " and " << argv[2] << " completed with " << mismatchCount << " mismatches." << std::endl;
    } else
    {
        std::cout << "run_msdscript_test must run with 1 or 2 filepath args." << '\n';
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
            return generateNum();
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
 * 0 to 100 for readable numbers that probably won't break int max values
 */
std::string generateNum()
{
    return std::to_string(rand() % 100);
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