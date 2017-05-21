#include "confidenceevaluator.h"
#include <fstream>
#include <sstream>

/**
 * @brief ConfidenceEvaluator::ConfidenceEvaluator
 * @param dictionaryPath
 */
ConfidenceEvaluator::ConfidenceEvaluator(const std::string& dictionaryPath)
{
    std::unordered_set<std::string> englishDictionary;
    loadDictionary(dictionaryPath);
}

/**
 * @brief ConfidenceEvaluator::calculateConfidence
 * @param text
 * @return
 */
double ConfidenceEvaluator::calculateConfidence(const std::string& text)
{
    unsigned int wordCount = 0;
    unsigned int englishWordCount = 0;
    std::istringstream textStream(text);
    std::string word;
    while(textStream >> word)
    {
        ++wordCount;
        if (englishDictionary.count(word))
        {
            ++englishWordCount;
        }
    }
    return englishWordCount * 1.0 / wordCount;
}

/**
 * @brief ConfidenceEvaluator::loadDictionary
 * @param dictionaryPath
 */
void ConfidenceEvaluator::loadDictionary(const std::string& dictionaryPath)
{
    std::ifstream file;
    file.open(dictionaryPath);
    std::string word;
    while (file >> word)
    {
        englishDictionary.insert(word);
    }
    file.close();
}
