#include "PermissionsSetter.h"
#include <stdexcept>
#include <map>
#include <vector>
#include "IUtils.h"

void PermissionsSetter::SetPermissions(std::string fileLocation, std::string permissions, IUtils* utils, IFileInfoProvider* fileInfoProvider) 
{
    if (!fileInfoProvider->Exists(fileLocation))
    {   
        throw std::runtime_error("File not found");
    }

    std::map<std::string, std::string> permissionsMap;
    try
    {
        permissionsMap = utils->SettingsStringToMap(permissions);
    }
    catch(std::runtime_error const & e)
    {
        throw e;
    }

    int mode = stoi(permissionsMap.find("mode")->second);
    int groupID = stoi(permissionsMap.find("groupID")->second);
    int userID = stoi(permissionsMap.find("userID")->second);

    if (fileInfoProvider->SetMode(fileLocation, mode) != 1 )
    {
        throw std::runtime_error("Failed to set file mode");
    }

    if (fileInfoProvider->SetUserAndGroupID(fileLocation, userID, groupID) != 1 )
    {
        throw std::runtime_error("Failed to set file user and group ID");
    }
}


