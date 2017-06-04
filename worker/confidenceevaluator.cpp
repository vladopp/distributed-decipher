#include "confidenceevaluator.h"
#include <fstream>
#include <sstream>
#include <QFile>
#include <QTextStream>

/**
 * @brief ConfidenceEvaluator::ConfidenceEvaluator
 * @param dictionaryPath
 */
ConfidenceEvaluator::ConfidenceEvaluator(QString dictionaryPath)
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
void ConfidenceEvaluator::loadDictionary(QString dictionaryPath)
{
    QFile file(dictionaryPath);
    if (!file.open(QIODevice::ReadOnly)) {
        printf("Unable to open file %s", qPrintable(file.errorString()));
        return;
    }

    QTextStream in(&file);
    while (!in.atEnd())
    {
        englishDictionary.insert(in.readLine().toStdString());
    }
    file.close();
}
