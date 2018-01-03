##############################
# General Settings
##############################

cmake_minimum_required (VERSION 3.0)
project (GECKFrontend)

option(PROJECT_STATIC_RUNTIME "Build with static runtime libs (/MT)" ON)

set (Boost_USE_STATIC_LIBS ON)
set (Boost_USE_MULTITHREADED ON)
set (Boost_USE_STATIC_RUNTIME PROJECT_STATIC_RUNTIME)

IF (MSVC)
    set (Boost_COMPILER "-vc140")
	set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")
	set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd")
ENDIF ()


add_definitions( -DBOOST_ALL_NO_LIB )

find_package(Boost REQUIRED COMPONENTS regex)

include_directories ("${CMAKE_CURRENT_SOURCE_DIR}/CBash/include/cbash"
                     ${Boost_INCLUDE_DIRS})


add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/CBash")
add_executable (GECKFrontend main.cpp)
add_dependencies(GECKFrontend CBash)
target_link_libraries (GECKFrontend CBash ${Boost_LIBRARIES})
