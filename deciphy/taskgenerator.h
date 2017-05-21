#ifndef TASKGENERATOR_H
#define TASKGENERATOR_H

#include <vector>
#include <string>

class TaskGenerator
{
public:

    static std::vector< std::pair<std::string, std::string> > getTasks( size_t keyLength );
private:
    static std::string getUpperBound(std::string lowerBound);
};

#endif // TASKGENERATOR_H
