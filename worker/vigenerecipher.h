#ifndef VIGENERECIPHER_H
#define VIGENERECIPHER_H

#include <string>

class VigenereCipher
{
public:
    static std::string encrypt(const std::string& text, const std::string& key);
    static std::string decrypt(const std::string& text, const std::string& key);
    static int findProbableKeyLength(const std::string& text);
private:
    static double calculateIndexOfCoincidence(const std::string& text, int step);
};

#endif // VIGENERECIPHER_H
