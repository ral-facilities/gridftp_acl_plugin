#include <Utils.h>
#include <regex>

std::vector<std::string> Utils::StringSplitter(std::string permissionsStr, char delimiter) const
{
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(permissionsStr);
    while (std::getline(tokenStream, token, delimiter))
    {
        tokens.push_back(token);
    }
    return tokens;
}

std::map<std::string, std::string> Utils::SettingsStringToMap(std::string inputSettings) const
{
    // Split on ; to get key-value pairs
    std::vector<std::string> tokens;
    tokens = StringSplitter(inputSettings, ';');

    // Loop over key-value pairs and split on =
    std::map<std::string, std::string> tokenMap;
    for (int i = 0; i < tokens.size(); i++)
    {
        std::vector<std::string> kvp;
        kvp = StringSplitter(tokens[i], '=');
        // put key-value pairs into map
        tokenMap[kvp[0]] = kvp[1];
    }
    return tokenMap;
}