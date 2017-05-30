#include "configmanager.h"

ConfigManager::ConfigManager()
{
}

bool ConfigManager::loadFromFile(std::string filename)
{
    std::ifstream configurationFile(filename);
    if(configurationFile.bad())
    {
        return false;
    }

    std::map<std::string,std::string> paramToValue;

    loadIntoMap(configurationFile, paramToValue);

    driver = paramToValue["driver"];
    hostName = paramToValue["hostName"];
    databaseName = paramToValue["databaseName"];
    username = paramToValue["username"];
    password = paramToValue["password"];

    configurationFile.close();

    return true;
}

void ConfigManager::loadIntoMap(std::ifstream &input, std::map<std::string,std::string> &paramToValue)
{
    // Expected file format:
    // param1=value1
    // param2=value2
    // ....
    std::string line;
    while(input >> line)
    {
        size_t equalityPos = line.find('=');
        std::string param = line.substr(0, equalityPos);
        std::string value = line.substr(equalityPos + 1, line.size());

        paramToValue[param] = value;
    }
}

std::string ConfigManager::getDriver() const
{
    return driver;
}
std::string ConfigManager::getHostName() const
{
    return hostName;

}
std::string ConfigManager::getDatabaseName() const
{
    return databaseName;

}
std::string ConfigManager::getUsername() const
{
    return username;

}
std::string ConfigManager::getPassword() const
{
    return password;
}
