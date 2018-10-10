file(GLOB SRCS *.cpp)

add_executable(testPlugin ${SRCS})

target_link_libraries(testPlugin
    gtest
    gmock
)

add_test(NAME testPlugin COMMAND testPlugin)

install(TARGETS testPlugin DESTINATION bin)

# add_custom_target(
#   NAME test
#   COMMAND testPlugin
# )