cmake_minimum_required(VERSION 3.10.0)
project(visonic VERSION 0.1.0 LANGUAGES C)

add_executable(visonic main.c)

include(CTest)
enable_testing()

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
