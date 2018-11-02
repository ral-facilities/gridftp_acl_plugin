file(GLOB SRCS *.cpp **/*.cpp)

add_executable(testPlugin ${SRCS} ${framework_src} ${application_src})

target_link_libraries(testPlugin
    gtest
    gmock
    spdlog
)

install(TARGETS testPlugin DESTINATION bin)

add_custom_target(
  test
  COMMAND testPlugin "--gtest_color=yes"
)