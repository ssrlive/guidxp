cmake_minimum_required(VERSION 3.5.1)
project(guidxp)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake")

set(CMAKE_DEBUG_POSTFIX "-dgb")

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release")
endif()

add_library(guidxp STATIC ${CMAKE_CURRENT_SOURCE_DIR}/guidxp.c)
set_property(TARGET guidxp PROPERTY POSITION_INDEPENDENT_CODE ON)

if(WIN32)
elseif(APPLE)
    find_library(CFLIB CoreFoundation)
    target_link_libraries(guidxp ${CFLIB})
elseif(ANDROID)
else()
    #[[
    find_package(Libuuid REQUIRED)
    if (NOT LIBUUID_FOUND)
        message(FATAL_ERROR "You might need to run 'sudo apt-get install uuid-dev' or similar")
    endif()
    target_include_directories(guidxp PRIVATE ${LIBUUID_INCLUDE_DIR})
    target_link_libraries(guidxp ${LIBUUID_LIBRARY})
    ]]
endif()

if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    set(WARNINGS "-Werror" "-Wall")
elseif(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    set(WARNINGS "-Werror" "-Wall")
elseif(MSVC)
    set(WARNINGS "/WX" "/W4")
endif()
target_compile_options(guidxp PRIVATE ${WARNINGS})

# Properties
# for a version number add
# VERSION ${CROSSGUID_VERSION_STRING} SOVERSION ${CROSSGUID_VERSION_STRING}
set_target_properties(guidxp PROPERTIES DEBUG_POSTFIX ${CMAKE_DEBUG_POSTFIX})

add_executable(testguid ${CMAKE_CURRENT_SOURCE_DIR}/test.c)
target_link_libraries(testguid guidxp)
