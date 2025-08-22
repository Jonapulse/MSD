//
//  main.cpp
//  StringAnalyzer
//
//  Created by Jonathan Pulsipher on 8/22/25.
//

#include <iostream>
#include <string>
using namespace std;

bool IsTerminator(char c)
{
    return c == '.' || c == '?' || c == '!';
}

bool IsPunctuation(char c)
{
    return IsTerminator(c) || c == ',';
}

bool IsVowel(char c)
{
    return c == 'a' || c == 'A' || c == 'e' || c == 'E' || c == 'i' || c == 'I'
        || c == 'o' || c == 'O' || c == 'u' || c == 'U' || c == 'y' || c == 'Y';
}

bool isConsonant(char c)
{
    return !(IsPunctuation(c) || IsVowel(c) || c == ' ');
}

int NumWords(string s)
{
    int spaceCount = 0;
    for(int i = 0; i < s.length(); i++)
    {
        if(s[i] == ' ')
            spaceCount++;
    }
    return spaceCount + 1;
}

int NumSentences(string s)
{
    int terminatorCount = 0;
    for(int i = 0; i < s.length(); i++)
    {
        if(IsTerminator(s[i]))
            terminatorCount++;
    }
    return terminatorCount;
}

int NumVowels(string s)
{
    int vowelCount = 0;
    for(int i = 0; i < s.length(); i++)
    {
        if(IsVowel(s[i]))
            vowelCount++;
    }
    return vowelCount;
}

int NumConsonants(string s)
{
    int consonantCount = 0;
    for(int i = 0; i < s.length(); i++)
    {
        if(isConsonant(s[i]))
            consonantCount++;
    }
    return consonantCount;
}

double AverageWordLength(string s)
{
    return (NumVowels(s) + NumConsonants(s)) / (double)NumWords(s);
}

double AverageVowelsPerWord(string s)
{
    return NumVowels(s) / (double)NumWords(s);
}

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







