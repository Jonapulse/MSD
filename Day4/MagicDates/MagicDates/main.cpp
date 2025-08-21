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
    
    //Copying inputDate for destructive removal of date info to maintain a copy of the original input
    //
    std::string inputDateCopy = inputDate;
    monthDigits = inputDateCopy.substr(0, inputDateCopy.find('/'));
    inputDateCopy = inputDateCopy.substr(inputDateCopy.find('/') + 1);
    dayDigits = inputDateCopy.substr(0, inputDateCopy.find('/'));
    inputDateCopy = inputDateCopy.substr(inputDateCopy.find('/') + 1);
    yearDigits = inputDateCopy;
    
    //Error checking (allows single digit entry for days and months)
    //
    if(monthDigits.length() == 0 || monthDigits.length() > 2 || std::stoi(monthDigits) > 12)
    {
        std::cout << "ERROR: Invalid value entered for month.\n";
        return 1;
    }
    //NOTE: Will accept some invalid days 29-31
    if(dayDigits.length() == 0 || dayDigits.length() > 2 || std::stoi(dayDigits) > 31)
    {
        std::cout << "ERROR: Invalid value entered for day.\n";
        return 1;
    }
    //NOTE: Will accept any 4-digit year.
    if(yearDigits.length() != 4)
    {
        std::cout << "ERROR: Invalid value entered for year.\n";
        return 1;
    }
    
    int month = std::stoi(monthDigits);
    int day = std::stoi(dayDigits);
    int yearFinalDigits = std::stoi(yearDigits.substr(2));
    
    
    if(month * day == yearFinalDigits)
        std::cout << inputDate << " IS a magic date!\n";
    else
        std::cout << inputDate << " is NOT a magic date.\n";
}
