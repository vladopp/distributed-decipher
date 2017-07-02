#include "task.h"

/**
 * @brief Task::Task Constructor.
 * @param id ID of the task.
 */
Task::Task(int id) :
    id(id)
{
}

/**
 * @brief Task::Task Constructor that sets the textId, fromKey and toKey.
 * The id will of the task will be generated from the database.
 * @param textId ID of the text to be processed.
 * @param fromKey Starting key from which to start the processing.
 * @param toKey Ending key to which to end the processing.
 */
Task::Task(int textId, QString fromKey, QString toKey) :
    id(-1),
    textId(textId),
    fromKey(fromKey),
    toKey(toKey)
{
}

/**
 * @brief Task::Task Constructor.
 * @param id ID of the task
 * @param textId ID of the text to be processed.
 * @param fromKey Starting key from which to start the processing.
 * @param toKey Ending key to which to end the processing.
 */
Task::Task(int id, int textId, QString fromKey, QString toKey) :
    id(id),
    textId(textId),
    fromKey(fromKey),
    toKey(toKey)
{
}

/**
 * @brief Task::Task Constructor.
 * @param id ID of the task
 * @param textId ID of the text to be processed.
 * @param fromKey Starting key from which to start the processing.
 * @param toKey Ending key to which to end the processing.
 * @param acceptedTimestamp The unixtimestamp when the worker accepted the task.
 */
Task::Task(int id, int textId, QString fromKey, QString toKey, unsigned long long acceptedTimestamp) :
    Task(id, textId, fromKey, toKey)
{
    setAcceptedTimestamp(acceptedTimestamp);
}

/**
 * @brief Task::Task Constructor
 * @param id ID of the task
 * @param textId ID of the text to be processed.
 * @param fromKey Starting key from which to start the processing.
 * @param toKey Ending key to which to end the processing.
 * @param acceptedTimestamp The unixtimestamp when the worker accepted the task.
 * @param bestKey The key that generated the best confidence score.
 * @param confidence The best confidence score produced by the best key.
 */
Task::Task(int id, int textId, QString fromKey, QString toKey, unsigned long long acceptedTimestamp, QString bestKey, double confidence) :
    Task(id, textId, fromKey, toKey, acceptedTimestamp)
{
    setBestKey(bestKey);
    setConfidence(confidence);
}

/**
 * @brief Task::getId
 * @return Returns the ID of the task.
 */
int Task::getId() const
{
    return id;
}

/**
 * @brief Task::getTextId
 * @return Returns the ID of the text to which the task is related.
 */
int Task::getTextId() const
{
    return textId;
}

/**
 * @brief Task::getFromKey
 * @return Returns the starting key of the task.
 */
QString Task::getFromKey() const
{
    return fromKey;
}

/**
 * @brief Task::getToKey
 * @return Returns the last key of the task.
 */
QString Task::getToKey() const
{
    return toKey;
}

/**
 * @brief Task::getAcceptedTimestamp
 * @return The unixtimestamp when the worker accepted the task.
 */
unsigned long long Task::getAcceptedTimestamp() const
{
    return acceptedTimestamp;
}

/**
 * @brief Task::setAcceptedTimestamp
 * @param value The unixtimestamp when the worker accepted the task.
 */
void Task::setAcceptedTimestamp(unsigned long long value)
{
    acceptedTimestamp = value;
}

/**
 * @brief Task::getBestKey
 * @return the key that generated the best confidence score.
 */
QString Task::getBestKey() const
{
    return bestKey;
}

/**
 * @brief Task::setBestKey
 * @param value the key that generated the best confidence score.
 */
void Task::setBestKey(const QString &value)
{
    bestKey = value;
}

/**
 * @brief Task::getConfidence
 * @return the confidence score of the best key.
 */
double Task::getConfidence() const
{
    return confidence;
}

/**
 * @brief Task::setConfidence
 * @param value the confidence score of the best key.
 */
void Task::setConfidence(double value)
{
    confidence = value;
}
