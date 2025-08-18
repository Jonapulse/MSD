//
//  main.cpp
//  lecture1program
//
//  Created by Jonathan Pulsipher on 8/18/25.
//

#include <iostream>

int main(int argc, const char * argv[]){
    double number1;
    double number2;
    
    // insert code here...
    std::cout << "Hello, Whirled!\n";
    
    std::cout << "Enter a number:\n";
    std::cin >> number1;
    
    std::cout << "Enter another:\n";
    std::cin >> number2;
    
    std::cout << "The sum of these numbers is " << (number1 + number2) << "\n";
    
    return 0;
};
