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
    
    Vector testVec {2};
    assert(testVec.GetCapacity() == 2);
    
    testVec.pushBack(1);
    assert(testVec.get(0) == 1);
    testVec.pushBack(2);
    assert(testVec.get(1) == 2);
    testVec.pushBack(3);
    assert(testVec.get(2) == 3);
    
    //Make sure they're still equal -- b4 this test a call to growvector was destroying values
    assert(testVec.get(0) == 1);
    assert(testVec.get(1) == 2);
    assert(testVec.get(2) == 3);

    
    //Check that it's grown
    assert(testVec.GetCapacity() == 4);
    
    
    testVec.set(1, 20);
    
    assert(testVec.get(1) == 20);
        
    //std::cout << popBack(testVec) << '\n' << popBack(testVec) << '\n' << popBack(testVec) << '\n';
    assert(testVec.popBack() == 3);
    assert(testVec.popBack() == 20);
    assert(testVec.popBack() == 1);
        
    return 0;
}
