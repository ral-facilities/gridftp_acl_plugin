#include "PermissionsReader.h"
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
        std::string basicPermissions = "mode=" + std::to_string(buf.st_mode) + 
                                    ";userID=" + std::to_string(buf.st_uid) +
                                    ";groupID=" + std::to_string(buf.st_gid);
        return basicPermissions;
    }
    else
    {
        throw std::runtime_error("Permissions not found");
    }
}
