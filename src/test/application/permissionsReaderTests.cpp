#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "MockFileInfoProvider.h"
#include "../../application/permissionsReader.h"
#include <string>

using ::testing::Return;
using ::testing::_;

class PermissionsReaderTests : public ::testing::Test
{
    std::string fileName = "file123.txt";
    // MockFileInfoProvider mockFileInfoProvider;

    virtual void setup() {}

    virtual void TearDown() {}
};

TEST_F(PermissionsReaderTests, CheckAssertion)
{
    MockFileInfoProvider mockFileInfoProvider;

    std::string fileName = "file123.txt";

    // add attribute st_mode
    struct stat buf;
    buf.st_mode = S_IFREG;  // file octal value
    buf.st_gid = 1000;
    buf.st_uid = 1000;

    // Update mock object with attribute
    EXPECT_CALL(mockFileInfoProvider, GetPermissions("file123.txt")).WillRepeatedly(Return(buf));
    EXPECT_CALL(mockFileInfoProvider, Exists("file123.txt")).WillRepeatedly(Return(1));
    PermissionsReader permissionsReader;
    ASSERT_EQ(permissionsReader.GetPermissions(fileName, &mockFileInfoProvider), "mode: 32768 groupID: 1000 userID: 1000");

    buf.st_mode = S_IFDIR;  // directory, 16384 equiv 40000 octal, must update mock each time st_mode is changed 
    EXPECT_CALL(mockFileInfoProvider, GetPermissions("file123.txt")).WillRepeatedly(Return(buf));
    ASSERT_EQ(permissionsReader.GetPermissions(fileName, &mockFileInfoProvider), "mode: 16384 groupID: 1000 userID: 1000");

    buf.st_mode = S_IFLNK; // link
    EXPECT_CALL(mockFileInfoProvider, GetPermissions("file123.txt")).WillRepeatedly(Return(buf));
    ASSERT_EQ(permissionsReader.GetPermissions(fileName, &mockFileInfoProvider), "mode: 40960 groupID: 1000 userID: 1000");

    EXPECT_CALL(mockFileInfoProvider, Exists("file123.txt")).WillRepeatedly(Return(0));
    try {
        permissionsReader.GetPermissions(fileName, &mockFileInfoProvider);
        FAIL() << "Expected: Permissions not found error";
    }
    catch(std::runtime_error const & e) {
        ASSERT_EQ(e.what(), std::string("Permissions not found"));
    }
}
