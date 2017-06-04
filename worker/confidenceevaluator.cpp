#include "confidenceevaluator.h"
#include <QFile>
#include <QStringList>
#include <QTextStream>

/**
 * @brief ConfidenceEvaluator::ConfidenceEvaluator
 * @param dictionaryPath
 */
ConfidenceEvaluator::ConfidenceEvaluator(const QString& dictionaryPath)
{
    QSet<QString> englishDictionary;
    loadDictionary(dictionaryPath);
}

/**
 * @brief ConfidenceEvaluator::calculateConfidence
 * @param text
 * @return
 */
double ConfidenceEvaluator::calculateConfidence(const QString& text)
{
    unsigned int wordCount = 0;
    unsigned int englishWordCount = 0;
    QStringList words = text.split(QRegExp("\\s"), QString::SkipEmptyParts);
    for(QString word : words)
    {
        ++wordCount;
        if (englishDictionary.contains(word))
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
void ConfidenceEvaluator::loadDictionary(const QString& dictionaryPath)
{
    QFile file(dictionaryPath);
    if (!file.open(QIODevice::ReadOnly)) {
        printf("Unable to open file %s", qPrintable(file.errorString()));
        return;
    }

    QTextStream in(&file);
    while (!in.atEnd())
    {
        englishDictionary.insert(in.readLine());
    }
    file.close();
}
