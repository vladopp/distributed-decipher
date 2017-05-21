#ifndef VIGENERECIPHER_H
#define VIGENERECIPHER_H

#include <string>

class VigenereCipher
{
public:
    static std::string encrypt(const std::string& text, const std::string& key);
    static std::string decrypt(const std::string& text, const std::string& key);
};

#endif // VIGENERECIPHER_H
