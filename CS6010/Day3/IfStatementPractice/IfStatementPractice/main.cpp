//
//  main.cpp
//  IfStatementPractice
//
//  Created by Jonathan Pulsipher on 8/20/25.
//  Working with Sofia and Badr

#include <iostream>

int main(int argc, const char * argv[]) {
    // Part 1
    //
    int age;
    std::cout << "Provide your age: ";
    std::cin >> age;
    
    if (age >= 18)
        std::cout << "You are old enough to vote! I'm sorry.\n";
    else
        std::cout << "You are not old enough to vote.\n";
    
    if (age >= 30)
        std::cout << "You are old enough to run for senate. Don't.\n";
    else
        std::cout << "You are not old enough to run for senate.\n";
    
    if (age > 80)
        std::cout << "You are part of the greatest generation.\n";
    else if (age > 60)
        std::cout << "Okay, boomer.\n";
    else if (age > 40)
        std::cout << "You are part of Generation X.\n";
    else if (age > 20)
        std::cout << "You are a millenial.\n";
    else
        std::cout << "You are... an iKid? (Gen Z)\n";
     
    // Part 2
    //
    char mIsWeekday, mIsHoliday, mHasYoungChildren; //Is this correct according to http://www.geeksforgeeks.org/naming-convention-in-c
    std::cout << "Is it a Weekday (Y/N)? ";
    std::cin >> mIsWeekday;
    std::cout << "Is it a Holiday (Y/N)? ";
    std::cin >> mIsHoliday;
    std::cout << "Do you have children (Y/N)? ";
    std::cin >> mHasYoungChildren;
    
    if((mIsWeekday == 'Y' || mIsHoliday == 'Y') && !mHasYoungChildren)
        std::cout << "You can sleep in today!\n";
    else
        std::cout << "Sorry, you cannot sleep in today.\n";
    
    return 0;
}
