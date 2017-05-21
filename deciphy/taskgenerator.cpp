#include "taskgenerator.h"

// TODO: Use getLastPermutation from KeyGenerator
std::string getLastPermutation(std::string currentPermutation)
{
    return std::string(currentPermutation.size(), 'z');
}

// TODO: Use nextPermutation from KeyGenerator
std::string nextPermutation(std::string currentPermutation)
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
 * @brief TaskGenerator::getTasks
 * @param keyLength
 * @return
 */
std::vector< std::pair<std::string, std::string> > TaskGenerator::getTasks( size_t keyLength )
{
    std::vector< std::pair<std::string, std::string> > result;

    std::string lowerBound( keyLength, 'a' );
    std::string upperBound = getUpperBound( lowerBound );
    std::string end( 'z', keyLength );
    while( lowerBound != upperBound )
    {
        result.push_back( std::make_pair( lowerBound, upperBound ) );

        lowerBound = nextPermutation(upperBound);
        upperBound = getUpperBound(lowerBound);
    }

    return result;
}

/**
 * @brief TaskGenerator::getUpperBound
 * @param lowerBound
 * @return
 */
std::string TaskGenerator::getUpperBound( std::string lowerBound )
{
    static const int TASK_SIZE = 3;
    if(lowerBound.size() <= TASK_SIZE )
    {
        // string size is too small, so return the upper bound of same length
        return getLastPermutation(lowerBound);
    }

    std::string upperBound = lowerBound;
    // set TASK_SIZE 'z' at the end
    for(size_t i=upperBound.size() - TASK_SIZE; i < upperBound.size(); i++)
    {
        upperBound[i] = 'z';
    }

    return upperBound;
}
