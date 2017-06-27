#include <dbmanager.h>
#include <QCoreApplication>
#include <QThread>
#include <QString>

#include "keygenerator.h"
#include "vigenerecipher.h"
#include "confidenceevaluator.h"
#include "configmanager.h"

static const QString CONFIG_FILE_PATH=":/config.ini";

/**
 * @brief loadConfiguration Loads the configuration persisted in the config file.
 * @return fully initialized ConfigManager object.
 */
ConfigManager loadConfiguration()
{
    ConfigManager configuration;
    if(!configuration.loadFromFile(CONFIG_FILE_PATH))
    {
        fprintf(stderr, "Failed to load configuration from %s. Closing the applicatoin.\n", qPrintable(CONFIG_FILE_PATH));
        exit(1);
    }
    return configuration;
}

/**
 * @brief connectDb Creates and initializes DBManager object connected to the specified database.
 * @param hostName the host name of the database
 * @param databaseName the name of the database
 * @param username username with access to the database
 * @param password password of the username
 * @return DBManager object connected to a database ready for use.
 */
DBManager connectDb(const QString& hostName, const QString& databaseName, const QString& username, const QString& password)
{
    DBManager dbManager(hostName, databaseName, username, password);
    printf("Connecting to database...\n");
    if (!dbManager.connect())
    {
        fprintf(stderr, "Failed to connect to database %s. Closing the applcation.\n", qPrintable(hostName));
        exit(1);
    }
    printf("Connected to database.\n");
    return dbManager;
}

/**
 * @brief processTask Processes a task. It will try to decrypt the text with every key specified in the interval
 * [fromKey, toKey] and update the task entry with the best key and its confidence score.
 * @param evaluator ConfidenceEvaluator object used to calculate the confidence score
 * @param task Task object containing the task information.]
 * @param dbManager DBManager object used for db connection
 */
void processTask(const ConfidenceEvaluator& evaluator, Task& task, DBManager& dbManager)
{
    QString text = dbManager.getTextById(task.getTextId());
    double maxConfidence = 0.0;
    QString bestKey = "";

    for (QString key = task.getFromKey(); key != KeyGenerator::nextPermutation(task.getToKey()); key=KeyGenerator::nextPermutation(key))
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
    dbManager.addTaskResult(task);
    printf("Processed task with id %d. Got score %f with key %s.\n", task.getId(), task.getConfidence(), qPrintable(task.getBestKey()));
}

/**
 * @brief printWelcomeMessage Prints welcome message on the standard output.
 */
void printWelcomeMessage() {
    printf("WELCOME TO DECIPHY 2000\n"
"                -. .                                        \n"
"           _____   ',' ,                                    \n"
"         ,'     ,'   ', ',                                  \n"
"       ,'     ,'      |  |                                  \n"
"      \\       \\       |  |                                  \n"
"        \\ /^\\   \\    ,' ,'                                  \n"
"              \\   \\ ,' ,'                                   \n"
"        / ~-.___\\.-'  ,'                                    \n"
"      /   .______.- ~ \\                                     \n"
"    /   /'          \\   \\                                   \n"
"    \\./               \\/'  \n\n");
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    printWelcomeMessage();
    ConfigManager configuration = loadConfiguration();
    DBManager dbManager = connectDb(configuration.getHostName(),
                                    configuration.getDatabaseName(),
                                    configuration.getUsername(),
                                    configuration.getPassword());
    ConfidenceEvaluator evaluator(configuration.getDictionaryPath());

    int tries = 0;
    int allowed_tries = configuration.getAllowedTries();
    int timeout_seconds = configuration.getTimeoutSeconds();
    while (tries < allowed_tries)
    {
        Task task = dbManager.getUnprocessedTask();
        if (task.getId() == 0)
        {
            printf("No tasks to process. Sleeping for %d seconds...\n", timeout_seconds);
            tries++;
            QThread::sleep(timeout_seconds);
            continue;
        }
        tries = 0;

        printf("Got task with id %d. Working on it...\n", task.getId());
        processTask(evaluator, task, dbManager);
    }

    printf("Did not find any unprocessed tasks for the last %d seconds. Closing the application.\n", allowed_tries * timeout_seconds);
    dbManager.closeConnection();
    exit(0);

    return a.exec();
}
