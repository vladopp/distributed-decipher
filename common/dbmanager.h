#include <QSqlDatabase>
#include <task.h>

#ifndef DBMANAGER_H
#define DBMANAGER_H


class DBManager
{
public:
    DBManager(std::string host, std::string database, std::string username, std::string password);
    bool connect();
    Task getUnprocessedTask();
    std::string getTextById(int id);
    int getTextId(const std::string& text);
    void addTaskResult(const Task& task);
    void addNewTask(const Task& task);
    void addNewText(const std::string& text);
    void closeConnection();
private:
    QSqlDatabase db;
    const std::string host;
    const std::string database;
    const std::string username;
    const std::string password;
};


#endif // DBMANAGER_H
