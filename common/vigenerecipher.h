#ifndef VIGENERECIPHER_H
#define VIGENERECIPHER_H

#include <QString>

class VigenereCipher
{
public:
    static QString encrypt(const QString& text, const QString& key);
    static QString decrypt(const QString& text, const QString& key);
    static int getProbableKeyLength(const QString& text);
private:
    static double calculateIndexOfCoincidenceEveryNthLetter(const QString& text, const int n);
    static QString getEveryNthLetter(const QString& text, const int n, const int startIdx);
    static double calculateIndexOfCoincidence(const QString& text);
    static int chooseMostProbableKeyLength(double probabilities[]);
};

#endif // VIGENERECIPHER_H
