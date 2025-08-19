//
//  main.cpp
//  GiveChange
//
//  Created by Jonathan Pulsipher on 8/19/25.
//

#include <iostream>
using namespace std;

int main(int argc, const char * argv[]) {
    
    int centPrice;
    int centsPaid;
    
    cout << "Enter item price in cents:\n";
    cin >> centPrice;
    cout << "Enter amount paid in cents:\n";
    cin >> centsPaid;
    
    int change = centsPaid - centPrice;
    cout << "Change = " << change << " cents:\n";
    
    int quarters = change / 25;
    change -= quarters * 25;
    int dimes = change / 10;
    change -= dimes * 10;
    int nickels = change / 5;
    change -= nickels * 5;
    int pennies = change;
    
    cout << " Quarters: " << quarters << "\n Dimes: " << dimes << "\n Nickels: " << nickels << "\n Pennies: " << pennies << "\n";
    
    return 0;
}
