#ifndef CONFIGMANAGER_H
#define CONFIGMANAGER_H

#include <QString>

class ConfigManager
{
public:
    ConfigManager();

    bool loadFromFile(QString filename);
    QString getHostName() const;
    QString getDatabaseName() const;
    QString getUsername() const;
    QString getPassword() const;

private:
    QString hostName;
    QString databaseName;
    QString username;
    QString password;
};

#endif // CONFIGMANAGER_H
