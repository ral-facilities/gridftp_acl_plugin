#include <Utils.h>
#include <regex>

char* Utils::StringToCharArray(std::string input)
{
    char * charArray = new char [input.length()+1];
    strcpy (charArray, input.c_str());
    return charArray;
}

std::vector<std::string> Utils::StringSplitter(std::string permissionsStr, std::string delimiter1, std::string delimiter2)
{
    char delim1 = Utils::StringToCharArray(delimiter1)[0];
    char* delim2 = Utils::StringToCharArray(delimiter2);
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(permissionsStr);
    while (std::getline(tokenStream, token, delim1))
    {
        char * tab2 = new char [token.length()+1];
        strcpy (tab2, token.c_str());
        char * pch;
        pch = strtok(tab2, delim2);
        while (pch != NULL)
        {
            tokens.push_back(pch);
            pch = strtok (NULL, delim2);
        }
    }
    return tokens;
}

std::map<std::string, std::string> Utils::TokensToMap(std::vector<std::string> tokens)
{
    std::map<std::string, std::string> tokenMap;
    for (int i = 0; i < tokens.size()-1; i++)
    {

        tokenMap[tokens[i]] = tokens[i+1];
       i++;
    }
    return tokenMap;
}