#include "configmanager.h"
#include <QSettings>

/**
 * @brief ConfigManager::ConfigManager empty constructor.
 */
ConfigManager::ConfigManager()
{
}

/**
 * @brief ConfigManager::loadFromFile Loads a configuration from file in .ini format.
 * @param filePath Path of the configuration file.
 * @return true if the configuration is loaded successfully, false if some error occured.
 */
bool ConfigManager::loadFromFile(QString filePath)
{
    QSettings configurationFile(filePath, QSettings::IniFormat);

    hostName = configurationFile.value("hostName").toString();
    databaseName = configurationFile.value("databaseName").toString();
    username = configurationFile.value("username").toString();
    password = configurationFile.value("password").toString();
    dictionaryPath = configurationFile.value("dictionary_path").toString();
    timeout_seconds = configurationFile.value("timeout_seconds").toInt();
    allowed_tries = configurationFile.value("allowed_tries").toInt();

    return configurationFile.status() == QSettings::NoError;
}

/**
 * @brief ConfigManager::getHostName
 * @return the host name of the database
 */
QString ConfigManager::getHostName() const
{
    return hostName;

}

/**
 * @brief ConfigManager::getDatabaseName
 * @return the name of the database
 */
QString ConfigManager::getDatabaseName() const
{
    return databaseName;

}

/**
 * @brief ConfigManager::getUsername
 * @return the username used for the database
 */
QString ConfigManager::getUsername() const
{
    return username;

}

/**
 * @brief ConfigManager::getPassword
 * @return the password used for the database
 */
QString ConfigManager::getPassword() const
{
    return password;
}

/**
 * @brief ConfigManager::getDictionaryPath
 * @return the path to the provided dictionary
 */
QString ConfigManager::getDictionaryPath() const
{
    return dictionaryPath;
}

/**
 * @brief ConfigManager::getTimeoutSeconds
 * @return the timeout in seconds used in the worker process
 */
int ConfigManager::getTimeoutSeconds() const
{
    return timeout_seconds;
}

/**
 * @brief ConfigManager::getAllowedTries
 * @return the number of allowed tries of the worker before shutting down
 */
int ConfigManager::getAllowedTries() const
{
    return allowed_tries;
}
