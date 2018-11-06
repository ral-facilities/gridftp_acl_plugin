#include "FileInfoProvider.h"
#include <stdexcept>
#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

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
    int status;
    // struct stat buffer;
    // int chmod(const char *path, mode_t mode);
    // chmod((char*)"/tmp/test.txt", 100777);
    // chmod((char*)"/tmp/test.txt", S_IRWXU);
    // chmod((char*)"/tmp/test.txt", 16895);
    chmod((char*)"/tmp/test.txt", mode);
    chmod((char*)"/home/vagrant/TestDir/test.txt", mode);
    // status = stat((char*)"/tmp/test.txt", &buffer);
    // cout << "Mode set to: " << buffer.st_mode << endl;

}

void FileInfoProvider::SetUserAndGroupID(std::string fileLocation, int userID, int groupID) const
{
    cout << "changing ownership and group of test file" << endl;
    cout << "uid before: " << getuid << endl;
    //setuid(0);
    //cout << setuid(0);
    //cout << "uid after: " << getuid << endl;

    cout << userID << " and group: " << groupID << endl;
    //THIS IS THE BIT YOU NEED!
    chown((char*)"/tmp/test.txt", 1234, 1234);
    
    // cout << "Tmp dir: " << chown((char*)"/tmp/test.txt", 1234, 1234);
    // struct stat buf;
    // stat((char*)"/home/vagrant/src/test.txt", &buf);
    // cout << buf.st_gid << endl;
    // cout << buf.st_uid << endl;
    // cout << chown((char*)"/home/vagrant/src/test.txt", 1234, 1234) << endl;
    // cout << 
    // system("echo vagrant | sudo chown 1234:1234 /home/vagrant/TestDir/test.txt");
    // stat((char*)"/home/vagrant/TestDir/test.txt", &buf);
    // cout << buf.st_gid << endl;
    // cout << buf.st_uid << endl;
}
