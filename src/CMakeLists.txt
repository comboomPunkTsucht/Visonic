cmake_minimum_required(VERSION 3.10.0)
project(Visonic VERSION 0.1.0 LANGUAGES C)

add_executable(visonic main.c)
target_compile_features(visonic PRIVATE c_std_99)

include(CTest)
enable_testing()

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
