#ifndef TASK_H
#define TASK_H

#include <QString>

/**
 * @brief The Task class
 * TODO: Add description.
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
