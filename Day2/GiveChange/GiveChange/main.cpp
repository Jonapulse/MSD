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
    int quarterStock = 2;
    int dimeStock = 2;
    int nickelStock = 2;
    int pennyStock = 2;
    
    cout << "Enter item price in cents:\n";
    cin >> centPrice;
    if(centPrice < 0)
    {
        cout << "Error: Price cannot be negative.\n";
        return 1;
    }
    cout << "Enter amount paid in cents:\n";
    cin >> centsPaid;
    if(centsPaid < 0)
    {
        cout << "Error: Amount paid cannot be negative.\n";
        return 1;
    } else if (centsPaid < centPrice)
    {
        cout << "Insufficient funds for item.\n";
        return 1;
    }
    
    int change = centsPaid - centPrice;
    cout << "Change = " << change << " cents:\n";
    
    int quarters = change / 25;
    if(quarters > 2)
        quarters = 2;
    change -= quarters * 25;
    int dimes = change / 10;
    if(dimes > 2)
        dimes = 2;
    change -= dimes * 10;
    int nickels = change / 5;
    if (nickels > 2)
        nickels = 2;
    change -= nickels * 5;
    int pennies = change;
    if (pennies > 2)
        pennies = 2;
    change -= pennies;
    
    if(change == 0)
    {
        cout << " Quarters: " << quarters << "\n Dimes: " << dimes
            << "\n Nickels: " << nickels << "\n Pennies: " << pennies << "\n";
    }
    else
    {
        cout << " Unable to return change. Out of coins!\n";
        return 1;
    }
    
    
    
    return 0;
}
