cmake_minimum_required(VERSION 3.10)

# 设置项目名称
project(app)

# 设置C标准
set(CMAKE_C_STANDARD 99)

# 查找源文件
set(SOURCES
   ${CMAKE_CURRENT_SOURCE_DIR}/main.c
   ${CMAKE_CURRENT_SOURCE_DIR}/atc.c
)

# 查找头文件路径
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
)

# 创建可执行文件
add_executable(${PROJECT_NAME} ${SOURCES})

# 可选：设置编译器标志
if(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -O2")
endif()
