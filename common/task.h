#ifndef TASK_H
#define TASK_H

#include <string>

/**
 * @brief The Task class
 * TODO: Add description.
 */
class Task
{
public:
    Task(int id);
    Task(int id, int textId, std::string fromKey, std::string toKey);
    Task(int id, int textId, std::string fromKey, std::string toKey, unsigned long long acceptedTimestamp);
    Task(int id, int textId, std::string fromKey, std::string toKey, unsigned long long acceptedTimestamp, std::string bestKey, double confidence);

    int getId() const;

    int getTextId() const;

    std::string getFromKey() const;

    std::string getToKey() const;

    unsigned long long getAcceptedTimestamp() const;
    void setAcceptedTimestamp(unsigned long long value);

    std::string getBestKey() const;
    void setBestKey(const std::string& value);

    double getConfidence() const;
    void setConfidence(double value);

private:
    const int id;
    int textId;
    std::string fromKey;
    std::string toKey;
    unsigned long long acceptedTimestamp;
    std::string bestKey;
    double confidence;
};

#endif // TASK_H
