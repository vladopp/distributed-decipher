#ifndef TASK_H
#define TASK_H

#include <QString>

/**
 * @brief The Task class
 *
 * This class represents a task to be processed by a worker instance.
 * It accepts the range of keys it needs to test and
 * calculates the confidence score for each one.
 */
class Task
{
public:
    Task(int id);
    Task(int textId, QString fromKey, QString toKey);
    Task(int id, int textId, QString fromKey, QString toKey);
    Task(int id, int textId, QString fromKey, QString toKey, unsigned long long acceptedTimestamp);
    Task(int id, int textId, QString fromKey, QString toKey, unsigned long long acceptedTimestamp, QString bestKey, double confidence);

    int getId() const;

    int getTextId() const;

    QString getFromKey() const;

    QString getToKey() const;

    unsigned long long getAcceptedTimestamp() const;
    void setAcceptedTimestamp(unsigned long long value);

    QString getBestKey() const;
    void setBestKey(const QString& value);

    double getConfidence() const;
    void setConfidence(double value);

private:
    const int id;
    int textId;
    QString fromKey;
    QString toKey;
    unsigned long long acceptedTimestamp;
    QString bestKey;
    double confidence;
};

#endif // TASK_H
