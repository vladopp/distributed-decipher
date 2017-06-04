#include <dbmanager.h>
#include <QCoreApplication>
#include <QThread>

#include <iostream>

#include "keygenerator.h"
#include "vigenerecipher.h"
#include "confidenceevaluator.h"
#include "configmanager.h"
#include <string>

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
    bool ok = dbManager->connect();

    if (!ok)
    {
        fprintf(stderr, "Error connecting to the database.");
        a.quit();
        return 1;
    }

    QString encr =  VigenereCipher::encrypt("Ferrari N.V. (pronounced [ferˈrari]) is an Italian sports car manufacturer based in Maranello. Founded by Enzo Ferrari in 1939 as Auto Avio Costruzioni, the company built its first car in 1940. However the company's inception as an auto manufacturer is usually recognized in 1947, when the first Ferrari-badged car was completed.", "ab");
    //std::cout << VigenereCipher::decrypt(encr, "ab") << std::endl;
    dbManager->addNewText(encr);
    int id = dbManager->getTextId(encr);
    Task taskk(id, "ab", "ab");
    //Task taskz(id, "bb", "zz");
    dbManager->addNewTask(taskk);
    //dbManager->addNewTask(taskz);

    printf("Connected to database.\n");
    QString bestKey = "";
    int rounds = 2;
    while (rounds--)
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
            QString fromKey = task.getFromKey();
            QString toKey = task.getToKey();
            int textId = task.getTextId();
            QString text = dbManager->getTextById(textId);
            double maxConfidence = 0.0;

            ConfidenceEvaluator evaluator(":/resources/english-words.txt");
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
                   task.getId(), task.getConfidence(), qPrintable(task.getBestKey()));
        }
        //break;
    }
    printf("%s", qPrintable(VigenereCipher::decrypt(dbManager->getTextById(id), bestKey)));

    dbManager->closeConnection();
    return a.exec();
}
