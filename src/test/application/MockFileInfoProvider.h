#ifndef MOCK_FileInfoProvider_H
#define MOCK_FileInfoProvider_H

#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "../../application/IFileInfoProvider.h"
using namespace std;

class MockFileInfoProvider : public IFileInfoProvider {
 public:
   MOCK_CONST_METHOD1(GetPermissions, struct stat(std::string fileLocation));
   MOCK_CONST_METHOD1(Exists, bool (std::string fileLocation));
   MOCK_CONST_METHOD2(SetMode, void (std::string fileLocation, int mode));
   MOCK_CONST_METHOD3(SetUserAndGroupID, void (std::string fileLocation, int userID, int groupID));
};

#endif