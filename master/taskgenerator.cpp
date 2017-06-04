#include "taskgenerator.h"
#include "keygenerator.h"

/**
 * @brief TaskGenerator::getTasks
 * @param keyLength
 * @return Returns a vector with all tasks for the provided @keyLength.
 */
std::vector< std::pair<QString, QString> > TaskGenerator::getTasks( size_t keyLength )
{
    std::vector< std::pair<QString, QString> > result;

    QString lowerBound(keyLength, 'a');
    QString upperBound = getUpperBound(lowerBound);
    QString end(keyLength, 'z');
    while( lowerBound != upperBound )
    {
        result.push_back(std::make_pair(lowerBound, upperBound));

        lowerBound = KeyGenerator::nextPermutation(upperBound);
        upperBound = getUpperBound(lowerBound);
    }

    return result;
}

/**
 * @brief TaskGenerator::getUpperBound
 * @param lowerBound
 * @return
 */
QString TaskGenerator::getUpperBound(QString lowerBound)
{
    static const int TASK_SIZE = 3;
    if(lowerBound.size() <= TASK_SIZE )
    {
        // string size is too small, so return the upper bound of same length
        return KeyGenerator::getLastPermutation(lowerBound);
    }

    QString upperBound = lowerBound;
    // set TASK_SIZE 'z' at the end
    for(size_t i=upperBound.size() - TASK_SIZE; i < upperBound.size(); i++)
    {
        upperBound.replace(i, 1, 'z');
    }

    return upperBound;
}
