## archive/
## |
## +--- main.cpp
## |
## +--- func.cpp

# Include source files;
AUX_SOURCE_DIRECTORY(. ACV_SRC_LIST)

# Generate static libs;
ADD_LIBRARY(func ${ACV_SRC_LIST})
