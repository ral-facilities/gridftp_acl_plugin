#include "permissionsReader.h"
#include <sys/stat.h>
#include <iostream>

//std::string PermissionsReader::GetPermissions(std::string fileLocation)
struct stat PermissionsReader::GetPermissions(std::string fileLocation) 
{
    struct stat buf;
    stat(fileLocation.c_str(), &buf);
    return buf;
}

//std::string PermissionsReader:
    //cout << "\nGetting permissions for: " << fileLocation << endl;
    // cout << buf.st_mode << endl;
    // cout << buf.st_dev << endl;
    // cout << buf.st_ino << endl;
    // cout << buf.st_mode << endl;
    // cout << buf. st_nlink << endl;
    // cout << buf.st_uid << endl;
    // cout << buf.st_gid << endl;
    // cout << buf.st_blksize << endl;
    // cout << buf.st_size << endl;
    // cout << buf.st_blocks << endl;
    // cout << buf.st_ctime << endl;
    // cout << buf.st_atime << endl;
    // cout << buf.st_mtime << endl;
    // cout << "\nDone\n" << endl;
    //int statchmod = buf.st_mode & (S_IRWXU | S_IRWXG | S_IRWXO);