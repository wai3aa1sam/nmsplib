set(sub_project_name ${project_namespace}_core)
message("==== ${sub_project_name} ====")
project(${sub_project_name})

my_add_library(${sub_project_name} ${CMAKE_CURRENT_SOURCE_DIR})
set_target_properties (${sub_project_name} PROPERTIES FOLDER ${project_namespace}/core)
target_link_libraries(${sub_project_name} PUBLIC fmt::fmt)
#my_link_sub_module(${sub_project_name} testlib core testlib_core ${project_root})