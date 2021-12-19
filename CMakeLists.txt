cmake_minimum_required(VERSION 3.9)
project(NGP C)

set(EXEC delaunay)
set(CMAKE_BUILD_TYPE Debug)

file(GLOB_RECURSE sources "${CMAKE_CURRENT_SOURCE_DIR}/src/*.c")
add_executable(${EXEC}
               "${CMAKE_CURRENT_SOURCE_DIR}/src/main.c"
               "${CMAKE_CURRENT_SOURCE_DIR}/src/inputs.c"
               "${CMAKE_CURRENT_SOURCE_DIR}/src/utils.c"
               "${CMAKE_CURRENT_SOURCE_DIR}/src/delaunay.c"
               "${CMAKE_CURRENT_SOURCE_DIR}/src/visualize.c"
               "${CMAKE_CURRENT_SOURCE_DIR}/src/mesh.c"
               "${CMAKE_CURRENT_SOURCE_DIR}/src/emst.c"
               )

target_include_directories(${EXEC} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/src")
set_target_properties(${EXEC} PROPERTIES
                      C_STANDARD 99
                      RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/bin")

add_subdirectory(deps/BOV)
target_link_libraries(${EXEC} bov)

# set ${EXEC} as the startup project in visual studio
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${EXEC})