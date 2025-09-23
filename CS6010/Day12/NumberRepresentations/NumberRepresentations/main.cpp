//
//  main.cpp
//  NumberRepresentations
//
//  Created by Jonathan Pulsipher on 9/3/25.
//

#include <iostream>
#include <fstream>
#include <cstdint>
#include <cassert>
#include <cmath>
#include <string>
using namespace std;

void printCharFile(const string fileName)
{
    std::ifstream charfile("./" + fileName);
    
    char c;

    const int ASCII_LIMIT = 127;
    int asciiCount = 0;
    int unicodeCount = 0;
    while( charfile >> c ){
        std::cout << c << '\n';
        if (c > 0 && c <= ASCII_LIMIT)
            asciiCount++;
        else
            unicodeCount++;
    }
    
    std::cout << fileName << " has " << asciiCount << " ascii characters and " << unicodeCount << " unicode characters.";
}

bool approxEquals( double a, double b, double tolerance)
{
    return abs(a - b) < tolerance;
}

int main(int argc, const char * argv[]) {

//    cout << sizeof(char) << '\n';
//    int x;
//    cout << sizeof(int) << '\n';
//    cout << sizeof(x) << '\n';
//    x = 10;
//    cout << sizeof(x) << '\n';
//    
//    int8_t x8t = 121;
//    cout << sizeof(x8t) << '\n';
//    cout << x8t << '\n';
//    
//    uint16_t u16t = 3;
//    cout << sizeof(u16t) <<'\n';
//    
//    x8t = 0b01111111;
//    cout << "8 bit max: " << (int)x8t << '\n';
//    x8t++;
//    cout << "8 bit max + 1: " << (int)x8t << '\n';
//    x8t = 0x7f; // 7 * 16 + 15 = 127
//    cout << "8 bit max w/ hex: " << (int)x8t << '\n';
//    x8t = 0b10000000;
//    cout << "8 bit min: " << (int)x8t << '\n';
//    x8t = 0x80;
//    cout << "8 bit min w/ hex: " << (int)x8t << '\n';
//    int32_t x32t = 0x7fffffff;
//    cout << "32-bit int max " << (int) x32t << '\n';
//    int64_t x64t = 0x7fffffffffffffff;
//    cout << "64-bit int max " << x64t << '\n';
//    
//    double floatTest = 0.1 + 0.2;
//    cout << "My double is: " << floatTest << '\n';
//    assert(floatTest != 0.3f); //does not equal with assignment written as is
//    floatTest = 0.1f + 0.2f;
//    assert(floatTest == 0.3f); //does equal with assignment written as is
//    assert(approxEquals(0.1, 0.2f, 3) == true);
    
    string checkStr = "Helloblahblahblahblahblahblahblahblahblahblah";
    cout << "Size of: " << sizeof(checkStr) << " and .size() " << checkStr.size();
    
    //printCharFile("UTF-8-demo.txt");
    
    cout << '\n';
    return 0;
}
