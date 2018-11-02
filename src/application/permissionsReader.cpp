#include "permissionsReader.h"
#include <sys/stat.h>
#include <iostream>
#include "IFileInfoProvider.h"

std::string PermissionsReader::GetPermissions(std::string fileLocation, IFileInfoProvider* fileInfoProvider) 
{
    
    struct stat buf = fileInfoProvider->GetPermissions(fileLocation);

    if ( buf.st_mode != 0 )
    {
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
