## archive/
## |
## +--- main.cpp
## |
## +--- func.cpp

# Include source files;
AUX_SOURCE_DIRECTORY(. LIB_SRC_LIST)

# Generate static libs;
ADD_LIBRARY(func ${LIB_SRC_LIST})
