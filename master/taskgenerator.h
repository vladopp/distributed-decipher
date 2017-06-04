#ifndef TASKGENERATOR_H
#define TASKGENERATOR_H

#include <vector>
#include <QString>

class TaskGenerator
{
public:
    static std::vector< std::pair<QString, QString> > getTasks( size_t keyLength );
private:
    static QString getUpperBound(QString lowerBound);
};

#endif // TASKGENERATOR_H
