//
//  main.cpp
//  DIYVector
//
//  Created by Jonathan Pulsipher on 9/9/25.
//

#include <iostream>
#include <cassert>
#include "Vector.h"

int main(int argc, const char * argv[]) {
    
    Vector testVec = makeVector(2);
    assert(testVec.capacity == 2);
    
    pushBack(testVec, 1);
    assert(get(testVec, 0) == 1);
    pushBack(testVec, 2);
    assert(get(testVec, 1) == 2);
    pushBack(testVec, 3);
    assert(get(testVec, 2) == 3);
    
    //std::cout << get(testVec, 0) << "," << get(testVec, 1) << "," << get(testVec, 2) << '\n';

    //Make sure they're still equal -- b4 this test a call to growvector was destroying values
    assert(get(testVec, 0) == 1);
    assert(get(testVec, 1) == 2);
    assert(get(testVec, 2) == 3);

    
    //Check that it's grown
    assert(testVec.capacity == 4);
    
    
    set(testVec, 1, 20);
    
    assert(get(testVec, 1) == 20);
        
    //std::cout << popBack(testVec) << '\n' << popBack(testVec) << '\n' << popBack(testVec) << '\n';
    assert(popBack(testVec) == 3);
    assert(popBack(testVec) == 20);
    assert(popBack(testVec) == 1);
    
    freeVector(testVec);
    
    return 0;
}
