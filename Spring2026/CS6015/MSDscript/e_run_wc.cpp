#include <iostream>
#include "exec.h"

int main (){
    
    const char * const wc_argv[] = { "/usr/bin/wc", "-w" };
    ExecResult wc_result = exec_program(2, wc_argv, "a b c");
    
    if (wc_result.exit_code != 0)
        std::cerr << "non-zero exit: " << wc_result.exit_code << "\n";
    if (wc_result.out != "       3\n")
        std::cerr << "bad wc result\n";

    std::cout << "Exec ran with " << wc_result.exit_code << " and out: " << wc_result.out;
    
    return 0;
}
