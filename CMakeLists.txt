CMAKE_MINIMUM_REQUIRED(VERSION 3.16)

project(FileContainString)
set(CMAKE_CXX_STANDARD 17)
find_package(Boost)
include_directories(${Boost_INCLUDE_DIRS})
add_executable(FileContainString FileContainString.cpp)
target_link_libraries(FileContainString ${Boost_LIBRARIES})