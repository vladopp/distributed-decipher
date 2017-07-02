#include "confidenceevaluator.h"
#include <QFile>
#include <QStringList>
#include <QTextStream>

/**
 * @brief ConfidenceEvaluator::ConfidenceEvaluator Constructor that loads a dictinary file that will be used for calculating confidence scores.
 * @param dictionaryPath The path to the file containig the dictionary to be used.
 */
ConfidenceEvaluator::ConfidenceEvaluator(const QString& dictionaryPath)
{
    QSet<QString> dictionary;
    loadDictionary(dictionaryPath);
}

/**
 * @brief ConfidenceEvaluator::calculateConfidence Calculates a confidance score which represents the probability of
 * the provided text to be the original (unencrypted text). It counts the number of words found in the loaded dictionary.
 * @param text The text that has to be evaluated
 * @return The confidence score as a floating point number
 */
double ConfidenceEvaluator::calculateConfidence(const QString& text) const
{
    unsigned int wordCount = 0;
    unsigned int englishWordCount = 0;
    QStringList words = text.split(QRegExp("\\s"), QString::SkipEmptyParts);
    for(QString word : words)
    {
        ++wordCount;
        if (dictionary.contains(word))
        {
            ++englishWordCount;
        }
    }
    return englishWordCount * 1.0 / wordCount;
}

/**
 * @brief ConfidenceEvaluator::loadDictionary Loads a list of words from a file used for calculating confidence scores.
 * @param dictionaryPath The path to a line separated text file containing the dictionary
 */
void ConfidenceEvaluator::loadDictionary(const QString& dictionaryPath)
{
    QFile file(dictionaryPath);
    if (!file.open(QIODevice::ReadOnly)) {
        printf("Unable to open file. No dictionary will be loaded and confidence scores cannot be calculated. %s\n", qPrintable(file.errorString()));
        return;
    }

    QTextStream in(&file);
    while (!in.atEnd())
    {
        dictionary.insert(in.readLine());
    }
    file.close();
}
