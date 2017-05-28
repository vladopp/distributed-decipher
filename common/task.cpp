#include "task.h"

/**
 * @brief Task::Task ctor.
 * @param id ID of the task.
 */
Task::Task(int id) : id(id)
{
}

/**
 * @brief Task::Task ctor.
 * @param textId ID of the text to be processed.
 * @param fromKey Starting key from which to start the processing.
 * @param toKey Ending key to which to end the processing.
 */
Task::Task(int textId, std::string fromKey, std::string toKey) :
    id(-1),
    textId(textId),
    fromKey(fromKey),
    toKey(toKey)
{
}

/**
 * @brief Task::Task ctor.
 * @param id ID of the task
 * @param textId ID of the text to be processed.
 * @param fromKey Starting key from which to start the processing.
 * @param toKey Ending key to which to end the processing.
 */
Task::Task(int id, int textId, std::string fromKey, std::string toKey) :
    id(id),
    textId(textId),
    fromKey(fromKey),
    toKey(toKey)
{
}

/**
 * @brief Task::Task ctor.
 * @param id ID of the task
 * @param textId ID of the text to be processed.
 * @param fromKey Starting key from which to start the processing.
 * @param toKey Ending key to which to end the processing.
 * @param acceptedTimestamp TODO: add description.
 */
Task::Task(int id, int textId, std::string fromKey, std::string toKey, unsigned long long acceptedTimestamp) :
    Task(id, textId, fromKey, toKey)
{
    setAcceptedTimestamp(acceptedTimestamp);
}

/**
 * @brief Task::Task
 * @param id
 * @param textId
 * @param fromKey
 * @param toKey
 * @param acceptedTimestamp
 * @param bestKey
 * @param confidence
 */
Task::Task(int id, int textId, std::string fromKey, std::string toKey, unsigned long long acceptedTimestamp, std::string bestKey, double confidence) :
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
std::string Task::getFromKey() const
{
    return fromKey;
}

/**
 * @brief Task::getToKey
 * @return Returns the last key of the task.
 */
std::string Task::getToKey() const
{
    return toKey;
}

/**
 * @brief Task::getAcceptedTimestamp
 * @return TODO: Add description.
 */
unsigned long long Task::getAcceptedTimestamp() const
{
    return acceptedTimestamp;
}

/**
 * @brief Task::setAcceptedTimestamp
 * @param value TODO: Add description.
 */
void Task::setAcceptedTimestamp(unsigned long long value)
{
    acceptedTimestamp = value;
}

/**
 * @brief Task::getBestKey
 * @return
 */
std::string Task::getBestKey() const
{
    return bestKey;
}

/**
 * @brief Task::setBestKey
 * @param value
 */
void Task::setBestKey(const std::string &value)
{
    bestKey = value;
}

/**
 * @brief Task::getConfidence
 * @return
 */
double Task::getConfidence() const
{
    return confidence;
}

/**
 * @brief Task::setConfidence
 * @param value
 */
void Task::setConfidence(double value)
{
    confidence = value;
}
