cmake_minimum_required(VERSION 3.22)
project(rtos_project NONE)

# ---------------------------------------------------------
# Options
# ---------------------------------------------------------
option(BUILD_SIM "Build firmware with Renode simulation flags" OFF)

# ---------------------------------------------------------
# Add STM32 firmware project
# ---------------------------------------------------------
add_subdirectory(target)

if(BUILD_SIM)
    target_compile_definitions(target PRIVATE RENODE_SIMULATION)
endif()

# ---------------------------------------------------------
# Custom targets (Makefile equivalents)
# ---------------------------------------------------------

# build
add_custom_target(build
    COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR}
    COMMENT "Building firmware"
)

# rebuild
add_custom_target(rebuild
    COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR} --target clean
    COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR}
    COMMENT "Rebuilding firmware"
)

# build-sim (no reconfigure!)
add_custom_target(build-sim
    COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR} --target target
    COMMENT "Building firmware for Renode simulation (BUILD_SIM must be set during configuration)"
)


# run-sim
add_custom_target(run-sim
    COMMAND renode ${CMAKE_SOURCE_DIR}/test.resc
    COMMENT "Launching Renode simulation"
)

# clean
add_custom_target(clean-all
    COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR} --target clean
    COMMENT "Cleaning build directory"
)

# test
add_custom_target(test
    COMMAND echo "Running Renode tests..."
    COMMAND renode-test ${CMAKE_SOURCE_DIR}/tests/test-button.robot
    COMMENT "Executing Renode Robot tests"
)
