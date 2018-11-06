#include "permissionsSetter.h"
#include <sys/stat.h>
#include <stdexcept>
#include "IFileInfoProvider.h"
#include <vector>
#include <sstream>
#include <iostream>
#include <string>
#include <map>
#include <regex>

void PermissionsSetter::SetPermissions(std::string fileLocation, std::string permissions, IFileInfoProvider* fileInfoProvider) 
{
    cout << "Attempting to change files permissions" << endl;
    if (fileInfoProvider->Exists(fileLocation))
    {   
        cout << "Permissions: " << permissions << endl;

        std::vector<std::string> tokens;
        std::string token;
        std::istringstream tokenStream(permissions);
        while (std::getline(tokenStream, token, ';'))
        {
            char * tab2 = new char [token.length()+1];
            strcpy (tab2, token.c_str());
            char * pch;
            pch = strtok(tab2, "=");
            while (pch != NULL)
            {
                tokens.push_back(pch);
                pch = strtok (NULL, "=");
            }
            

        }
        std::cout << "Number of tokens: " << tokens.size() << std::endl;
 
        std::map<std::string, int> permissionsMap;
        for (int i = 0; i < tokens.size()-1; i++)
        {
            permissionsMap[tokens[i]] = atoi(tokens[i+1].c_str());
            cout << tokens[i] << " " << tokens[i+1];
            i++;
        }

        int mode = permissionsMap.find("mode")->second;
        cout << "Mode value is: " << mode << endl;
        fileInfoProvider->SetMode(fileLocation, mode);

        int groupID = permissionsMap.find("groupID")->second;
        int userID = permissionsMap.find("userID")->second;
        cout << "File Location: " << fileLocation << endl;
        cout << "Group: " << groupID << " User: " << userID << endl;
        fileInfoProvider->SetUserAndGroupID(fileLocation, userID, groupID);
    }
    else
    {
        throw std::runtime_error("Failed to set permissions");
    }
}
