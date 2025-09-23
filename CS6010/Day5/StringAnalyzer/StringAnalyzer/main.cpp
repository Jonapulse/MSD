//
//  main.cpp
//  StringAnalyzer
//
//  Created by Jonathan Pulsipher on 8/22/25.
//

#include <iostream>
#include <string>
#include "LetterHelper.h"
#include "WordHelper.h"
using namespace std;

//NOTE: I was going back and forth between having this assemble a string or print it. It it better
//"Separation of Concern" to have it like this, creating the string? I was leaning yes but don't know.
string GetStringAnalysis(string s)
{
    if(s == "")
        return "Analysis: You didn't write anything.\n";
    
    string analysisString = "Analysis: \n Number of words: " + to_string(NumWords(s))
        + "\n Number of sentences: " + to_string(NumSentences(s))
        + "\n Number of vowels: " + to_string(NumVowels(s))
        + "\n Number of consonants: " + to_string(NumConsonants(s))
        + "\n Reading level (average word length): " + std::format("{:.5g}", AverageWordLength(s))
        + "\n Average vowels per word: " + std::format("{:.5g}", AverageVowelsPerWord(s))
        + "\n";
    return analysisString;
}

int main(int argc, const char * argv[]) {
    
    /*
     Input: string with assumed restrictions - only letters, spaces, commas, and terminators
     Output behavior: Print analysis, repeating until user inputs "done".
     */
    
    string input;
    
    while(true)    {
        cout << "Enter a string containing one or more sentences: \n";
        getline(cin, input);
        
        if(input != "done")
            cout << GetStringAnalysis(input);
        else
            cout << "Goodbye.\n";
    }
    
    return 0;
}







