//
//  main.cpp
//  Palindromes
//
//  Created by Jonathan Pulsipher on 8/21/25.
//  Working with Alexis and Tyler

#include <iostream>
#include <string>

int main(int argc, const char * argv[]) {
    
    std::string palCandidate;
    std::cout << "Enter a word to check if it's a palindrome: ";
    std::cin >> palCandidate;
    
    std::string reversed = "";
    for(int i = palCandidate.size() - 1; i >= 0; i--)
        reversed += palCandidate[i];
    
    if(palCandidate == reversed)
        std::cout << "It's a palindrome!\n";
    else
        std::cout << "Not a palindrome.\n";
    
}
