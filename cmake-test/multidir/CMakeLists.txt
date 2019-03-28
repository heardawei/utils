cmake_minimum_required(VERSION 3.13)

project(helloworld)

# Add the source in project root directory
aux_source_directory(${PROJECT_SOURCE_DIR}/ LOCAL_ROOT_SRCS)

# Add header file include directories
include_directories(${PROJECT_SOURCE_DIR}/ ${PROJECT_SOURCE_DIR}/hello/ ${PROJECT_SOURCE_DIR}/world/)

# Add block directories
add_subdirectory(hello)
add_subdirectory(world)

# Target
add_executable(helloworld ${LOCAL_ROOT_SRCS})
target_link_libraries(helloworld hello world)
