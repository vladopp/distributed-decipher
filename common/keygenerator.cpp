#include "keygenerator.h"

/**
 * @brief KeyGenerator::nextPermutation Generates the next permutation of the string, if such is possible.
 * @param currentPermutation Starting permutation of letters in range ['a':'z'].
 * @return Returns the next permutation of characters or if such doesn't exist it returns the @lastPermutation of the @currentPermutation.
 */
QString KeyGenerator::nextPermutation(QString currentPermutation)
{
    // check if input is valid
    for(int i=0; i < currentPermutation.size(); i++)
    {
        if(currentPermutation.at(i) < 'a' || currentPermutation.at(i) > 'z')
        {
            return getLastPermutation(currentPermutation);
        }
    }

    // generate new permutation
    QString newPermutation = currentPermutation;
    bool incremented = false;
    // signed counter, to get negative when we iterated whole string
    for(int i = newPermutation.size() - 1; i >= 0 ; i--)
    {
        if(newPermutation.at(i) < 'z')
        {
            incremented = true;
            newPermutation.replace(i, 1, newPermutation.at(i).unicode()+1);
            break;
        }
        else
        {
            newPermutation.replace(i, 1, 'a');
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
QString KeyGenerator::getLastPermutation(QString currentPermutation)
{
    return QString(currentPermutation.size(), 'z');
}
