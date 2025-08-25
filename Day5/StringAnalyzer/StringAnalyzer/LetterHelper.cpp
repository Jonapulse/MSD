//
//  LetterHelper.cpp
//  StringAnalyzer
//
//  Created by Jonathan Pulsipher on 8/25/25.
//

#include "LetterHelper.h"

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
