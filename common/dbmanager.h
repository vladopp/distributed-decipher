#include <QSqlDatabase>
#include <task.h>

#ifndef DBMANAGER_H
#define DBMANAGER_H


class DBManager
{
public:
    DBManager(QString host, QString database, QString username, QString password);
    bool connect();
    Task getUnprocessedTask();
    QString getTextById(int id);
    int getTextId(const QString& text);
    void addTaskResult(const Task& task);
    void addNewTask(const Task& task);
    void addNewText(const QString& text);
    void closeConnection();
private:
    QSqlDatabase db;
    const QString host;
    const QString database;
    const QString username;
    const QString password;
};


#endif // DBMANAGER_H
