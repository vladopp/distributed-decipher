#include "vigenerecipher.h"

/**
 * @brief VigenereCipher::encrypt Encrypts the text with the key, using Vigenere cipher.
 * @param text Text to be encrypted.
 * @param key Key to be used for encryption.
 * @return Returns the encrypted text.
 */
std::string VigenereCipher::encrypt(const std::string& text, const std::string& key)
{
std::string result=text;

    size_t idxText=0U;
    size_t idxKey=0U;
    for(;idxText<result.size(); idxText++)
    {
        result[idxText] = result[idxText] + key[idxKey];

        idxKey = (idxKey + 1) % key.size();
    }

    return result;
}

/**
 * @brief VigenereCipher::decrypt Decrypts the text with the key, using Vigenere cipher.
 * @param text Text to be decrypted.
 * @param key Key to be used for decryption.
 * @return Returns the decrypted text.
 */
std::string VigenereCipher::decrypt(const std::string& text, const std::string& key)
{
std::string result=text;

    size_t idxText=0U;
    size_t idxKey=0U;
    for(;idxText<result.size(); idxText++)
    {
        result[idxText] = result[idxText] - key[idxKey];

        idxKey = (idxKey + 1) % key.size();
    }

    return result;
}
