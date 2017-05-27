#include <dbmanager.h>
#include <QCoreApplication>
#include <QSqlDatabase>
#include <QSqlRecord>
#include <QVariant>
#include <QThread>

#include <iostream>

#include <keygenerator.h>
#include <vigenerecipher.h>
#include <confidenceevaluator.h>

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
        Task task = dbManager->getUnprocessedTask();
        if (task.getId() == 0)
        {
            printf("No tasks to process. Sleeping for 30 seconds...\n");
            QThread::sleep(30);
            continue;
        } else
        {
            printf("Got task with id %d. Working on it...\n", task.getId());
            std::string fromKey = task.getFromKey();
            std::string toKey = task.getToKey();
            int textId = task.getTextId();
            std::string text = dbManager->getTextById(textId);
            double maxConfidence = 0.0;
            std::string bestKey = "";
            ConfidenceEvaluator evaluator("D:\\Education\\NBU\\Semester 6\\NETB380 (Programming Practice)\\distributed-decipher\\worker\\resources\\english-words.txt");
            for (std::string key = fromKey; key != KeyGenerator::nextPermutation(toKey); key=KeyGenerator::nextPermutation(key))
            {
                std::string decipheredText = VigenereCipher::decrypt(text, key);
                double confidence = evaluator.calculateConfidence(decipheredText);
                if (confidence > maxConfidence)
                {
                    maxConfidence = confidence;
                    bestKey = key;
                }
            }
            task.setBestKey(bestKey);
            task.setConfidence(maxConfidence);
            dbManager->persistTaskResult(task);
            printf("Processed task with id %d. Got score %f with key %s\n", task.getId(), task.getConfidence(), task.getBestKey().c_str());
        }
    }

    dbManager->closeDbConnection();
    return a.exec();
}
