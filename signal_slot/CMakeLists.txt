cmake_minimum_required(VERSION 3.10)

# 设置项目名称
project(signal_slot_project)

# 设置C标准
set(CMAKE_C_STANDARD 99)

# 创建库
add_library(signal_slot_lib signal_slot.c)

# 添加头文件目录
target_include_directories(signal_slot_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# 创建可执行文件
add_executable(signal_slot_app example.c)

# 链接库到可执行文件
target_link_libraries(signal_slot_app signal_slot_lib)

# 设置输出目录
set_target_properties(signal_slot_app PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

# 可选：如果需要生成静态库或动态库
# add_library(signal_slot_static STATIC signal_slot.c)
# add_library(signal_slot_shared SHARED signal_slot.c)
