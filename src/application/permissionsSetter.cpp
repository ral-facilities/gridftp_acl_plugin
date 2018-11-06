#include "permissionsSetter.h"
#include <sys/stat.h>
#include <stdexcept>
#include "IFileInfoProvider.h"
#include <vector>
#include <sstream>
#include <iostream>
#include <regex>
#include <string>
#include <map>

void PermissionsSetter::SetPermissions(std::string fileLocation, std::string permissions, IFileInfoProvider* fileInfoProvider) 
{
    cout << "Attempting to change files permissions" << endl;
    if (fileInfoProvider->Exists(fileLocation))
    {   
        // input string: "250 PERMISSIONS: mode: 16895 groupID: 1000 userID: 1000"
        // const std::string prefix = "250 PERMISSIONS: ";
        // if ( permissions.substr(0, 16) == prefix)
        // {
            // permissions.substr(17, permissions.size());
        // }
        // else
        // {
            // throw std::runtime_error("Failed to set permissions");
        // }

        permissions = permissions.substr(17, permissions.size()); // Remove "250 PERMISSIONS: " prefix

        std::vector<std::string> tokens;
        std::string token;
        std::istringstream tokenStream(permissions);
        while (std::getline(tokenStream, token, ' '))
        {
            tokens.push_back(token);
        }
        // std::cout << "Number of tokens: " << tokens.size() << std::endl;

        std::map<std::string, std::string> permissionsMap;
         for (int i = 0; i < tokens.size()-1; i++)
        {
            std::string key = std::string(tokens[i].substr(0, tokens[i].size()-1)); // knock off the last char ":"
            std::string val = std::string(tokens[i+1]);
            permissionsMap[key]=val;
            i++;
        }

        int mode = std::stoi(permissionsMap.find("mode")->second);
        fileInfoProvider->SetMode(fileLocation, mode);

        // this is now user and groupID
        // needs to be modified so that this is got from the user input string from
        // SITE SETPERMISSIONS abcd
        fileInfoProvider->SetUserAndGroupID(fileLocation, 1234, 1234);
        // struct stat buffer;
        // struct stat buf = fileInfoProvider->GetPermissions(fileLocation);
        // std::string basicPermissions = "mode: " + std::to_string(buf.st_mode) + 
                                    // " groupID: " + std::to_string(buf.st_gid) +
                                    // " userID: " + std::to_string(buf.st_uid);
        // return basicPermissions;
    }
    else
    {
        throw std::runtime_error("Failed to set permissions");
    }
}
