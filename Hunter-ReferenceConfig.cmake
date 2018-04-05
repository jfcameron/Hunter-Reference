# © 2017 Joseph Cameron - All Rights Reserved
# Project: Hello Travis CI
# Created on 2017-12-7.

# Sets the lib and include paths. Keep in mind the project must have been built.
set(Hunter-Reference_INCLUDE_DIR ${CMAKE_CURRENT_LIST_DIR}/include
    CACHE PATH "Hunter-Reference include directory" FORCE)

set(Hunter-Reference_LIBRARIES ${CMAKE_CURRENT_LIST_DIR}/build/libHunter-Reference.a;glfw
    CACHE PATH "Hunter-Reference output libraries" FORCE)
