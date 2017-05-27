#include "task.h"

Task::Task(int id) : id(id)
{
}

Task::Task(int id, int textId, std::string fromKey, std::string toKey) : id(id)
{
    setTextId(textId);
    setFromKey(fromKey);
    setToKey(toKey);
}

Task::Task(int id, int textId, std::string fromKey, std::string toKey, unsigned long long acceptedTimestamp) : id(id)
{
    setTextId(textId);
    setFromKey(fromKey);
    setToKey(toKey);
    setAcceptedTimestamp(acceptedTimestamp);
}

Task::Task(int id, int textId, std::string fromKey, std::string toKey, unsigned long long acceptedTimestamp, std::string bestKey, double confidence) : id(id)
{
    setTextId(textId);
    setFromKey(fromKey);
    setToKey(toKey);
    setAcceptedTimestamp(acceptedTimestamp);
    setBestKey(bestKey);
    setConfidence(confidence);
}

int Task::getId() const
{
    return id;
}

int Task::getTextId() const
{
    return textId;
}

void Task::setTextId(int value)
{
    textId = value;
}

std::string Task::getFromKey() const
{
    return fromKey;
}

void Task::setFromKey(const std::string &value)
{
    fromKey = value;
}

std::string Task::getToKey() const
{
    return toKey;
}

void Task::setToKey(const std::string &value)
{
    toKey = value;
}

unsigned long long Task::getAcceptedTimestamp() const
{
    return acceptedTimestamp;
}

void Task::setAcceptedTimestamp(unsigned long long value)
{
    acceptedTimestamp = value;
}

std::string Task::getBestKey() const
{
    return bestKey;
}

void Task::setBestKey(const std::string &value)
{
    bestKey = value;
}

double Task::getConfidence() const
{
    return confidence;
}

void Task::setConfidence(double value)
{
    confidence = value;
}
