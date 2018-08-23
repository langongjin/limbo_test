cmake_minimum_required(VERSION 3.8)
project(LimboTest)

find_package(Eigen3 REQUIRED)

find_package(Boost REQUIRED COMPONENTS
        system
        filesystem
        thread
        regex
        unit_test_framework)

find_package(NLOpt REQUIRED)


if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
else(Boost_FOUND)
    find_library(Boost boost PATHS /opt/local/lib)
    include_directories(${Boost_LIBRARY_PATH})
endif()


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

include_directories(limbo/
                    external/)

set(SOURCE_FILES main.cpp)

include_directories(${EIGEN3_INCLUDE_DIR})
include_directories(${NLOPT_INCLUDE_DIR})

add_executable(LimboTest ${SOURCE_FILES})
target_compile_definitions(LimboTest PUBLIC USE_NLOPT=1)
target_link_libraries(LimboTest ${TBB_LIBRARIES} ${Boost_LIBRARIES} nlopt)
