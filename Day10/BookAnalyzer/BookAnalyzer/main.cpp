//
//  main.cpp
//  BookAnalyzer
//
//  Created by Jonathan Pulsipher on 8/29/25.
//

#include <fstream>
#include <iostream>
#include <string>
using namespace std;

int main(int argc, const char * argv[]) {
    string word;

//    string bookName1 = "./The Strange House.txt";
    string bookName1 = "./HeroicAirmenAndTheirExploits.txt";
    
    std::ifstream myBook(bookName1);
    
    while(myBook >> word)
    {
        cout << word << '\n';
    }
    
//    string line;
//    while(getline(myBook, line))
//    {
//        cout << line << '\n';
//    }
    
    myBook.close();
    
    return 0;
}
