#-------------------------------------------------
# Project converted from qmake file using q2c
# https://github.com/benapetr/q2c at Sun Oct 23 22:58:53 2016
#-------------------------------------------------
cmake_minimum_required (VERSION 2.8.4)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

set (CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/modules/")
project (icosphere)
# Download and unpack googletest at configure time
configure_file(CMakeLists.txt.in googletest-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
        RESULT_VARIABLE result
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download )
if(result)
    message(FATAL_ERROR "CMake step for googletest failed: ${result}")
endif()
execute_process(COMMAND ${CMAKE_COMMAND} --build .
        RESULT_VARIABLE result
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download )
if(result)
    message(FATAL_ERROR "Build step for googletest failed: ${result}")
endif()

# Prevent overriding the parent project's compiler/linker settings on Windows
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Add googletest directly to our build. This defines the gtest and gtest_main targets.
add_subdirectory(${CMAKE_BINARY_DIR}/googletest-src
        ${CMAKE_BINARY_DIR}/googletest-build
        EXCLUDE_FROM_ALL)

# The gtest/gtest_main targets carry header search path dependencies automatically when using CMake 2.8.11 or later. Otherwise we have to add them here ourselves.
if (CMAKE_VERSION VERSION_LESS 2.8.11)
    include_directories("${gtest_SOURCE_DIR}/include")
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")
#set(CMAKE_AUTOMOC ON)
set(SOURCE_FILES
        icosphere/geometry.h
        icosphere/icosphere.h
        icosphere/icosphere.cpp
        tests/icospheretest.cpp
        tests/main.cpp
        containers/robinhood.h
        tests/minimalistprinter.h
        tests/MinimalistPrinter.cpp
)

find_package (GeographicLib 1.34 REQUIRED)


if (NOT MSVC)
    set (CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)
endif()

#if (CMAKE_VERSION VERSION_LESS 2.8.11)
    include_directories (${GeographicLib_INCLUDE_DIRS})
    add_definitions (${GeographicLib_DEFINITIONS})
#endif()

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/modules/")
add_library (icosphere SHARED ${SOURCE_FILES})

target_link_libraries (${PROJECT_NAME} ${GeographicLib_LIBRARIES} gtest_main)

if (MSVC)
    get_target_property (_LIBTYPE ${GeographicLib_LIBRARIES} TYPE)
    if (_LIBTYPE STREQUAL "SHARED_LIBRARY")
    # On Windows systems copy the shared library to build directory
        COMMAND (${CMAKE_COMMAND} -E
        copy $<TARGET_FILE:${GeographicLib_LIBRARIES}> ${CMAKE_CFG_INTDIR}
        COMMENT "Copying shared library for GeographicLib")
    endif()
endif()


# Make test executable and link against gtest or gtest_main as needed.
add_executable (tests tests/main.cpp)
target_link_libraries (tests gtest_main icosphere)
add_test(NAME tests COMMAND tests)

