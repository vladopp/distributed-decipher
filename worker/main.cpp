#include <dbmanager.h>
#include <QCoreApplication>
#include <QThread>

#include <iostream>

#include "keygenerator.h"
#include "vigenerecipher.h"
#include "confidenceevaluator.h"
#include "configmanager.h"

static const int SECONDS_TIMEOUT = 30;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    ConfigManager configuration;
    if(!configuration.loadFromFile(":/config.ini"))
    {
        fprintf(stderr, "Error reading configuration file.");
    }

    DBManager* dbManager = new DBManager(configuration.getHostName(),
                                         configuration.getDatabaseName(),
                                         configuration.getUsername(),
                                         configuration.getPassword());

    printf("Connecting to database...\n");
    if (!dbManager->connect())
    {
        fprintf(stderr, "Error connecting to the database.");
        a.quit();
        return 1;
    }
    printf("Connected to database.\n");

    ConfidenceEvaluator evaluator(":/resources/english-words.txt");
    while (true)
    {
        Task task = dbManager->getUnprocessedTask();
        if (task.getId() == 0)
        {
            printf("No tasks to process. Sleeping for %d seconds...\n", SECONDS_TIMEOUT);
            QThread::sleep(SECONDS_TIMEOUT);
            continue;
        }

        printf("Got task with id %d. Working on it...\n", task.getId());

        QString fromKey = task.getFromKey();
        QString toKey = task.getToKey();
        int textId = task.getTextId();
        QString text = dbManager->getTextById(textId);
        double maxConfidence = 0.0;
        QString bestKey = "";

        for (QString key = fromKey; key != KeyGenerator::nextPermutation(toKey); key=KeyGenerator::nextPermutation(key))
        {
            QString decipheredText = VigenereCipher::decrypt(text, key);
            double confidence = evaluator.calculateConfidence(decipheredText);
            if (confidence >= maxConfidence)
            {
                maxConfidence = confidence;
                bestKey = key;
            }
        }

        task.setBestKey(bestKey);
        task.setConfidence(maxConfidence);
        dbManager->addTaskResult(task);
        printf("Processed task with id %d. Got score %f with key %s\n",
               task.getId(),
               task.getConfidence(),
               qPrintable(task.getBestKey()));
    }

    dbManager->closeConnection();
    return a.exec();
}
