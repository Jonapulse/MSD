//
//  main.cpp
//  DateFormats
//
//  Created by Jonathan Pulsipher on 8/21/25.
//  Working with Alexis and Tyler (some cont'd work separately after class)
//

#include <iostream>
#include <string>

int main(int argc, const char * argv[]) {
    
    /* Input: string, mm/dd/yyyy
       Output: string, month(written) dd, yyyy
     */
    
    std::string inputDate;
    std::string monthDigits;
    std::string dayDigits;
    std::string yearDigits;
    std::string monthName;
    
    std::cout << "Please input a date (mm/dd/yyyy) to convert to (month dd, yyyy): ";
    std::cin >> inputDate;
    
    //Copying inputDate for destructive remova0l of date info to maintain a copy of the original input
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
    
    //Converting month number to written month
    //
    if(monthDigits == "01" || monthDigits == "1")
        monthName = "January";
    else if(monthDigits == "02" || monthDigits == "2")
        monthName = "February";
    else if(monthDigits == "03" || monthDigits == "3")
        monthName = "March";
    else if(monthDigits == "04" || monthDigits == "4")
        monthName = "April";
    else if(monthDigits == "05" || monthDigits == "5")
        monthName = "May";
    else if(monthDigits == "06" || monthDigits == "6")
        monthName = "June";
    else if(monthDigits == "07" || monthDigits == "7")
        monthName = "July";
    else if(monthDigits == "08" || monthDigits == "8")
        monthName = "August";
    else if(monthDigits == "09" || monthDigits == "9")
        monthName = "September";
    else if(monthDigits == "10")
        monthName = "October";
    else if(monthDigits == "11")
        monthName = "November";
    else if(monthDigits == "12")
        monthName = "December";
    
    std::cout << monthName + " " + dayDigits + ", " + yearDigits + "\n";
}
