file(GLOB SRCS *.cpp)

add_executable(testPlugin ${SRCS})

target_link_libraries(testPlugin
    gtest
    gmock
)

install(TARGETS testPlugin DESTINATION bin)

add_custom_target(
  test
  COMMAND testPlugin "--gtest_color=yes"
)