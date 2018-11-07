#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "MockFileInfoProvider.h"
#include "../../application/PermissionsSetter.h"
#include <string>

using ::testing::Return;
using ::testing::_;

class PermissionsSetterTests : public ::testing::Test
{
    protected:
      MockFileInfoProvider mockFileInfoProvider;
      std::string fileName = "file123.txt";
      PermissionsSetter permissionsSetter;
      std::string permissionsString = "mode=100777;groupID=1234;userID=1234";

      virtual void setup() {}
    
      virtual void TearDown() {}
};

TEST_F(PermissionsSetterTests, CheckAssertion)
{
    EXPECT_CALL(mockFileInfoProvider, Exists(_)).WillRepeatedly(Return(false));
    
    try{
        permissionsSetter.SetPermissions(fileName, permissionsString, &mockFileInfoProvider);
        FAIL() << "Expected: File not found error";
    }
    catch(std::runtime_error const & e)
    {
        ASSERT_EQ(e.what(), std::string("File not found"));
    }
}
