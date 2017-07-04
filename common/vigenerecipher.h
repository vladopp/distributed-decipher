#ifndef VIGENERECIPHER_H
#define VIGENERECIPHER_H

#include <QString>

class VigenereCipher
{
public:
    static QString encrypt(const QString& text, const QString& key);
    static QString decrypt(const QString& text, const QString& key);
};

#endif // VIGENERECIPHER_H
