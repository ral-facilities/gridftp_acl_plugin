#ifndef MOCK_FileInfoProvider_H
#define MOCK_FileInfoProvider_H

#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "../../application/IFileInfoProvider.h"

class MockFileInfoProvider : public IFileInfoProvider {
 public:
   MOCK_CONST_METHOD1(GetPermissions, struct stat(std::string fileLocation));
   MOCK_CONST_METHOD1(Exists, bool (std::string fileLocation));
   MOCK_CONST_METHOD2(SetPermissions, void (std::string fileLocation, std::string permissions));
};

#endif