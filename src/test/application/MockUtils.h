#ifndef MOCK_Utils_H
#define MOCK_Utils_H

#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "../../application/IUtils.h"
using namespace std;

class MockUtils : public IUtils {
 public:
   MOCK_CONST_METHOD1(SettingsStringToMap, std::map<std::string, std::string> (std::string settingsString));
};

#endif