#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "MockFileInfoProvider.h"
#include "MockUtils.h"
#include "../../application/PermissionsSetter.h"
#include <string>

using ::testing::Return;
using ::testing::_;

class PermissionsSetterTests : public ::testing::Test
{
    protected:
      MockFileInfoProvider mockFileInfoProvider;
      MockUtils mockUtils;
      std::string fileName = "file123.txt";
      PermissionsSetter permissionsSetter;
      std::string permissionsString = "mode=100777;groupID=1234;userID=1234";
      std::vector<std::string> tokens;
      std::map<std::string, std::string> permissionsMap;

      virtual void setup() {
          tokens = {"mode", "10077", "userID", "1000", "groupID", "1000"};
          permissionsMap = {{"mode", "100777"}, {"userID", "1000"}, {"groupID", "1000"}};
      }
    
      virtual void TearDown() {}
};

ACTION(ThrowException)
{
    throw std::runtime_error("Test exception thrown");
}

TEST_F(PermissionsSetterTests, ThrowRuntimeErrorIfFileDoesntExist)
{
    setup();
    EXPECT_CALL(mockFileInfoProvider, Exists(_)).WillRepeatedly(Return(false));
    EXPECT_CALL(mockUtils, SettingsStringToMap(permissionsString)).WillRepeatedly(Return(permissionsMap));
    
    try{
        permissionsSetter.SetPermissions(fileName, permissionsString, &mockUtils, &mockFileInfoProvider);
        FAIL() << "Expected: File not found error";
    }
    catch(std::runtime_error const & e)
    {
        ASSERT_EQ(e.what(), std::string("File not found"));
    }
}

TEST_F(PermissionsSetterTests, ThrowRuntimeErrorIfModeNotSet)
{
    setup();
    EXPECT_CALL(mockFileInfoProvider, Exists(_)).WillRepeatedly(Return(true));
    EXPECT_CALL(mockUtils, SettingsStringToMap(permissionsString)).WillRepeatedly(Return(permissionsMap));
    EXPECT_CALL(mockFileInfoProvider, SetMode(_, 100777)).WillRepeatedly(Return(false));

    try{
        permissionsSetter.SetPermissions(fileName, permissionsString, &mockUtils, &mockFileInfoProvider);
        FAIL() << "Expected: Failed to set file mode";
    }
    catch(std::runtime_error const & e)
    {
        ASSERT_EQ(e.what(), std::string("Failed to set file mode"));
    }   
}