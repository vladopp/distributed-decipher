#include "keygenerator.h"

/**
 * @brief KeyGenerator::nextPermutation Generates the next permutation of the string, if such is possible.
 * @param currentPermutation Starting permutation of letters in range ['a':'z'].
 * @return Returns the next permutation of characters or if such doesn't exist it returns the @lastPermutation of the @currentPermutation.
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
    for(size_t i = newPermutation.size() - 1; i >= 0 ; i--)
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
 * @brief KeyGenerator::getLastPermutation Gets the last permutation of length the length of currentPermutation.
 * @param currentPermutation The string from which to get the length of the returning string.
 * @return Returns a string with same length as currentPermutation's length, filled with 'z' character.
 */
std::string KeyGenerator::getLastPermutation(std::string currentPermutation)
{
    return std::string(currentPermutation.size(), 'z');
}
