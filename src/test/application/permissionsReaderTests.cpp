#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "MockFileInfoProvider.h"
#include "../../application/PermissionsReader.h"
#include <string>

using ::testing::Return;
using ::testing::_;

class PermissionsReaderTests : public ::testing::Test
{
    protected:
      std::string fileName = "file123.txt";
      MockFileInfoProvider mockFileInfoProvider;
      PermissionsReader permissionsReader;
      struct stat buf;

    virtual void setup() {
        buf.st_mode = S_IFREG;  // file octal value
        buf.st_gid = 1000;
        buf.st_uid = 1000;
    }
    virtual void TearDown() {}
};

TEST_F(PermissionsReaderTests, CheckOutputPermissionsStringForFile)
{
    PermissionsReaderTests::setup();
    EXPECT_CALL(mockFileInfoProvider, GetPermissions("file123.txt")).WillRepeatedly(Return(buf));
    EXPECT_CALL(mockFileInfoProvider, Exists("file123.txt")).WillRepeatedly(Return(1));
    ASSERT_EQ(permissionsReader.GetPermissions(fileName, &mockFileInfoProvider), "mode=32768;userID=1000;groupID=1000");
}

TEST_F(PermissionsReaderTests, CheckOutputPermissionsStringForDirectory)
{
    PermissionsReaderTests::setup();
    buf.st_mode = S_IFDIR;  // directory, 16384 equiv 40000 octal, must update mock each time st_mode is changed
    EXPECT_CALL(mockFileInfoProvider, GetPermissions("file123.txt")).WillRepeatedly(Return(buf));
    EXPECT_CALL(mockFileInfoProvider, Exists("file123.txt")).WillRepeatedly(Return(1));
    ASSERT_EQ(permissionsReader.GetPermissions(fileName, &mockFileInfoProvider), "mode=16384;userID=1000;groupID=1000");
}

TEST_F(PermissionsReaderTests, CheckOutputPermissionsStringForLink)
{
    PermissionsReaderTests::setup();
    buf.st_mode = S_IFLNK;
    EXPECT_CALL(mockFileInfoProvider, GetPermissions("file123.txt")).WillRepeatedly(Return(buf));
    EXPECT_CALL(mockFileInfoProvider, Exists("file123.txt")).WillRepeatedly(Return(1));
    ASSERT_EQ(permissionsReader.GetPermissions(fileName, &mockFileInfoProvider), "mode=40960;userID=1000;groupID=1000");
}

TEST_F(PermissionsReaderTests, ThrowsRuntimeErrorWhenFileDoesntExist)
{
    PermissionsReaderTests::setup();
    EXPECT_CALL(mockFileInfoProvider, Exists("file123.txt")).WillRepeatedly(Return(0));
    try {
        permissionsReader.GetPermissions(fileName, &mockFileInfoProvider);
        FAIL() << "Expected: Permissions not found error";
    }
    catch(std::runtime_error const & e) {
        ASSERT_EQ(e.what(), std::string("Permissions not found"));
    }
}
