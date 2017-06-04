#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDialog>
#include "dbmanager.h"

namespace Ui {
class mainwindow;
}

class mainwindow : public QDialog
{
    Q_OBJECT

public:
    explicit mainwindow(QWidget *parent = 0);
    ~mainwindow();

private slots:
    void on_buttonDecrypt_clicked();

private:
    Ui::mainwindow *ui;
    DBManager *db;

    void generateTasks(std::string encryptedText);
    int getMostProbableKeyLength(std::string encryptedText);
    void watchDecryptedTextStatus();
    int submitAllKeysWithLength(int keyLength, int startTaskID, int textID);
};

#endif // MAINWINDOW_H
