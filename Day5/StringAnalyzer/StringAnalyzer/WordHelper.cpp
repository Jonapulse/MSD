//
//  WordHelper.cpp
//  StringAnalyzer
//
//  Created by Jonathan Pulsipher on 8/25/25.
//

#include "WordHelper.h"

int NumWords(std::string s)
{
    int spaceCount = 0;
    for(int i = 0; i < s.length(); i++)
    {
        if(s[i] == ' ')
            spaceCount++;
    }
    return spaceCount + 1;
}

int NumSentences(std::string s)
{
    int terminatorCount = 0;
    for(int i = 0; i < s.length(); i++)
    {
        if(IsTerminator(s[i]))
            terminatorCount++;
    }
    return terminatorCount;
}

int NumVowels(std::string s)
{
    int vowelCount = 0;
    for(int i = 0; i < s.length(); i++)
    {
        if(IsVowel(s[i]))
            vowelCount++;
    }
    return vowelCount;
}

int NumConsonants(std::string s)
{
    int consonantCount = 0;
    for(int i = 0; i < s.length(); i++)
    {
        if(isConsonant(s[i]))
            consonantCount++;
    }
    return consonantCount;
}

double AverageWordLength(std::string s)
{
    return (NumVowels(s) + NumConsonants(s)) / (double)NumWords(s);
}

double AverageVowelsPerWord(std::string s)
{
    return NumVowels(s) / (double)NumWords(s);
}
