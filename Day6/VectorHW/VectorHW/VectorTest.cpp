
/*
  Author: Daniel Kopta and ??
  July 2017
  
  CS 6010 Fall 2019
  Vector util library tests

  Compile this file together with your VectorUtil library with the following command:
  clang++ -std=c++11 VectorTest.cpp VectorUtil.cpp

  Most of the provided tests will fail until you have provided correct
  implementations for the VectorUtil library functions.

  You will need to provide more thorough tests.
*/

#include <iostream>
#include <string>

// Include the VectorUtil library
#include "VectorUtil.h"

/*
 * Helper function for failing a test.
 * Prints a message and exits the program.
 */
void ErrorExit( std::string message )
{
  std::cerr << "Failed test: " << message << std::endl;
  exit(1); // Causes the entire program to exit.
}


int main()
{
  
  // Set up some input vectors for testing purposes.

  // We can use list initialization syntax:
  vector<int> v1 = {3, 1, 0, -1, 5};

  // Or we can repeatedly push_back items
  vector<int> v2;
  v2.push_back(1);
  v2.push_back(2);
  v2.push_back(3);

  // When testing, be sure to check boundary conditions, such as an empty vector
  vector<int> empty;
  
  
  /*
   * Contains tests
   */

  // v1 doesn't contain 4, so this should return false
  if( Contains(v1, 4) ) {
    ErrorExit( "Contains() - test 1" );
  }

  // v1 does contain -1, so this should return true
  if(!Contains(v1, -1)) {
    ErrorExit("Contains() - test 2");
  }

  /*
   * The vector 'empty' doesn't contain anything, so this should return false
   * The specific value we're looking for here (99) is not important in this test.
   * This test is designed to find any general errors caused by the array being empty.
   * That type of error is unlikely to depend on the value we are looking for.
  */
  if( Contains(empty, 99) ) {
    ErrorExit("Contains() - empty");
  }
  
  /*
   * Testing for FindMin
   */
    vector<int> vMinSimple = {1,2,3};
    vector<int> vMinSimple2 = {8,3,2,189,3,3,8};
    vector<int> vMinNegative = {-2, -10, -3, -4};
    vector<int> vMinDuplicate = {3, 3, 3, 5, 5};
    ///vector<int> vMinEmpty = {};// Skip this test because we assume input is non-empty
    int testVar;
    
    testVar = FindMin(vMinSimple);
    if(testVar != 1))
    {
        ErrorExit("FindMin() - test 1, " + testVar + " != 1");
    }
    
    testVar = FindMin(vMinSimple2);
    if(testVar != 2))
    {
        ErrorExit("FindMin() - test 2, " + testVar + " != 2");
    }
    
    testVar = FindMin(vMinNegative);
    if(testVar != -10))
    {
        ErrorExit("FindMin() - test 3, " + testVar + " != -10");
    }
    
    testVar = FindMin(vMinDuplicate);
    if(testVar != 3))
    {
        ErrorExit("FindMin() - test 4, " + testVar + " != 1");
    }
    
    
    /*
     * Testing for FindMax
     */
    vector<int> vMaxSimple = {1, 2, 3};
    vector<int> vMaxSimple2 = {8, 3, 2, 189, 3, 3, 8};
    vector<int> vMaxNegative = {-2, -10, -3, -4};
    vector<int> vMaxDuplicate = {3, 3, 5, 5, 5};
    
    testVar = FindMax(vMaxSimple);
    if(testVar != 3))
    {
        ErrorExit("FindMax() - test 1, " + testVar + " != 3");
    }
    
    testVar = FindMax(vMaxSimple2);
    if(testVar != 189))
    {
        ErrorExit("FindMax() - test 2, " + testVar + " != 189");
    }
    
    testVar = FindMax(vMaxNegative);
    if(testVar != -2))
    {
        ErrorExit("FindMax() - test 3, " + testVar + " != -2");
    }
    
    testVar = FindMax(vMaxDuplicate);
    if(testVar != 5))
    {
        ErrorExit("FindMax() - test 4, " + testVar + " != 5");
    }

    /*
     * Testing for Average
     */
    
    vector<int> vAverageSimple = {1, 2, 3};
    vector<int> vAverageSimpleRoundDown = {4, 5, 6, 7};
    vector<int> vAverageNegative = {-1, -2, -3};
    vector<int> vAverageNegativeRoundDown = {-1, -2, -3, -4};
    vector<int> vAverageDuplicate = {3, 3, 3, 3};
    
    testVar = Average(vAverageSimple);
    if(testVar != 2))
    {
        ErrorExit("Average() - test 1, " + testVar + " != 2");
    }
    
    testVar = Average(vAverageSimpleRoundDown);
    if(testVar != 5))
    {
        ErrorExit("Average() - test 2, " + testVar + " != 5");
    }
    
    testVar = Average(vAverageNegative);
    if(testVar != -2))
    {
        ErrorExit("Average() - test 3, " + testVar + " != -2");
    }
    
    testVar = Average(vAverageNegativeRoundDown);
    if(testVar != -3))
    {
        ErrorExit("Average() - test 4, " + testVar + " != -3");
    }
    
    testVar = Average(vAverageDuplicate);
    if(testVar != 3))
    {
        ErrorExit("Average() - test 5, " + testVar + " != 3");
    }
    
    /*
     * Testing for IsSorted
     */
    vector<int> vIsSortSimpleTrue = {1, 2, 3};
    vector<int> vIsSortSimpleFalse = {2,1,3};
    vector<int> vIsSortNegativeTrue = {-10, -9, -8, -6, 7};
    vector<int> vIsSortNegativeFalse = {-10, -9, -8, 7, -6}
    vector<int> vIsSortDuplicateTrue = {1, 2, 2, 2, 2, 3, 3};
    vector<int> vIsSortDuplicateFalse = {1, 2, 2, 2, 3, 2, 3}
    bool testBool;
    
    testBool = IsSorted(vIsSortSimpleTrue);
    if(testBool != true))
    {
        ErrorExit("IsSorted() - test 1, should be true but is false);
    }
    
    testBool = IsSorted(vIsSortSimpleFalse);
    if(testBool != false))
    {
        ErrorExit("IsSorted() - test 2, should be false but is true);
    }
    
    testBool = IsSorted(vIsSortNegativeTrue);
    if(testBool != true))
    {
        ErrorExit("IsSorted() - test 3, should be true but is false);
    }
    
    testBool = IsSorted(vIsSortNegativeFalse);
    if(testBool != false))
    {
        ErrorExit("IsSorted() - test 4, should be false but is true);
    }
    
    testBool = IsSorted(vIsSortDuplicateTrue);
    if(testBool != true))
    {
        ErrorExit("IsSorted() - test 5, should be true but is false);
    }
    
    testBool = IsSorted(vIsSortDuplicateFalse);
    if(testBool != false))
    {
        ErrorExit("IsSorted() - test 2, should be false but is true);
    }


  std::cout << "All tests passed!\n";
    
}
