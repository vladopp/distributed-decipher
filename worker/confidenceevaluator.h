#ifndef CONFIDENCEEVALUATOR_H
#define CONFIDENCEEVALUATOR_H

#include <string>
#include <unordered_set>

class ConfidenceEvaluator
{
public:
    ConfidenceEvaluator(const std::string& dictionaryPath);
    double calculateConfidence(const std::string& text);
private:
    std::unordered_set<std::string> englishDictionary;
    void loadDictionary(const std::string& dictionaryPath);
};

#endif // CONFIDENCEEVALUATOR_H
