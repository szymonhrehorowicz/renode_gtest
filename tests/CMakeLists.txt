# tests/CMakeLists.txt

# Use vcpkg GTest
find_package(GTest CONFIG REQUIRED)

add_executable(integration_tests
    sample_test.cpp
    renode/renode.cpp
    renode/uart.cpp
)

target_link_libraries(integration_tests
    PRIVATE
        GTest::gtest
        GTest::gtest_main
        Ws2_32
)

set_target_properties(integration_tests PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
)

# Enable CTest
enable_testing()

# Automatically register all GTest tests with CTest
include(GoogleTest)
gtest_discover_tests(integration_tests)
