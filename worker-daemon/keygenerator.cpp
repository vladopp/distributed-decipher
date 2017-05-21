#include "keygenerator.h"

/**
 * @brief KeyGenerator::nextPermutation
 * @param currentPermutation
 * @return
 */
std::string KeyGenerator::nextPermutation(std::string currentPermutation)
{
    // check if input is valid
    for(size_t i=0; i < currentPermutation.size(); i++)
    {
        if(currentPermutation[i] < 'a' || currentPermutation[i] > 'z')
        {
            return getLastPermutation(currentPermutation);
        }
    }

    // generate new permutation
    std::string newPermutation = currentPermutation;
    bool incremented = false;
    // signed counter, to get negative when we iterated whole string
    for(int i = newPermutation.size() - 1; i >= 0 ; i--)
    {
        if(newPermutation[i] < 'z')
        {
            incremented = true;
            newPermutation[i]++;
            break;
        }
        else
        {
            newPermutation[i] = 'a';
        }
    }

    // if this is the last permutation of the string
    if(!incremented)
    {
        // set the result to invalid state, in case of string "zzz...zzz"
        newPermutation = getLastPermutation(currentPermutation);
    }

    return newPermutation;
}

/**
 * @brief KeyGenerator::getLastPermutation
 * @param currentPermutation
 * @return
 */
std::string KeyGenerator::getLastPermutation(std::string currentPermutation)
{
    return std::string('z', currentPermutation.size());
}
