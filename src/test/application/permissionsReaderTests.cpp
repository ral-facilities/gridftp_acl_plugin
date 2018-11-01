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
    MockFileInfoProvider mockFileInfoProvider;

    virtual void setup() {}

    virtual void TearDown() {}

//   unsigned long BuildMode(int owner, int group, int other) {
//     return other + (8*group) + (64*owner);    

    void RunPermissionsReaderTests()
    {
        //EXPECT_CALL(mockFileInfoProvider, GetPermissions(fileName)).WillRepeatedly(::testing::Return(true))
    }
};

TEST_F(PermissionsReaderTests, CheckAssertion)
{
    // RunPermissionsReaderTests();
    ASSERT_EQ(1, 1);
    MockFileInfoProvider mockFileInfoProvider;

    // add attribute st_mode
    std::string fileName = "file123.txt";
    struct stat buf;
    //              type, rwx
    //32768 equiv to 100000 = S_IFREG
    buf.st_mode = S_IFREG;
    buf.st_gid = 1000;
    buf.st_uid = 1000;
    EXPECT_CALL(mockFileInfoProvider, GetPermissions("file123.txt")).WillRepeatedly(Return(buf));

    //#define S_IFREG _IFREG;
    PermissionsReader permissionsReader;
    //std::string test = permissionsReader.GetPermissions(fileName, &mockFileInfoProvider);
    ASSERT_EQ(permissionsReader.GetPermissions(fileName, &mockFileInfoProvider), "mode: 32768 groupID: 1000 userID: 1000");

    buf.st_mode = S_IFDIR;  //dir, 16384 equiv 40000
    EXPECT_CALL(mockFileInfoProvider, GetPermissions("file123.txt")).WillRepeatedly(Return(buf));
    try
    {
        permissionsReader.GetPermissions(fileName, &mockFileInfoProvider);
        FAIL() << "Expected File not found error";

    }
    catch (std::runtime_error& e)
    {
        ASSERT_EQ(e.what(), std::string("File not found"));
    }

    buf.st_mode = S_IFLNK;
    EXPECT_CALL(mockFileInfoProvider, GetPermissions("file123.txt")).WillRepeatedly(Return(buf));
    try
    {
        permissionsReader.GetPermissions(fileName, &mockFileInfoProvider);
        FAIL() << "Expected File not found error";

    }
    catch (std::runtime_error& e)
    {
        ASSERT_EQ(e.what(), std::string("File not found"));
    }



}
