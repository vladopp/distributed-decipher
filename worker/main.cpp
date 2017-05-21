#include <dbmanager.h>
#include <QCoreApplication>
#include <QSqlDatabase>
#include <QSqlRecord>
#include <QVariant>
#include <QThread>

#include <iostream>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    DBManager *dbManager = new DBManager();
    printf("Connecting to database...\n");
    bool ok = dbManager->initDbConnection();

    if (!ok)
    {
        fprintf(stderr, "Error connecting to the database.");
        a.quit();
        return 1;
    }

    printf("Connected to database.\n");


    while (true)
    {
        QSqlRecord taskRecord = dbManager->getFirstUnprocessedTask();
        if (taskRecord.value("id").toInt() == 0) {
            printf("No tasks to process. Sleeping for 30 seconds...\n");
            QThread::sleep(30);
            continue;
        } else
        {
            printf("Got task with id %d. Working on it...\n", taskRecord.value("id").toInt());
        }

        QString text = dbManager->getTextById(taskRecord.value("text_id").toInt());
        qInfo("Got text %s\n", qPrintable(text));


        // call function to execute task


        dbManager->persistTaskResult("key", 100.0, "text", taskRecord.value("text_id").toInt());
    }

    dbManager->closeDbConnection();
    return a.exec();
}
