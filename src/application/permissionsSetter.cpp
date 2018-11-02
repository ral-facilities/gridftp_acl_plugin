#include "permissionsSetter.h"
#include <sys/stat.h>
#include <iostream>
#include <stdexcept>
#include "IFileInfoProvider.h"
#include <vector>
#include <sstream>

void PermissionsSetter::SetPermissions(std::string fileLocation, std::string permissions, IFileInfoProvider* fileInfoProvider) 
{
    cout << "Attempting to change files permissions" << endl;
    if (fileInfoProvider->Exists(fileLocation))
    {   
        std::string mode = "1000000";

        // split permissions string
        std::vector<std::string> tokens;
        std::string token;
        std::istringstream tokenStream(permissions);
        while (std::getline(tokenStream, token, ', '))
        {
            tokens.push_back(token);

        }
        std::cout << tokens.size() << std::endl;


        fileInfoProvider->SetPermissions(fileLocation, mode);
    //     struct stat buffer;
    //     struct stat buf = fileInfoProvider->GetPermissions(fileLocation);
    //     std::string basicPermissions = "mode: " + std::to_string(buf.st_mode) + 
    //                                 " groupID: " + std::to_string(buf.st_gid) +
    //                                 " userID: " + std::to_string(buf.st_uid);
    //     return basicPermissions;
    }
    else
    {
        throw std::runtime_error("Failed to set permissions");
    }
}
