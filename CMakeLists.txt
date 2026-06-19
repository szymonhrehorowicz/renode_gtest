cmake_minimum_required(VERSION 3.22)

project(rtos_project LANGUAGES C CXX)

# ---------------------------------------------------------
# Options
# ---------------------------------------------------------
option(BUILD_SIM "Build firmware with Renode simulation flags" OFF)

# ---------------------------------------------------------
# Add STM32 firmware project (only when cross-compiling)
# ---------------------------------------------------------
if(CMAKE_CROSSCOMPILING OR BUILD_SIM)
    add_subdirectory(target)
endif()

if(BUILD_SIM)
    target_compile_definitions(target PRIVATE RENODE_SIMULATION)
endif()

# ---------------------------------------------------------
# Add host-side tests (always)
# ---------------------------------------------------------
if(NOT BUILD_SIM)
add_subdirectory(tests)
endif()
# ---------------------------------------------------------
# Custom targets
# ---------------------------------------------------------

add_custom_target(build
    COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR}
    COMMENT "Building firmware"
)

add_custom_target(rebuild
    COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR} --target clean
    COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR}
    COMMENT "Rebuilding firmware"
)

add_custom_target(build-sim
    COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR} --target target
    COMMENT "Building firmware for Renode simulation"
)

add_custom_target(run-sim
    COMMAND renode ${CMAKE_SOURCE_DIR}/test.resc
    COMMENT "Launching Renode simulation"
)

add_custom_target(clean-all
    COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR} --target clean
    COMMENT "Cleaning build directory"
)

add_custom_target(integration-tests
    COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR} --target integration_tests
    COMMENT "Building GoogleTest integration tests"
)
