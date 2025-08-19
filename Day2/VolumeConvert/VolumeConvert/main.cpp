//
//  main.cpp
//  VolumeConvert
//
//  Created by Jonathan Pulsipher on 8/19/25.
//

#include <iostream>
using namespace std; 

int main(int argc, const char * argv[]) {
    double oz;
    
    cout << "Enter volume in ounces:\n";
    cin >> oz;
    
    cout << "Ounces: " << oz << "\nCups: " << oz / 8 << "\nPints: " << oz / 16 << "\nGallons: "
    << oz / 128 << "\nLiters: " << oz * 0.0296 << "\nCubic Inches: " << oz * 1.8 << "\n";
    
    return 0;
}
