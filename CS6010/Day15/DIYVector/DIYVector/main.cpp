//
//  main.cpp
//  DIYVector
//
//  Created by Jonathan Pulsipher on 9/9/25.
//

#include <iostream>
#include <cassert>
#include <string>
#include <algorithm>
#include <numeric>
#include "Vector.h"

bool is_even(int num)
{
    return num % 2 == 0;
}

int main(int argc, const char * argv[]) {
    
    Vector<int> testVec {2};
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
    
    assert(testVec[1] == 20);
    testVec[2] = 21;
    assert(testVec[2] == 21);
        
    //std::cout << popBack(testVec) << '\n' << popBack(testVec) << '\n' << popBack(testVec) << '\n';
    assert(testVec.popBack() == 21);
    assert(testVec.popBack() == 20);
    assert(testVec.popBack() == 1);
    
    Vector<std::string> testVecString{10};
    testVecString.pushBack("Hello");
    std::cout << testVecString[0] << '\n';
    
    Vector<int> compareIntA {4};
    compareIntA.pushBack(9);
    compareIntA.pushBack(9);
    compareIntA.pushBack(4);
    compareIntA.pushBack(15);
    
    Vector<int> compareIntB {4};
    compareIntB.pushBack(9);
    compareIntB.pushBack(9);
    compareIntB.pushBack(10);
    compareIntB.pushBack(12);

    assert(compareIntA == compareIntA);
    assert(compareIntA != compareIntB);
    assert(compareIntA < compareIntB);
    assert(compareIntA <= compareIntB);
    assert(!(compareIntA == compareIntB));
    assert(!(compareIntA > compareIntB));
    assert(!(compareIntA >= compareIntB));
    
    compareIntB[2] = 4;
    compareIntB[3] = 15;
    
    assert(compareIntA == compareIntB);
    assert(!(compareIntA != compareIntB));
    assert(!(compareIntA < compareIntB));
    assert(compareIntA <= compareIntB);
    
    for(int n : compareIntA)
        std::cout << n << '\n';
    
    std::sort(compareIntA.begin(),compareIntA.end());
    for(int n : compareIntA)
        std::cout << n << '\n';
    
    int min_element = *std::min_element(compareIntA.begin(), compareIntA.end());
    int sum = std::accumulate(compareIntA.begin(), compareIntA.end(), 0);
    int evenCount = std::count_if(compareIntA.begin(), compareIntA.end(), is_even);
    std::cout << "Min int is: " << min_element << '\n';
    std::cout << "Sum is: " << sum << '\n';
    std::cout << "Even count is: " << evenCount << '\n';
    return 0;
}
