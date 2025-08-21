//
//  main.cpp
//  RomanNumerals
//
//  Created by Jonathan Pulsipher on 8/21/25.
//  Working with Sofia and Tyler

#include <iostream>
#include <string>
using namespace std;

int main(int argc, const char * argv[]) {
    
    /*
     Input: int number
     Output: string Roman Numeral
     */
    
    string romanNum;
    
    int inputNum;
    cout << "Enter a number to Romanticize (convert to Roman Numeral):  ";
    cin >> inputNum;
    
    if(inputNum <= 0)
    {
        cout << "Error: The romans didn't have a concept for that number. They've probably figured out that your a time traveler. RUN!\n";
        return 1;
    }
    
    // Walk down roman numerals from highest to lowest, subtracting them from inputNum while adding that numeral to romanNum until inputNum reaches zero
    //
    while (inputNum >= 1000)
    {
        inputNum -= 1000;
        romanNum += "M";
    }
    while (inputNum >= 900)
    {
        inputNum -= 900;
        romanNum += "CM";
    }
    while (inputNum >= 500)
    {
        inputNum -= 500;
        romanNum += "D";
    }
    while (inputNum >= 400)
    {
        inputNum -= 400;
        romanNum += "CD";
    }
    while (inputNum >= 100)
    {
        inputNum -= 100;
        romanNum += "C";
    }
    while (inputNum >= 90)
    {
        inputNum -= 90;
        romanNum += "XC";
    }
    while (inputNum >= 50)
    {
        inputNum -= 50;
        romanNum += "L";
    }
    while (inputNum >= 40)
    {
        inputNum -= 40;
        romanNum += "XL";
    }
    while (inputNum >= 10)
    {
        inputNum -= 10;
        romanNum += "X";
    }
    while (inputNum >= 9)
    {
        inputNum -= 9;
        romanNum += "IX";
    }
    while (inputNum >= 5)
    {
        inputNum -= 5;
        romanNum += "V";
    }
    while (inputNum >= 4)
    {
        inputNum -= 4;
        romanNum += "IV";
    }
    while (inputNum >= 1)
    {
        inputNum -= 1;
        romanNum += "I";
    }
    
    cout << "Roman numeral version:\n " << romanNum << '\n';
    
}
