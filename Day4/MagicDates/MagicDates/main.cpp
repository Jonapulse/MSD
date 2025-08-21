//
//  main.cpp
//  MagicDates
//
//  Created by Jonathan Pulsipher on 8/21/25.
//

#include <iostream>

int main(int argc, const char * argv[]) {
    /* Checking for day * month == last 2 digits of year
     */
    
    std::string inputDate;
    std::string monthDigits;
    std::string dayDigits;
    std::string yearDigits;
    std::string monthName;
    
    std::cout << "Please input a date (mm/dd/yyyy) to discover if it is... MAGIC...";
    std::cin >> inputDate;
    
    std::string inputDateCopy = inputDate;
    //We will harvest the leading value and then remove it from the input string at '/'
    monthDigits = inputDateCopy.substr(0, inputDate.find('/'));
    inputDateCopy = inputDateCopy.substr(inputDate.find('/') + 1);
    dayDigits = inputDateCopy.substr(0, inputDate.find('/'));
    inputDateCopy = inputDateCopy.substr(inputDate.find('/') + 1);
    yearDigits = inputDateCopy;
    
    int month = std::stoi(monthDigits);
    int day = std::stoi(dayDigits);
    int yearFinalDigits = std::stoi(yearDigits.substr(2));
    
    
    if(month * day == yearFinalDigits)
        std::cout << inputDate << " IS a magic date!\n";
    else
        std::cout << inputDate << " is NOT a magic date.\n";
}
