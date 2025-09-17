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
    std::string keyword = "";
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
        // Capture title and author
        //
        if(previousWord == "Title:" || readingTitle)
        {
            readingTitle = true;
            if(bookStats.title == "unknown")
                bookStats.title = word;
            else if (word == "Author:")
                readingTitle = false;
            else
                bookStats.title += " " + word;
        } else if(previousWord == "Author:" || readingAuthor)
        {
            readingAuthor = true;
            
            if(bookStats.author == "unknown")
                bookStats.author = word;
            else if(word == "Release")
                readingAuthor = false;
            else
                bookStats.author += " " + word;
            
        }
        
        if(bookStats.shortestWord == "" || word.size() < bookStats.shortestWord.size())
            bookStats.shortestWord = word;
        else if (bookStats.longestWord == "" || word.size() > bookStats.longestWord.size())
            bookStats.longestWord = word;
        
        bookStats.wordCount++;
        bookStats.charCount += word.size();
        
        //Capture keyword along with the preceding and following word
        //
        bookStats.keyword = keyword;
        if(word == keyword)
        {
            bookStats.keywordContext.push_back(previousWord + " " + word);
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

void printBookInfo(BookInfo bookStats)
{
    cout << "Statistics for " << bookStats.title << " by " << bookStats.author
        << "\n\tNumber of words: " << std::to_string(bookStats.wordCount)
        << "\n\tNumber of characters: " << std::to_string(bookStats.charCount)
        << "\n\tThe shortest words is \"" << bookStats.shortestWord << "\", and the longest words is\"" << bookStats.longestWord << '\n';
    
    cout << "The word " << bookStats.keyword << " appears " << bookStats.keywordContext.size() << " times:\n";
    for(int i = 0; i < bookStats.keywordContext.size(); i++)
    {
        cout << "  at " << bookStats.keywordPercent[i] << "%: \"" << bookStats.keywordContext[i] << "\"\n";
    }
}

int main(int argc, const char * argv[]) {

    //string bookName = "./The Strange House.txt";
    string bookName = "./HeroicAirmenAndTheirExploits.txt";
    string keyword = "whom";
    //string keyword = "fish";//Note: lone among the words I've tested, this one finds nothing. Ah! I'm not recognizing words with attached punctuation. Further refinement would fix this issue as well as give more meaningful longest words (currently most are hyphenated or urls)
    
    printBookInfo(getBookInfo(bookName, keyword));
    
    
    
    return 0;
}
