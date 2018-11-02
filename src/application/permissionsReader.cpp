#include "permissionsReader.h"
#include <sys/stat.h>
#include <iostream>
#include <stdexcept>
#include "IFileInfoProvider.h"

std::string PermissionsReader::GetPermissions(std::string fileLocation, IFileInfoProvider* fileInfoProvider) 
{

    if (fileInfoProvider->Exists(fileLocation))
    {
        struct stat buffer;
        struct stat buf = fileInfoProvider->GetPermissions(fileLocation);
        std::string basicPermissions = "mode: " + std::to_string(buf.st_mode) + 
                                    " groupID: " + std::to_string(buf.st_gid) +
                                    " userID: " + std::to_string(buf.st_uid);
        return basicPermissions;
    }
    else
    {
        throw std::runtime_error("Permissions not found");
    }
}
