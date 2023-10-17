cmake_minimum_required(VERSION 3.0)
project(TriedToMerge)

set(CMAKE_CXX_STANDARD 11)

# Add all the .cpp files in the source directory
file(GLOB SOURCES "./*.cpp")

# Add all the .h files in the include directory
file(GLOB HEADERS "./*.h")

# Include the directories where the header files are located
include_directories(include)

# Create an executable target from the source files
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})