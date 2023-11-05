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
set(project_namespace_marco NMSP)

project(${project_name})

my_set_opt(${project_namespace_marco}_ENABLE_PROFILER           0)
my_set_opt(${project_namespace_marco}_ENABLE_INTERNAL_PROFILER  0)
my_set_opt(${project_namespace_marco}_ENABLE_SANITIZER          0)

my_set_opt(${project_namespace_marco}_JOB_SYSTEM_DEVELOPMENT    1)

my_only_one_opt_could_on_3( ${project_namespace_marco}_ENABLE_PROFILER
                            ${project_namespace_marco}_ENABLE_INTERNAL_PROFILER
                            ${project_namespace_marco}_ENABLE_SANITIZER
                        )

find_package(fmt                        CONFIG REQUIRED)
find_package(benchmark                  CONFIG REQUIRED)
find_package(Threads                           REQUIRED)
find_package(Tracy                      CONFIG REQUIRED)
find_package(EABase                     CONFIG REQUIRED)
find_package(EASTL                      CONFIG REQUIRED)
find_package(unofficial-concurrentqueue CONFIG REQUIRED)
find_package(spdlog                     CONFIG REQUIRED)
find_package(glm                        CONFIG REQUIRED)
find_package(PNG                               REQUIRED)
find_package(Stb                               REQUIRED)
find_package(nlohmann_json              CONFIG REQUIRED)

# --- git_submodule ---
#my_add_git_submodule(external/)

# --- core ---
add_subdirectory(src/core/base)
add_subdirectory(src/core/stl)
add_subdirectory(src/core/os)
add_subdirectory(src/core/profiler)
add_subdirectory(src/core/log)
add_subdirectory(src/core/math)
add_subdirectory(src/core/file_io)
add_subdirectory(src/core/job_system)
#add_subdirectory(src/core/reflection)
#add_subdirectory(src/core/net)
#add_subdirectory(src/core/audio)
add_subdirectory(src/core)

add_subdirectory(src/test/base)
add_subdirectory(src/test/core)
#add_subdirectory(src/test/test_proj)

message("--- end for add_subdirectory ---")

set_property (DIRECTORY PROPERTY VS_STARTUP_PROJECT ${project_namespace}_core_test)