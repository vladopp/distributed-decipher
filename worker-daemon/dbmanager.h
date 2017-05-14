#include <QSqlRecord>
#include <QSqlDatabase>

#ifndef DBMANAGER_H
#define DBMANAGER_H


class DBManager
{
public:
    DBManager();
    bool initDbConnection();
    QSqlRecord getFirstUnprocessedTask();
    QString getTextById(int id);
    bool persistTaskResult(QString key, double confidence, QString result, int text_id);
    void closeDbConnection();

private:
    QSqlDatabase db;
};


#endif // DBMANAGER_H
