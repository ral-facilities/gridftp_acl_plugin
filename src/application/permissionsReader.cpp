#include "permissionsReader.h"
#include <sys/stat.h>
#include <iostream>
#include "IFileInfoProvider.h"

std::string PermissionsReader::GetPermissions(std::string fileLocation, IFileInfoProvider* fileInfoProvider) 
{
    
    struct stat buf = fileInfoProvider->GetPermissions(fileLocation);
    cout << buf.st_mode << endl;
    cout << buf.st_gid << endl;
    cout << buf.st_uid << endl;
    if ( buf.st_mode & S_IFREG )
    {
        std::string basicPermissions = "mode: " + std::to_string(buf.st_mode) + 
                                    " groupID: " + std::to_string(buf.st_gid) +
                                    " userID: " + std::to_string(buf.st_uid);
        return basicPermissions;
        // File found
    }
    // else if (buf.st_mode & S_IFDIR )
    // {
    //     // Directory found
    // }
    else
    {
        throw std::runtime_error("File not found");
    }
}
