//
//  main.cpp
//  Gradebook
//
//  Created by Tyler Han and Jon Pulsipher on 8/19/25.
//

#include <iostream>
using namespace std;

int main(int argc, const char * argv[]) {
    
    float g1, g2, g3, g4, g5;
    cout << "Enter 5 assignment scores:\n";
    cin >> g1 >> g2 >> g3 >> g4 >> g5;
    float res = (g1 + g2 + g3 + g4 + g5) / 5;
    cout << "Average: " << res << "\n";
    
    
    return 0;
}
