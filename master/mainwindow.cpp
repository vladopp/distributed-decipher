#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "taskgenerator.h"
#include <QMessageBox>
#include <QString>
#include <string>
#include <utility>
#include "configmanager.h"
#include "dbmanager.h"

mainwindow::mainwindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::mainwindow)
{
    ui->setupUi(this);

    ConfigManager configuration;
    if(configuration.loadFromFile("config.ini"))
    {
        QMessageBox msgBox;
        msgBox.setInformativeText("Error reading configuration from file.");
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.setDefaultButton(QMessageBox::Ok);
        msgBox.exec();
    }

    DBManager *dbManager = new DBManager();
    printf("Connecting to database...\n");
    bool ok = dbManager->initDbConnection(
                configuration.getDriver(),
                configuration.getHostName(),
                configuration.getDatabaseName(),
                configuration.getUsername(),
                configuration.getPassword());

    if (!ok)
    {
        QMessageBox msgBox;
        msgBox.setInformativeText("Error connecting to the database.");
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.setDefaultButton(QMessageBox::Ok);
        msgBox.exec();
        close();
    }
}

mainwindow::~mainwindow()
{
    delete ui;
}

void mainwindow::on_buttonDecrypt_clicked()
{
    // TODO: This check should be removed and add binding to the button and the text content of the Edit object
    // P.S: If it is too much work, just leave it as it is. :)
    if(ui->editEncryptedText->toPlainText().trimmed() == "")
    {
        // not entered encrypted text, show error message
        QMessageBox msgBox;
        msgBox.setInformativeText("Please, at least enter encrypted text! We will do the rest. :)");
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.setDefaultButton(QMessageBox::Ok);
        msgBox.exec();
        return;
    }
    std::string encryptedText = ui->editEncryptedText->toPlainText()
            .trimmed()
            .toStdString();

    // TODO: This method should be called in seperate thread.
    // Reason: We must update the status of the decrypted text dynamically.
    generateTasks(encryptedText);

    // TODO: This method should be called in seperate thread.
    // Reason: We must update the status of the decrypted text dynamically.
    watchDecryptedTextStatus();

    // TODO: Add status bar with "Generating" and then change to "Waiting for workers"
    QMessageBox msgBox;
    msgBox.setInformativeText("Done generating tasks. Now it's time to wait for workers to do the work!");
    msgBox.setStandardButtons(QMessageBox::Ok);
    msgBox.setDefaultButton(QMessageBox::Ok);
    msgBox.exec();
}

void mainwindow::generateTasks(std::string encryptedText)
{
    int mostProbableKeyLength = getMostProbableKeyLength(encryptedText);
    int startTaskID = 0;
    int textID = db.getTextID();

    if(mostProbableKeyLength == -1) // didn't find such key
    {
        // brute force all possibilites until the max brute force key length
        const int MAX_BF_KEY_LENGTH = 10;
        for(int keyLength = 1; keyLength < MAX_BF_KEY_LENGTH; keyLength++)
        {
            startTaskID = submitAllKeysWithLength(keyLength, startTaskID, textID) + 1;
        }
    }
    else
    {
        (void) submitAllKeysWithLength(mostProbableKeyLength, startTaskID, textID);
    }
}

int mainwindow::getMostProbableKeyLength(std::string encryptedText)
{
    // TODO: Method should be implemented after a meeting with Landjev. Haha...
    return -1;
}

void mainwindow::watchDecryptedTextStatus()
{
    // TODO: Implement queries to the DB to refresh the status of the decrypted text.
}

/**
 * @brief mainwindow::submitAllKeysWithLength
 * @param keyLength
 * @param startTaskID
 * @param textID
 * @return Returns the last generated task ID.
 */
int mainwindow::submitAllKeysWithLength(int keyLength, int startTaskID, int textID)
{
    // TODO: Perhaps do a producer-consumer pattern instead of returning the whole vector?
    std::vector< std::pair<std::string, std::string> > tasks = TaskGenerator::getTasks(keyLength);

    int nextTaskID = startTaskID;
    for(std::pair<std::string, std::string > taskBounds : tasks)
    {
        Task currentTask(nextTaskID, textID, taskBounds.first, taskBounds.second);

        // TODO: Submit currentTask to DB.

        nextTaskID++;
    }

    return nextTaskID;
}
