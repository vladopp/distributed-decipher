#include <QRegularExpression>
#include "vigenerecipher.h"

const int LOWERCASE_LETTERS_COUNT = 26;
const int MAX_PROBABLE_LENGTH = 20;
const double ENGLISH_INDEX_OF_COINCIDENCE = 0.0667;

/**
 * @brief VigenereCipher::encrypt Encrypts the text with the key, using Vigenere cipher.
 * Only the letter characters will be encrypted.
 * @param text Text to be encrypted.
 * @param key Key to be used for encryption.
 * @return Returns the encrypted text.
 */
QString VigenereCipher::encrypt(const QString& text, const QString& key)
{
    QString result = text.toLower();
    QString keyCopy = key.toLower();

    int idxText = 0;
    int idxKey = 0;
    while(idxText<result.size())
    {
        if (!result.at(idxText).isLetter())
        {
            idxText++;
            continue;
        }

        int replacement = result.at(idxText).toLatin1() + (keyCopy.at(idxKey).toLatin1() - 'a');
        if (replacement > 'z')
        {
            replacement -= LOWERCASE_LETTERS_COUNT;
        }
        result.replace(idxText, 1, QChar(replacement));
        idxKey = (idxKey + 1) % keyCopy.size();
        idxText++;
    }

    return result;
}

/**
 * @brief VigenereCipher::decrypt Decrypts the text with the key, using Vigenere cipher.
 * Only the letter characters will be decrypted.
 * @param text Text to be decrypted.
 * @param key Key to be used for decryption.
 * @return Returns the decrypted text.
 */
QString VigenereCipher::decrypt(const QString& text, const QString& key)
{
    QString result = text.toLower();
    QString keyCopy = key.toLower();

    int idxText = 0;
    int idxKey = 0;
    while(idxText<result.size())
    {
        if (!result.at(idxText).isLetter())
        {
            idxText++;
            continue;
        }

        int replacement = result.at(idxText).toLatin1() - (keyCopy.at(idxKey).toLatin1() - 'a');
        if (replacement < 'a')
        {
            replacement += LOWERCASE_LETTERS_COUNT;
        }
        result.replace(idxText, 1, QChar(replacement));
        idxKey = (idxKey + 1) % keyCopy.size();
        idxText++;
    }

    return result;
}

/**
 * @brief getProbableKeyLength Tries to find out how long is the key used to encipher the provided text.
 * It uses the method of Index of Coincidence to find it out. However this is heuristics method and it is possible
 * to produce wrong results.
 * @param text Eciphered text that should be used for finding the probable key length
 * @return the probable key lenght
 */
int VigenereCipher::getProbableKeyLength(const QString& text)
{
    double probabilities[MAX_PROBABLE_LENGTH];

    for(int length = 1; length < MAX_PROBABLE_LENGTH; length++)
    {
        probabilities[length] = calculateIndexOfCoincidenceEveryNthLetter(text, length);
    }

    return chooseMostProbableKeyLength(probabilities);
}

/**
 * @brief VigenereCipher::calculateIndexOfCoincidence Calculates the Index of Coincidence using every Nth letter.
 * @param text The text that should be processed
 * @param n The gap between the letters that should be used when calculating the Index of Coincidence.
 * @return The Index of Coincidence
 */
double VigenereCipher::calculateIndexOfCoincidenceEveryNthLetter(const QString& text, const int n)
{
    double coincidences = 0;
    for(int startIdx = 0; startIdx < n; startIdx++)
    {
        coincidences += calculateIndexOfCoincidence(getEveryNthLetter(text, n, startIdx));
    }
    return coincidences * 1.0 / n;
}


/**
 * @brief VigenereCipher::getEveryNthLetter Returns a QString containing every Nth letter of the provided string.
 * @param text The text to be processed.
 * @param n The gap between the letters that should be copied.
 * @param startIdx The starting index which will be used when processing the provided text.
 * @return QString containing every Nth letter of the provided string.
 */
QString VigenereCipher::getEveryNthLetter(const QString& text, const int n, const int startIdx)
{
    QString letters = text.toLower();
    letters.replace(QRegularExpression("[^a-z]"), "");
    QString result = "";
    for(int i = startIdx; i < letters.size(); i += n)
    {
        result.append(letters.at(i));
    }
    return result;
}

/**
 * @brief VigenereCipher::calculateIndexOfCoincidence Calculates the Index of Coincidence of a given text.
 * @param text The text that should be processed. It should contain only letters.
 * @return The calculated Index of Coincidence
 */
double VigenereCipher::calculateIndexOfCoincidence(const QString& text)
{
    int letterCount[LOWERCASE_LETTERS_COUNT];
    for (int i = 0; i < LOWERCASE_LETTERS_COUNT; i++)
    {
        letterCount[i] = 0;
    }

    for (int i = 0; i < text.size(); i++)
    {
        letterCount[text.at(i).toLatin1() - 'a']++;
    }
    int sum = 0;
    for (int i = 0; i < LOWERCASE_LETTERS_COUNT; i++)
    {
        sum = sum + letterCount[i] * (letterCount[i] - 1);
    }

    double indexOfCoincidence = sum * 1.0 / (text.size() * (text.size() - 1));
    return indexOfCoincidence;
}

/**
 * @brief VigenereCipher::chooseMostProbableKeyLength Chooses the most probable key length
 * @param probabilities Array containing the probabilites of the different key lengths
 * @return The most shortest key length that has larger than 110% of the avg probability
 */
int VigenereCipher::chooseMostProbableKeyLength(double probabilities[])
{

    double avgProbability = 0;
    for (int length = 1; length < MAX_PROBABLE_LENGTH; length++)
    {
        avgProbability += probabilities[length];
    }
    avgProbability /= MAX_PROBABLE_LENGTH - 1;
    double cutline = avgProbability * 1.1;

    for (int length = 1; length < MAX_PROBABLE_LENGTH; length++)
    {
        if (probabilities[length] > cutline)
        {
            return length;
        }
    }

    return MAX_PROBABLE_LENGTH - 1;
}
