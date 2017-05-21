#include "vigenerecipher.h"

std::string VigenereCipher::encrypt(const std::string& text, const std::string& key)
{
std::string result=text;

    size_t idxText=0U;
    size_t idxKey=0U;
    for(;idxText<result.size(); idxText++)
    {
        result[idxText] = std::tolower(result[idxText]) + key[idxKey];

        idxKey = (idxKey + 1) % key.size();
    }

    return result;
}

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
