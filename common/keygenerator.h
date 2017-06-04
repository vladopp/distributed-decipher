#ifndef KEYGENERATOR_H
#define KEYGENERATOR_H

#include <vector>
#include <QString>

/**
 * @brief The KeyGenerator class This class is responsible for creating alphabetical permutations
 * of strings in order to ease the process of creating keys.
 *
 */
class KeyGenerator
{
public:
    static QString nextPermutation(QString currentPermutation);
    static QString getLastPermutation(QString currentPermutation);
};

#endif // KEYGENERATOR_H
