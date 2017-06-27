#include "vigenerecipher.h"

/**
 * @brief VigenereCipher::encrypt Encrypts the text with the key, using Vigenere cipher.
 * @param text Text to be encrypted.
 * @param key Key to be used for encryption.
 * @return Returns the encrypted text.
 */
QString VigenereCipher::encrypt(const QString& text, const QString& key)
{
    QString result = text.toLower();
    QString key_copy = key.toLower();

    int idxText = 0U;
    int idxKey = 0U;
    for(;idxText<result.size(); idxText++)
    {
        if (result.at(idxText) == ' '
                || result.at(idxText) == ','
                || result.at(idxText) == '.'
                || result.at(idxText) == '!'
                || result.at(idxText) == '?'
                || result.at(idxText) == ':'
                || result.at(idxText) == '-')
        {
            continue;
        }

        int replacement = result.at(idxText).toLatin1() + (key_copy.at(idxKey).toLatin1() - 97);
        if (replacement > 122)
        {
            replacement -= 26;
        }
        result.replace(idxText, 1, QChar(replacement));
        idxKey = (idxKey + 1) % key_copy.size();
    }

    return result;
}

/**
 * @brief VigenereCipher::decrypt Decrypts the text with the key, using Vigenere cipher.
 * @param text Text to be decrypted.
 * @param key Key to be used for decryption.
 * @return Returns the decrypted text.
 */
QString VigenereCipher::decrypt(const QString& text, const QString& key)
{
    QString result = text.toLower();
    QString key_copy = key.toLower();

    int idxText = 0U;
    int idxKey = 0U;
    for(;idxText<result.size(); idxText++)
    {
        if (result.at(idxText) == ' '
                || result.at(idxText) == ','
                || result.at(idxText) == '.'
                || result.at(idxText) == '!'
                || result.at(idxText) == '?'
                || result.at(idxText) == ':'
                || result.at(idxText) == '-'
        {
            continue;
        }

        int replacement = result.at(idxText).toLatin1() - (key_copy.at(idxKey).toLatin1() - 97);
        if (replacement < 97)
        {
            replacement += 26;
        }
        result.replace(idxText, 1, QChar(replacement));
        idxKey = (idxKey + 1) % key_copy.size();
    }

    return result;
}
