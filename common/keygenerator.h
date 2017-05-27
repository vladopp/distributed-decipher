#ifndef KEYGENERATOR_H
#define KEYGENERATOR_H

#include <vector>
#include <string>

/**
 * @brief The KeyGenerator class This class is responsible for creating alphabetical permutations
 * of strings in order to ease the process of creating keys.
 *
 */
class KeyGenerator
{
public:
    static std::string nextPermutation(std::string currentPermutation);
    static std::string getLastPermutation(std::string currentPermutation);
};

#endif // KEYGENERATOR_H
