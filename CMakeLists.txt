# references
# - https://github.com/SimpleTalkCpp/SimpleGameEngine
cmake_minimum_required(VERSION 3.18)

set(CMAKE_TOOLCHAIN_FILE "./external/vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE STRING "")
set(CMAKE_CXX_STANDARD 17)

include(cmake_utility.cmake)

#set(CMAKE_BUILD_TYPE Debug)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

set(project_name nmsplib)
set(project_namespace nmsp)
set(project_root ${CMAKE_CURRENT_SOURCE_DIR})

project(${project_name})

#option (ENABLE_SANITIZER "enable sanitizer" false)
set     (ENABLE_SANITIZER true)

find_package(fmt CONFIG REQUIRED)

# --- git_submodule ---
#my_add_git_submodule(external/)

# --- core ---
add_subdirectory(src/core/base)
add_subdirectory(src/core/stl)
add_subdirectory(src/core/math)
add_subdirectory(src/core/log)
add_subdirectory(src/core/profiler)
#add_subdirectory(src/core/file_io)
#add_subdirectory(src/core/reflection)
#add_subdirectory(src/core/serializer)
#add_subdirectory(src/core/multi_threading)
#add_subdirectory(src/core/audio)
add_subdirectory(src/core)

add_subdirectory(src/test/base)
add_subdirectory(src/test/core)

set_property (DIRECTORY PROPERTY VS_STARTUP_PROJECT ${project_namespace}_core_test)