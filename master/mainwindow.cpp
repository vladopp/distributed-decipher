#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "taskgenerator.h"
#include <QMessageBox>
#include <QString>
#include <QThread>
#include <QPair>
#include <string>
#include <utility>
#include "configmanager.h"
#include "dbmanager.h"
#include "vigenerecipher.h"

mainwindow::mainwindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::mainwindow)
{
    ui->setupUi(this);

    ConfigManager configuration;
    if(!configuration.loadFromFile(":/config.ini"))
    {
        QMessageBox msgBox;
        msgBox.setInformativeText("Error reading configuration from file.");
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.setDefaultButton(QMessageBox::Ok);
        msgBox.exec();
    }

    db = new DBManager(configuration.getHostName(),
                configuration.getDatabaseName(),
                configuration.getUsername(),
                configuration.getPassword());

    if (!db->connect())
    {
        fprintf(stderr, "Error connecting to the database.");
        exit(1);
    }
}

mainwindow::~mainwindow()
{
    delete db;
    delete ui;
}

void mainwindow::on_buttonDecrypt_clicked()
{
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
    QString encryptedText = ui->editEncryptedText->toPlainText().trimmed();

    int textId = db->addNewText(encryptedText);
    if (textId == -1)
    {
        fprintf(stderr, "Error inserting new text into the database.");
        exit(1);
    }
    generateTasks(encryptedText);

    // Update the status of the decrypted text dynamically.
    timer.setInterval(1000);
    // DO NOT TOUCH!!! EXTREMELY FRAFILE!!! :D THAT LAMBDA, THOUGH...
    connect(&timer, &QTimer::timeout, [=]() { update_decryption_status(encryptedText, textId); });
    timer.start();

    // TODO: Add status bar with "Generating" and then change to "Waiting for workers"
    QMessageBox msgBox;
    msgBox.setInformativeText("Done generating tasks. Now it's time to wait for workers to do the work!");
    msgBox.setStandardButtons(QMessageBox::Ok);
    msgBox.setDefaultButton(QMessageBox::Ok);
    msgBox.exec();
}

void mainwindow::generateTasks(QString encryptedText)
{
    int mostProbableKeyLength = getMostProbableKeyLength(encryptedText);
    int startTaskID = 0;
    //int textID = db->getTextId(encryptedText);
    int textID = 1;

    if(mostProbableKeyLength == -1) // didn't find such key
    {
        // brute force all possibilites until the max brute force key length
        const int MAX_BF_KEY_LENGTH = 5;
        for(int keyLength = 1; keyLength < MAX_BF_KEY_LENGTH; keyLength++)
        {
            startTaskID = submitAllKeysWithLength(keyLength, startTaskID, textID) + 1;
        }
    }
    else
    {
        submitAllKeysWithLength(mostProbableKeyLength, startTaskID, textID);
    }
}

int mainwindow::getMostProbableKeyLength(QString encryptedText)
{
    // TODO: Method should be implemented after a meeting with Landjev. Haha...
    return -1;
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
    std::vector< std::pair<QString, QString> > tasks = TaskGenerator::getTasks(keyLength);

    int nextTaskID = startTaskID;
    for(std::pair<QString, QString > taskBounds : tasks)
    {
        Task currentTask(nextTaskID, textID, taskBounds.first, taskBounds.second);

        db->addNewTask(currentTask);

        nextTaskID++;
    }

    return nextTaskID;
}

void mainwindow::update_decryption_status(QString text, int textId)
{
    static int a=0;
    ui->editDecryptedText->setText(QString(a++));

    QPair<QString, double> keyToConfidencePair = db->getBestKey(textId);
    if (keyToConfidencePair.second > 0.1)
    {
        QString decryptedText = VigenereCipher::decrypt(text, keyToConfidencePair.first);
        ui->editDecryptedText->setText(decryptedText);
        timer.stop();
    }
}
