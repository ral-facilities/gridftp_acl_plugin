#include "FileInfoProvider.h"
#include <stdexcept>
#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sstream>
#include <regex>
#include <string>

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

void FileInfoProvider::SetMode(std::string fileLocation, int mode) const
{
    cout << "setting file permissions" << "\n";
    cout << "File is: " << fileLocation << "\n";
    cout << "Mode is: " << mode << "\n";
    // int status;
    // int chmod(const char *path, mode_t mode);
    // chmod((char*)"/tmp/test.txt", 100777);
    // chmod((char*)"/tmp/test.txt", S_IRWXU);
    // chmod((char*)"/tmp/test.txt", 16895);
    chmod((char*)"/tmp/test.txt", mode);
    chmod((char*)"/home/vagrant/TestDir/test.txt", mode);
    // status = stat((char*)"/tmp/test.txt", &buffer);

}

void FileInfoProvider::SetUserAndGroupID(std::string fileLocation, int userID, int groupID) const
{
    cout << "changing ownership and group of test file" << endl;
    cout << "uid before: " << getuid << endl;
    cout << userID << " and group: " << groupID << endl;
    char * tab2 = new char [fileLocation.length()+1];
    strcpy (tab2, fileLocation.c_str());
    chown((char*)tab2, userID, groupID);
}
