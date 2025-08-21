//
//  main.cpp
//  DateFormats
//
//  Created by Jonathan Pulsipher on 8/21/25.
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
    
    std::string inputDateCopy = inputDate;
    //We will harvest the leading value and then remove it from the input string at '/'
    monthDigits = inputDateCopy.substr(0, inputDate.find('/'));
    inputDateCopy = inputDateCopy.substr(inputDate.find('/') + 1);
    dayDigits = inputDateCopy.substr(0, inputDate.find('/'));
    inputDateCopy = inputDateCopy.substr(inputDate.find('/') + 2); //I'm sad about it being +2... I don't know why. It was +1 beforehand.
    std::cout << inputDateCopy << '\n';
    yearDigits = inputDateCopy;
              
    if(monthDigits == "01" || monthDigits == "1")
        monthName = "January";
    else if(monthDigits == "02" || monthDigits == "1")
        monthName = "February";
    else if(monthDigits == "03" || monthDigits == "2")
        monthName = "March";
    else if(monthDigits == "04" || monthDigits == "3")
        monthName = "April";
    else if(monthDigits == "05" || monthDigits == "4")
        monthName = "May";
    else if(monthDigits == "06" || monthDigits == "5")
        monthName = "June";
    else if(monthDigits == "07" || monthDigits == "6")
        monthName = "July";
    else if(monthDigits == "08" || monthDigits == "7")
        monthName = "August";
    else if(monthDigits == "09" || monthDigits == "8")
        monthName = "September";
    else if(monthDigits == "10" || monthDigits == "9")
        monthName = "October";
    else if(monthDigits == "11")
        monthName = "November";
    else if(monthDigits == "12")
        monthName = "December";
    
    std::cout << monthName + " " + dayDigits + ", " + yearDigits + "\n";
}
