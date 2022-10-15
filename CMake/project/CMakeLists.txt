## project/
## |
## +--- main.cpp
## |
## +--- archive/
##      |
##      +--- func.hpp
##      |
##      +--- func.cpp

# Minimum cmake required;
CMAKE_MINIMUM_REQUIRED(VERSION 3.24)

# Project info;
PROJECT(project CXX)

# Include configuration files;
configure_file(
    "${PROJECT_SOURCE_DIR}/config.h.in"
    "${PROJECT_BINARY_DIR}/config.h"
)
# Add configuration file to #include directory;
INCLUDE_DIRECTORIES("${CMAKE_CURRENT_BINARY_DIR}")

OPTION (USE_GoogleTest "Use Google Test" OFF) 
# Whether use func archive;
OPTION (USE_func "Use provided func implementation" ON) 
# Then #include "config.h" in main.cpp is allowed;
# and macro USE_func is available in main.cpp;

# Include func archive;
IF (USE_func)
  MESSAGE(STATUS "Archive func ON. ")
  INCLUDE_DIRECTORIES("${PROJECT_SOURCE_DIR}/archive")
  ADD_SUBDIRECTORY(archive)  
  SET(EXTRA_ARCHIVES ${EXTRA_ARCHIVES} func)
ELSE ()
  MESSAGE(STATUS "Archive func OFF. ")
ENDIF (USE_func)

IF (USE_GoogleTest)
  MESSAGE(STATUS "Google Test ON. ")
  OPTION (USE_GoogleTest_LOCAL "Find Google Test libraries from local directories" ON)

  # GoogleTest requires at least C++14
  SET(CMAKE_CXX_STANDARD 14)

  IF (USE_GoogleTest_LOCAL) # THIS IS NOT SOLVED YET.
  
  ELSE ()
    MESSAGE(STATUS "Downloading Google Test package... ")

    INCLUDE(FetchContent)
    FetchContent_Declare( # Declaring the source of third-party project
      googletest
      GIT_REPOSITORY https://github.com/google/googletest.git
      GIT_TAG release-1.12.1
    )
    # For Windows: Prevent overriding the parent project's compiler/linker settings
    SET(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    # Start downloading...
    FetchContent_MakeAvailable(googletest) 

    enable_testing()
    SET(EXTRA_ARCHIVES ${EXTRA_ARCHIVES} GTest::gtest_main)
  ENDIF (USE_GoogleTest_LOCAL)
ELSE ()
  MESSAGE(STATUS "Google Test OFF. ")
ENDIF (USE_GoogleTest)

# Include all source files;
AUX_SOURCE_DIRECTORY(. SRC_LIST)

# Specify generation target;
ADD_EXECUTABLE(exeproject ${SRC_LIST})
# Include archives;
TARGET_LINK_LIBRARIES(exeproject ${EXTRA_ARCHIVES})

# Reset VS startup project;
# (ALL_BUILD by default, which causes error because there is no .exe file in ALL_BUILD);
SET_PROPERTY(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT exeproject)
