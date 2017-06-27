#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDialog>
#include <QTimer>
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

public slots:
    void on_buttonDecrypt_clicked();
    void update_decryption_status(QString text, int text_id);

private:
    Ui::mainwindow *ui;
    DBManager *db;
    QTimer *timer;

    void generateTasks(QString encryptedText, int textID);
    int getMostProbableKeyLength(QString encryptedText);
    int submitAllKeysWithLength(int keyLength, int startTaskID, int textID);
};

#endif // MAINWINDOW_H
