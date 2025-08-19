//
//  main.cpp
//  RoadTripCalculator
//
//  Created by Jonathan Pulsipher on 8/19/25.
//

#include <iostream>
using namespace std;

int main(int argc, const char * argv[]) {
    
    int distance;
    float mpg;
    float costPerGallon;
    
    cout << "Welcome to RoadTripCalculator!\nHow many miles are you driving?\n";
    cin >> distance;
    cout << "What is the mpg of your vehicle?\n";
    cin >> mpg;
    cout << "What is the cost of a gallon of gas?\n";
    cin >> costPerGallon;
    
    float gallonsUsed = distance / mpg;
    float fullCost = gallonsUsed * costPerGallon;
    
    cout << "Your trip will cost you $" << fullCost << ".\n ...but it will cost Mother Nature much more...\n";
    
    return 0;
}
