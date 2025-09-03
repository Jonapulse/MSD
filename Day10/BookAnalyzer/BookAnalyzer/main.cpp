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
    std::string title = "unknown";
    std::string author = "unknown";
    int wordCount = 0;
    int charCount = 0;
    std::string shortestWord = "";
    std::string longestWord = "";
    vector<string> keywordContext;
    vector<float> keywordPercent;
};

BookInfo getBookInfo(string fileName, string keyword)
{
    std::ifstream myBook(fileName);
    BookInfo bookStats;
    bool collectingKeywordContext = false;
    
    bool readingTitle = false;
    bool readingAuthor = false;
    std:string previousWord = "";
    string word;
    
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
        
        //Check for keywords
        if(word == keyword)
        {
            bookStats.keywordContext.push_back(previousWord + "  " + word);
            bookStats.keywordPercent.push_back(bookStats.wordCount);
            collectingKeywordContext = true;
        } else if (collectingKeywordContext)
        {
            bookStats.keywordContext[bookStats.keywordContext.size() - 1] += " " + word;
            collectingKeywordContext = false;
        }
        
        previousWord = word;
    }
    
    //Convert keyWordPercents to percentage values
    //
    for(int i = 0; i < bookStats.keywordPercent.size(); i++)
        bookStats.keywordPercent[i] = bookStats.keywordPercent[i] / (float)bookStats.wordCount;
    
    myBook.close();
    
    return bookStats;
}

int main(int argc, const char * argv[]) {

//    string bookName1 = "./The Strange House.txt";
    string bookName = "./HeroicAirmenAndTheirExploits.txt";
    string keyWord = "fish";
    
    BookInfo bookStats = getBookInfo(bookName, keyWord);
    
    cout << "Statistics for " << bookStats.title << " by " << bookStats.author
        << "\n\tNumber of words: " << std::to_string(bookStats.wordCount)
        << "\n\tNumber of characters: " << std::to_string(bookStats.charCount)
        << "\n\tThe shortest words is \"" << bookStats.shortestWord << "\", and the longest words is\"" << bookStats.longestWord;
    
    cout << "The word " << keyWord << " appears " << bookStats.keywordContext.size() << " times:\n";
    for(int i = 0; i < bookStats.keywordContext.size(); i++)
    {
        cout << "  at " << bookStats.keywordPercent[i] << "%: \"" << bookStats.keywordContext[i] << "\"";
    }
    
    return 0;
}
