//
//  main.cpp
//  RomanNumerals
//
//  Created by Jonathan Pulsipher on 8/21/25.
//  Working with Sofia and Tyler

#include <iostream>

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
    
    monthDigits = inputDate.substr(0, 2);
    dayDigits = inputDate.substr(3, 2);
    yearDigits = inputDate.substr(6, 4);
              
    if(monthDigits == "01")
        monthName = "January";
    else if(monthDigits == "02")
        monthName = "February";
    else if(monthDigits == "03")
        monthName = "March";
    else if(monthDigits == "04")
        monthName = "April";
    else if(monthDigits == "05")
        monthName = "May";
    else if(monthDigits == "06")
        monthName = "June";
    else if(monthDigits == "07")
        monthName = "July";
    else if(monthDigits == "08")
        monthName = "August";
    else if(monthDigits == "09")
        monthName = "September";
    else if(monthDigits == "10")
        monthName = "October";
    else if(monthDigits == "11")
        monthName = "November";
    else if(monthDigits == "12")
        monthName = "December";
    
    std::cout << monthName + " " + dayDigits + ", " + yearDigits + "\n";
    
}
