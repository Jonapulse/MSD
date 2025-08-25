//
//  WordHelper.h
//  StringAnalyzer
//
//  Created by Jonathan Pulsipher on 8/25/25.
//

#ifndef WordHelper_H
#define WordHelper_H

#include <string>
#include "LetterHelper.h"

int NumWords(std::string s);

int NumSentences(std::string s);

int NumVowels(std::string s);

int NumConsonants(std::string s);

double AverageWordLength(std::string s);

double AverageVowelsPerWord(std::string s);

#endif
