#ifndef CONFIGMANAGER_H
#define CONFIGMANAGER_H

#include <map>
#include <fstream>
#include <string>

class ConfigManager
{
public:
    ConfigManager();

    bool loadFromFile(std::string filename);
    std::string getDriver() const;
    std::string getHostName() const;
    std::string getDatabaseName() const;
    std::string getUsername() const;
    std::string getPassword() const;

private:
    std::string driver;
    std::string hostName;
    std::string databaseName;
    std::string username;
    std::string password;

    void loadIntoMap(std::ifstream &input, std::map<std::string,std::string> &paramToValue);
};

#endif // CONFIGMANAGER_H
