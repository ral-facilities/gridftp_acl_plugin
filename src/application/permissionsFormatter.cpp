#include "permissionsFormatter.h"
#include "permissionsReader.h"
#include <sys/stat.h>
#include <iostream>

//std::string PermissionsReader::GetPermissions(std::string fileLocation)
std::string PermissionsFormatter::ToString(std::string fileLocation) 
{
    static PermissionsReader permissionsReader;
    struct stat buf = permissionsReader.GetPermissions(fileLocation);
    std::string basicPermissions = "mode: " + std::to_string(buf.st_mode) + 
                                    " groupID: " + std::to_string(buf.st_gid) +
                                    " userID: " + std::to_string(buf.st_uid) +
                                    "\n";
    return basicPermissions;
}