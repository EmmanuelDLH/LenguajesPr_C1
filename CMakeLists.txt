cmake_minimum_required(VERSION 3.14)
project(Proyecto1Lenguajes C)

set(CMAKE_C_STANDARD 99)

ADD_LIBRARY(regex STATIC IMPORTED)
SET_TARGET_PROPERTIES(regex PROPERTIES IMPORTED_LOCATION C:/msys64/mingw64/lib/libsystre.dll.a)

add_executable(Proyecto1Lenguajes main.c)
target_link_libraries(Proyecto1Lenguajes regex)