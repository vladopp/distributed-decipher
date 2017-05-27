#include <QSqlRecord>
#include <QSqlDatabase>
#include <task.h>

#ifndef DBMANAGER_H
#define DBMANAGER_H


class DBManager
{
public:
    DBManager();
    bool initDbConnection(); //TODO move to the constructor?
    Task getUnprocessedTask();
    std::string getTextById(int id);
    void persistTaskResult(const Task& task);
    void addNewTask(const Task& task);
    void closeDbConnection(); //TODO move to destructor?
private:
    QSqlDatabase db;
};


#endif // DBMANAGER_H
