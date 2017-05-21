#ifndef KEYGENERATOR_H
#define KEYGENERATOR_H

#include <vector>
#include <string>

class KeyGenerator
{
public:
    static std::string nextPermutation(std::string currentPermutation);
private:
    static std::string getLastPermutation(std::string currentPermutation);
};

#endif // KEYGENERATOR_H
