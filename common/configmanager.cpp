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
