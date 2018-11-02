#include "FileInfoProvider.h"
#include <stdexcept>
#include <iostream>

struct stat FileInfoProvider::GetPermissions(std::string fileLocation) const
{
    struct stat buf;
    stat(fileLocation.c_str(), &buf);
    return buf;
}

bool FileInfoProvider::Exists(std::string fileLocation) const
{
    struct stat buf;
    return (stat(fileLocation.c_str(), &buf) == 0);
}

void FileInfoProvider::SetPermissions(std::string fileLocation, std::string mode) const
{
    cout << "setting file permissions" << "\n";
    cout << "File is: " << fileLocation << "\n";
    cout << "Mode is: " << mode << "\n";
    //int chmod(const char *path, mode_t mode);
    //int chmod(const char *fileLocation, mode_t mode);
    //int chmod(const char *fileLocation, mode_t 0666 );

}