//
//  main.cpp
//  BookAnalyzer
//
//  Created by Jonathan Pulsipher on 8/29/25.
//

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct BookInfo
{
    std::string title = "";
    std::string author = "";
    int wordCount = 0;
    int charCount = 0;
    std::string shortestWord = "";
    std::string longestWord = "";
    vector<string> keywordContext;
    vector<float> keywordPercent;
}

int main(int argc, const char * argv[]) {
    string word;

//    string bookName1 = "./The Strange House.txt";
    string bookName1 = "./HeroicAirmenAndTheirExploits.txt";
    
    std::ifstream myBook(bookName1);
    BookInfo bookStats;
    
    bool readingTitle = false;
    bool readingAuthor = false;
    std:string previousWord = "";
    
    while(myBook >> word)
    {
        if(word == "Title:")
        {
            readingTitle = true;
        }
        else if (word == "Author")
        {
            readingTitle = false;
            readingAuthor = true;
        }
        else if (word == "ReleasedDate")
        {
            readingAuthor = false;
        }
        
        if(readingTitle)
        {
            bookStats.title += word;
        } else if(readingAuthor)
        {
            bookStats.author += word;
        }
        
        if(bookStats.shortestWord == "" || word.size() < bookStats.shortestWord.size())
            bookStats.shortestWord = word;
        else if (bookStats.longestWord == "" || word.size() > bookStats.longestWord.size())
            bookStats.longestWord = word;
        
        bookStats.wordCount++;
        bookStats.charCount += word.size();
        
        
    }
    
//    string line;
//    while(getline(myBook, line))
//    {
//        cout << line << '\n';
//    }
    
    myBook.close();
    
    return 0;
}
