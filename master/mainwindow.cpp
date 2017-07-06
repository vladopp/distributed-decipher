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
    ui(new Ui::mainwindow),
    timer(0)
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

/**
 * Called when the button for decryption is clicked.
 * @brief mainwindow::on_buttonDecrypt_clicked
 */
void mainwindow::on_buttonDecrypt_clicked()
{
    ui->buttonDecrypt->setEnabled(false);
    ui->editEncryptedText->setReadOnly(true);

QMessageBox msgBox;

    if(ui->editEncryptedText->toPlainText().trimmed() == "")
    {
        // not entered encrypted text, show error message
        msgBox.setInformativeText("Please, at least enter encrypted text! We will do the rest. :)");
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.setDefaultButton(QMessageBox::Ok);
        msgBox.exec();
        return;
    }
    QString encryptedText = ui->editEncryptedText->toPlainText().trimmed();

    int textID = db->addNewText(encryptedText);
    if (textID == -1)
    {
        fprintf(stderr, "Error inserting new text into the database.");
        //update_decryption_status(encryptedText, db->getIdOfText(encryptedText));
        //exit(1);

        textID = db->getIdOfText(encryptedText);

        msgBox.setInformativeText("The same text is already in Database. Now it's time to wait for workers to do the work!");
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.setDefaultButton(QMessageBox::Ok);
        msgBox.exec();
    }
    else
    {
        generateTasks(encryptedText, textID);

        msgBox.setInformativeText("Done generating tasks. Now it's time to wait for workers to do the work!");
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.setDefaultButton(QMessageBox::Ok);
        msgBox.exec();
    }

    timer = new QTimer();
    // Update the status of the decrypted text dynamically.
    timer->setInterval(1000);
    // DO NOT TOUCH!!! EXTREMELY FRAGILE!!! :D THAT LAMBDA, THOUGH...
    connect(timer, &QTimer::timeout, [=]() { update_decryption_status(encryptedText, textID); });
    timer->start();
}

/**
 * @brief mainwindow::generateTasks Generates all tasks for the given text.
 * @param encryptedText Encrypted text for which to generate the tasks. It is needed to check
 * the most probable key length.
 * @param textID Text ID of the encrypted text from the database.
 */
void mainwindow::generateTasks(QString encryptedText, int textID)
{
    int mostProbableKeyLength = getMostProbableKeyLength(encryptedText);
    int startTaskID = 0;

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

/**
 * @brief mainwindow::getMostProbableKeyLength
 * @param encryptedText
 * @return Returns the most probable key length.
 */
int mainwindow::getMostProbableKeyLength(QString encryptedText)
{
    return VigenereCipher::getProbableKeyLength(encryptedText);
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

/**
 * Makes queries to the database with the best key and updates the GUI to show the current
 * best key and its confidence. It also colors the key and confidence according to the level
 * of confidence.
 * If there are no more tasks to wait for, this function stops the timer.
 *
 * @brief mainwindow::update_decryption_status
 * @param text Encrypted text
 * @param textId ID of the encrypted text
 */
void mainwindow::update_decryption_status(QString text, int textId)
{
    timer->stop();

    QPair<QString, double> keyToConfidencePair = db->getBestKey(textId);
    const double confidence = keyToConfidencePair.second;
    const double colorStepsCount = 10;
    const double colorStep = 255/colorStepsCount;
    if (confidence > 0.0)
    {
        QString decryptedText = VigenereCipher::decrypt(text, keyToConfidencePair.first);
        ui->editDecryptedText->setFontPointSize(12);
        ui->editDecryptedText->setText(decryptedText);

        std::string styleSheet = "";
        styleSheet += "font-weight: bold;";
        // calculate color: If confidence is low, the color goes to red, otherwise it goes to green
        styleSheet += ("color: rgb(") +
                std::to_string(255-(confidence * 10.0 * colorStep)) + "," +
                std::to_string((confidence * 10.0 * colorStep)) + "," +
                std::to_string(0) + ");";

        ui->textEditConfidence->setStyleSheet(styleSheet.c_str());
        ui->textEditConfidence->setFontPointSize(12);
        ui->textEditConfidence->setText(QString( std::to_string(confidence).c_str() ));

        ui->textEditKey->setStyleSheet(styleSheet.c_str());
        ui->textEditKey->setFontPointSize(12);
        ui->textEditKey->setText(QString( keyToConfidencePair.first ));
    }

    if(db->hasRemainingTasksForText(textId) == false)
    {
        QMessageBox msgBox;
        msgBox.setInformativeText("All tasks for this text are finished. The best text is shown.");
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.setDefaultButton(QMessageBox::Ok);
        msgBox.exec();

        ui->buttonDecrypt->setEnabled(true);
        ui->editEncryptedText->setReadOnly(false);
    }
    else
    {
        timer->start();
    }
}
