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

# Whether use func archive;
option (USE_func "Use provided func implementation" ON) 
# Then #include "config.h" in main.cpp is allowed;
# and macro USE_func is available in main.cpp;

# Include func archive;
if (USE_func)
    INCLUDE_DIRECTORIES("${PROJECT_SOURCE_DIR}/archive")
    ADD_SUBDIRECTORY(archive)  
    SET(EXTRA_ARCHIVES ${EXTRA_ARCHIVES} func)
endif (USE_func)

# Include all source files;
AUX_SOURCE_DIRECTORY(. SRC_LIST)

# Specify generation target;
ADD_EXECUTABLE(exeproject ${SRC_LIST})
# Include archives;
TARGET_LINK_LIBRARIES(exeproject ${EXTRA_ARCHIVES})

# Reset VS startup project;
# (ALL_BUILD by default, which causes error because there is no .exe file in ALL_BUILD);
SET_PROPERTY(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT exeproject)
