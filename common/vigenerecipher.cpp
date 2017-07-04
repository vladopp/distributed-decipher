#include "vigenerecipher.h"

/**
 * @brief VigenereCipher::encrypt Encrypts the text with the key, using Vigenere cipher.
 * @param text Text to be encrypted.
 * @param key Key to be used for encryption.
 * @return Returns the encrypted text.
 */
QString VigenereCipher::encrypt(const QString& text, const QString& key)
{
QString result=text;

    int idxText=0U;
    int idxKey=0U;
    while(idxText<result.size())
    {
        result.replace(idxText, 1, QChar(result.at(idxText).unicode() + key.at(idxKey).unicode()));
        idxKey = (idxKey + 1) % key.size();
        idxText++;
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
QString result=text;

    int idxText=0U;
    int idxKey=0U;
    while(idxText<result.size())
    {
        result.replace(idxText, 1, QChar(result.at(idxText).unicode() - key.at(idxKey).unicode()));
        idxKey = (idxKey + 1) % key.size();
        idxText++;
    }

    return result;
}
