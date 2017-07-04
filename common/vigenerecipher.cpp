#include "vigenerecipher.h"

/**
 * @brief VigenereCipher::encrypt Encrypts the text with the key, using Vigenere cipher.
 * Only the letter characters will be encrypted.
 * @param text Text to be encrypted.
 * @param key Key to be used for encryption.
 * @return Returns the encrypted text.
 */
QString VigenereCipher::encrypt(const QString& text, const QString& key)
{
    QString result = text.toLower();
    QString keyCopy = key.toLower();

    int idxText = 0;
    int idxKey = 0;
    while(idxText<result.size())
    {
        if (!result.at(idxText).isLetter())
        {
            idxText++;
            continue;
        }

        int replacement = result.at(idxText).toLatin1() + (keyCopy.at(idxKey).toLatin1() - 97);
        if (replacement > 122)
        {
            replacement -= 26;
        }
        result.replace(idxText, 1, QChar(replacement));
        idxKey = (idxKey + 1) % keyCopy.size();
        idxText++;
    }

    return result;
}

/**
 * @brief VigenereCipher::decrypt Decrypts the text with the key, using Vigenere cipher.
 * Only the letter characters will be decrypted.
 * @param text Text to be decrypted.
 * @param key Key to be used for decryption.
 * @return Returns the decrypted text.
 */
QString VigenereCipher::decrypt(const QString& text, const QString& key)
{
    QString result = text.toLower();
    QString keyCopy = key.toLower();

    int idxText = 0;
    int idxKey = 0;
    while(idxText<result.size())
    {
        if (!result.at(idxText).isLetter())
        {
            idxText++;
            continue;
        }

        int replacement = result.at(idxText).toLatin1() - (keyCopy.at(idxKey).toLatin1() - 97);
        if (replacement < 97)
        {
            replacement += 26;
        }
        result.replace(idxText, 1, QChar(replacement));
        idxKey = (idxKey + 1) % keyCopy.size();
        idxText++;
    }

    return result;
}
