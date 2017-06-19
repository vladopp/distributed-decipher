#include "configmanager.h"
#include <QSettings>

ConfigManager::ConfigManager()
{
}

bool ConfigManager::loadFromFile(QString filename)
{
    QSettings configurationFile(filename, QSettings::IniFormat);

    hostName = configurationFile.value("hostName").toString();
    databaseName = configurationFile.value("databaseName").toString();
    username = configurationFile.value("username").toString();
    password = configurationFile.value("password").toString();
    dictionaryPath = configurationFile.value("dictionary_path").toString();
    timeout_seconds = configurationFile.value("timeout_seconds").toInt();
    allowed_tries = configurationFile.value("allowed_tries").toInt();

    return true;
}

QString ConfigManager::getHostName() const
{
    return hostName;

}

QString ConfigManager::getDatabaseName() const
{
    return databaseName;

}

QString ConfigManager::getUsername() const
{
    return username;

}

QString ConfigManager::getPassword() const
{
    return password;
}

QString ConfigManager::getDictionaryPath() const
{
    return dictionaryPath;
}

int ConfigManager::getTimeoutSeconds() const
{
    return timeout_seconds;
}

int ConfigManager::getAllowedTries() const
{
    return allowed_tries;
}
