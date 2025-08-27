//
//  main.cpp
//  Cards
//
//  Created by Jonathan Pulsipher on 8/26/25.
//

#include <iostream>
#include "Cards.h"

int main(int argc, const char * argv[]) {
    
    InitializeDeck();
    Card draw = Draw();
    std::cout << "We drew a " + To_StringCard(draw);
    
    //Code review: Could make a "hand" struct. Communicates more meaning. Has more utility, like comparing hands to find winner.
    
    return 0;
}
