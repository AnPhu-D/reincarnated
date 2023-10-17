cmake_minimum_required(VERSION 3.2)
project(Reincarnated)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/bin")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/lib")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/lib")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1y -g -fprofile-arcs -ftest-coverage")

include_directories(${CMAKE_SOURCE_DIR}/include)
link_directories(${LIBRARY_OUTPUT_PATH})

include_directories(
  ${CMAKE_SOURCE_DIR}/test/lib/googletest/include/
  ${CMAKE_SOURCE_DIR}/test/lib/googlemock/include/
)

add_subdirectory(Frame_Render_Prototype_3)
add_subdirectory(test)

