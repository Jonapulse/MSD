//
//  main.cpp
//  PoliStructs
//
//  Created by Jonathan Pulsipher on 8/26/25.
//

#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct Politician{
    string name;
    bool isJavacanNotCPluser;
    bool isFederalNotState;
};

vector<Politician> Javacans(vector<Politician> politicians)
{
    vector<Politician> filteredPoliticians;
    for(int i = 0; i < politicians.size(); i++)
        if(politicians[i].isJavacanNotCPluser)
            filteredPoliticians.push_back(politicians[i]);
    return filteredPoliticians;
}

vector<Politician> federalCPlusers(vector<Politician> politicians)
{
    vector<Politician> filteredPoliticians;
    for(int i = 0; i < politicians.size(); i++)
        if((!politicians[i].isJavacanNotCPluser) && politicians[i].isFederalNotState)
            filteredPoliticians.push_back(politicians[i]);
    return filteredPoliticians;
}

int main(int argc, const char * argv[]) {
    
    vector<Politician> testPols = {
        {"Alex Amberson", true, true},
        {"Biha Bobsworth", false, true},
        {"Carl Cowlick", true, true},
        {"Doug Defleppard", false, true},
        {"Edgar Elephurt", true, false},
        {"Finley Finder", false, false},
        {"Gordon Ramsey", true, false}
    };
    
    vector<Politician> filteredPols1 = Javacans(testPols);
    cout << "Javacan politicians:\n";
    for(int i = 0; i < filteredPols1.size(); i++)
        cout << "\t" << filteredPols1[i].name << '\n';
    
    vector<Politician> filteredPols2 = federalCPlusers(testPols);
    cout << "Federal CPluser politicians:\n";
    for(int i = 0; i < filteredPols2.size(); i++)
        cout << "\t" << filteredPols2[i].name << '\n';
    
    
    return 0;
}
