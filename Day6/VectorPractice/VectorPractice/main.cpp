//
//  main.cpp
//  VectorPractice
//
//  Created by Jonathan Pulsipher on 8/25/25.
//

#include <iostream>
#include <vector>
#include <string>

using namespace std;

int sum(vector<int> values)
{
    int sum = 0;
    for(int i = 0; i < values.size(); i++)
        sum += values[i];
    
    return sum;
}

vector<char> stringToVec(string convertStr){
    vector<char> charVec;
    for(int i = 0; i < convertStr.length(); i++)
        charVec.push_back(convertStr[i]);
    return charVec;
}

vector<int> reverse(vector<int> vec)
{
    vector<int> reversedVec;
    for(int i = vec.size() - 1; i >= 0; i--)
        reversedVec.push_back(vec[i]);
    return reversedVec;
}

int main(int argc, const char * argv[]) {
    //Test Code
    //
    vector<int> vecSumIs35 = {5, 5, 10, 8, 7};
    cout << "Sum should be 35: " << sum(vecSumIs35) << '\n';
    
    string testStr = "Test string";
    vector<char> testCharVec = {'T', 'e', 's', 't', ' ', 's', 't', 'r', 'i', 'n', 'g'};
    
    for (int i = 0; i < testCharVec.size(); i++){
        cout << testCharVec[i];
    }
    cout << '\n';
    vector<char> compareVecChar = stringToVec(testStr);
    for (int i = 0; i < compareVecChar.size(); i++){
        cout << compareVecChar[i];
    }
    cout << '\n';
    
    vector<int> ascendingVec = {1, 2, 3, 4, 5, 6, 7};
    vector<int> reversedVec = reverse(ascendingVec);
    for(int i = 0; i < reversedVec.size(); i++)
        cout << reversedVec[i] << ",";
    cout << "and we're done.\n";
    
    return 0;
}

