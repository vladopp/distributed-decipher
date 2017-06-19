#ifndef CONFIDENCEEVALUATOR_H
#define CONFIDENCEEVALUATOR_H

#include <QString>
#include <QSet>

class ConfidenceEvaluator
{
public:
    ConfidenceEvaluator(const QString& dictionaryPath);
    double calculateConfidence(const QString& text) const;
private:
    QSet<QString> dictionary;
    void loadDictionary(const QString& dictionaryPath);
};

#endif // CONFIDENCEEVALUATOR_H
