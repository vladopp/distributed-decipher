#ifndef TASK_H
#define TASK_H

#include <QString>

/**
 * @brief The Task class
 *
 * This class represents a task to be processed by a worker instance.
 * It contains information about the id of the task, the id of the text that is processed,
 * the starting and ending key of the sequence, the accepted timestamp of the task if it is
 * accepted by a worker, the key that produced the best confidence score if the task is processed
 * and the confidence score of the best key if the task is processed.
 * Objects created for inserting into the db should use the constructor without id, because the
 * id will be generated from the database.
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
    const int textId;
    const QString fromKey;
    const QString toKey;
    unsigned long long acceptedTimestamp;
    QString bestKey;
    double confidence;
};

#endif // TASK_H
