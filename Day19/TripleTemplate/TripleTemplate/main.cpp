//
//  main.cpp
//  TripleTemplate
//
//  Created by Jonathan Pulsipher on 9/11/25.
//

#include <iostream>
#include "Triple.h"
#include <string>
#include <vector>

int main(int argc, const char * argv[]) {
    
    Triple t_int{1, 2, 3};
    std::cout << t_int.getA() << ", " << t_int.getB() << ", " << t_int.getC() << ": " << t_int.SumTriple() << '\n';
    
    std::string s1 = "One";
    std::string s2 = "Two";
    std::string s3 = "Three";
    
    Triple t_string{s1, s2, s3};
    std::cout << t_string.getA() << ", " << t_string.getB() << ", " << t_string.getC() << ": " << t_string.SumTriple() << '\n';
    
    std::vector v1 = {1, 2, 3};
    std::vector v2 = {3, 4, 5};
    std::vector v3 = {5, 6, 7};
    Triple t_vec = {v1, v2, v3};
    std::cout << t_vec.getA() << ", " << t_vec.getB() << ", " << t_vec.getC() << ": " << '\n';
    
    
    return 0;
}
