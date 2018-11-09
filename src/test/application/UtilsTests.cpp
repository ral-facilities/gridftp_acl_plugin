#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "MockFileInfoProvider.h"
#include "../../application/Utils.h"
#include <string>

using ::testing::Return;
using ::testing::_;

class UtilsTests : public ::testing::Test
{
    protected:
      Utils utils;
      std::string settingsString = "mode=100777;userID=1234;groupID=12345";

      virtual void setup() {
      }
    
      virtual void TearDown() {}
};

TEST_F(UtilsTests, CheckSettingsStringToMapReturnsCorrectNumberOfMapEntries)
{
    std::map<std::string, std::string> permissionsMap = utils.SettingsStringToMap(settingsString);
    ASSERT_EQ(stoi(permissionsMap.find("mode")->second), 100777);
    ASSERT_EQ(stoi(permissionsMap.find("userID")->second), 1234);
    ASSERT_EQ(stoi(permissionsMap.find("groupID")->second), 12345);
}
