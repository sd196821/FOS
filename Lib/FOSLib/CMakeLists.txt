project(FOSLib-Build_and_test)
cmake_minimum_required(VERSION 2.8)
aux_source_directory(. SRC_LIST)
add_subdirectory(MMU)
add_subdirectory(Tasker)
add_subdirectory(HardwareDrivers)
add_executable(${PROJECT_NAME} ${SRC_LIST})


