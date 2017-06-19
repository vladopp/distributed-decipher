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
    QString getDictionaryPath() const;
    int getTimeoutSeconds() const;
    int getAllowedTries() const;

private:
    QString hostName;
    QString databaseName;
    QString username;
    QString password;
    QString dictionaryPath;
    int timeout_seconds;
    int allowed_tries;
};

#endif // CONFIGMANAGER_H
