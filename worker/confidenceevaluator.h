#ifndef CONFIDENCEEVALUATOR_H
#define CONFIDENCEEVALUATOR_H

#include <string>
#include <unordered_set>
#include <QString>

class ConfidenceEvaluator
{
public:
    ConfidenceEvaluator(QString dictionaryPath);
    double calculateConfidence(const std::string& text);
private:
    std::unordered_set<std::string> englishDictionary;
    void loadDictionary(QString dictionaryPath);
};

#endif // CONFIDENCEEVALUATOR_H
