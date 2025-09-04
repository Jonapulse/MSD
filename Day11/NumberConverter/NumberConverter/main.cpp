//
//  main.cpp
//  NumberConverter
//
//  Created by Jonathan Pulsipher on 9/3/25.
//

#include <iostream>
#include <string>
#include <cassert>

/*
 * Helper function for failing a test.
 * Prints a message and exits the program.
 */
void ErrorExit( std::string message )
{
  std::cerr << message << std::endl;
  exit(1); // Causes the entire program to exit.
}

// Returns a char converted to an int up to the max hex value of '15'.
//
int convertCharToDigit(char c)
{
    int convertedValue = c - '0';
    if(convertedValue >= 0 && convertedValue <= 9)
        return convertedValue;
    //Check lower-case hexes
    convertedValue = c - 'a' + 10;
    if(convertedValue >= 10 && convertedValue <= 15)
        return convertedValue;
    //Check upper-case hexes
    convertedValue = c - 'A' + 10;
    if(convertedValue >= 10 && convertedValue <= 15)
        return convertedValue;
    
    ErrorExit("Invalid char sent to convertCharToDigit: " + std::to_string(c));
    return -1; //Nonsense value to stop compiler from complaining. Is there a better way? It can't reach here.
}

// Returns values up to 15 as chars representing 15 as "F"
//
char convertDigitToChar(int d)
{
    if(d >= 0 && d <= 9)
        return '0' + d;
    else if(d <= 15)
        return 'A' + (d - 10);
    
    ErrorExit("Invalid int sent to convertDigitToChar: " + std::to_string(d));
    return -1; //Nonsense value to stop compiler from complaining. Is there a better way? It can't reach here.
}

// Convert binary base to int of specified base
//
int stringToInt(std::string binaryStr, int base, bool isSignedInt)
{
    int convertedIntSoFar = 0;
    int runningPower = 1;
    for(int i = binaryStr.size() - 1; i >= 0; i--)
    {
        //if signed, treat left-most int as negative flag
        if(isSignedInt && i == 0){
            if(binaryStr[i] == '1')
                convertedIntSoFar = -runningPower + convertedIntSoFar;
        }
        else
        {
            convertedIntSoFar += convertCharToDigit(binaryStr[i]) * runningPower;
            runningPower *= base;
        }
    }
    return convertedIntSoFar;
}

//Convert int to string representation of specific base
//
std::string intToString(int num, int base, bool isSignedInt)
{
    //While num > 0, we attempt to subtract the largest power of the base that is smaller than num.
    int smallestPowerOfBaseBeneathNum = 1;
    while(smallestPowerOfBaseBeneathNum * base < num)
        smallestPowerOfBaseBeneathNum *= base;
    
    std::string convertedStringSoFar = "";
    while(smallestPowerOfBaseBeneathNum >= 1)
    {
        int digitsOfThisPower = 0;
        while(smallestPowerOfBaseBeneathNum <= num){
            digitsOfThisPower += 1;
            num -= smallestPowerOfBaseBeneathNum;
        }
        convertedStringSoFar += convertDigitToChar(digitsOfThisPower);
        
        if(smallestPowerOfBaseBeneathNum > 1)
            smallestPowerOfBaseBeneathNum /= base;
        else break;
    }
    
    return convertedStringSoFar;
}

void runConversionTests()
{
    // String to Int
    //
    assert(stringToInt( "99" , 10, false ) == 99); // Converts "99" from a decimal number (in string form) to the integer value 99

    assert(stringToInt( "1100", 2, false) == 12); // Converts "1100" from a string of binary digits to the integer 12

    assert(stringToInt( "FF", 16, false ) == 255); // Converts "FF" from a string of hex digits to the integer value 255 (expressed here in decimal)
    
    assert(stringToInt("11111111", 2, false) == 255); //Converts unsigned "11111111" to 255
        
    assert(stringToInt("11111111", 2, true) == -1);
    
    // Int to String
    //
    assert(intToString(99, 10, false) == "99");
    
    assert(intToString( 12, 2, false) == "1100");

    assert(intToString( 255, 16, false ) == "FF");
    
    assert(intToString(255, 2, false) == "11111111");
        
    assert(intToString(-1, 2, true) == "11111111");
}

int main(int argc, const char * argv[]) {
    
    runConversionTests();
    
    
    
    return 0;
}
