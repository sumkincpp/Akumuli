project(Akumuli)
cmake_minimum_required(VERSION 2.8)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

#set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DDEBUG -Wall -Werror -fsanitize=address -static-libasan")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DDEBUG -Wall -Werror")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Wall -Werror -ffast-math -funroll-loops -march=native")

find_package(Boost 1.53.0
    COMPONENTS
    unit_test_framework
    program_options
    system
    thread
    filesystem
    coroutine
    context
    regex
    date_time
    REQUIRED
)

find_package(Log4Cxx REQUIRED)
find_package(Sqlite3 REQUIRED)
find_package(APR REQUIRED)

include_directories(${Boost_INCLUDE_DIRS})
include_directories("${APR_INCLUDE_DIR}")
include_directories("${APRUTIL_INCLUDE_DIR}")
include_directories("${SQLITE3_INCLUDE_DIR}")

#if(CMAKE_COMPILER_IS_GNUCXX)
add_definitions(-std=c++1y -fvisibility=hidden)
#endif()

include_directories(./include)

add_subdirectory(libakumuli)
add_subdirectory(akumulid)
add_subdirectory(perftests)
add_subdirectory(functests)

enable_testing()
add_subdirectory(unittests)

