#include "PermissionsSetter.h"
#include <stdexcept>
#include <vector>
#include <map>
#include "Utils.h"

void PermissionsSetter::SetPermissions(std::string fileLocation, std::string permissions, IFileInfoProvider* fileInfoProvider) 
{
    if (!fileInfoProvider->Exists(fileLocation))
    {   
        throw std::runtime_error("File not found");
    }
    Utils utils;
    std::vector<std::string> tokens;
    std::map<std::string, std::string> permissionsMap;
    int mode;
    int groupID;
    int userID;

    try
    {
        // Split the users input string and put values into a map
        tokens = utils.StringSplitter(permissions, ";", "=");
        permissionsMap = utils.TokensToMap(tokens);
        mode = atoi(permissionsMap.find("mode")->second.c_str());
        groupID = atoi(permissionsMap.find("groupID")->second.c_str());
        userID = atoi(permissionsMap.find("userID")->second.c_str());
    }
    catch (std::exception& e)
    {
        throw std::runtime_error("Failed to read permissions");
    }

    if (fileInfoProvider->SetMode(fileLocation, mode) != 1 )
    {
        throw std::runtime_error("Failed to set file mode");
    }
    
    if (fileInfoProvider->SetUserAndGroupID(fileLocation, userID, groupID) != 1 )
    {
        throw std::runtime_error("Failed to set file user and group ID");
    }
}


