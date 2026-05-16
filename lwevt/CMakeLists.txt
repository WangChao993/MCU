cmake_minimum_required(VERSION 3.10)
project(lwevt_project)

# 设置C标准
set(CMAKE_C_STANDARD 99)

# 定义lwevt库的源文件
set(LWEVT_SOURCES
    lwevt/lwevt.c
)

# 定义lwevt库的头文件目录
set(LWEVT_INCLUDE_DIRS
    ${CMAKE_CURRENT_SOURCE_DIR}/lwevt/inc
    ${CMAKE_CURRENT_SOURCE_DIR}/lwevt/port
)

# 创建lwevt静态库
add_library(lwevt STATIC ${LWEVT_SOURCES})
target_include_directories(lwevt PUBLIC ${LWEVT_INCLUDE_DIRS})

# 添加dev目录下的main.c可执行文件
add_executable(main dev/main.c)
target_link_libraries(main lwevt)
target_include_directories(main PRIVATE ${LWEVT_INCLUDE_DIRS})

# 如果您还有其他示例程序要构建，也可以添加它们
# add_executable(example_basic_consumer examples/example_basic_consumer.c)
# target_link_libraries(example_basic_consumer lwevt)
# target_include_directories(example_basic_consumer PRIVATE ${LWEVT_INCLUDE_DIRS})

# add_executable(example_basic_producer examples/example_basic_producer.c)
# target_link_libraries(example_basic_producer lwevt)
# target_include_directories(example_basic_producer PRIVATE ${LWEVT_INCLUDE_DIRS})

# add_executable(example_basic_producer_local examples/example_basic_producer_local.c)
# target_link_libraries(example_basic_producer_local lwevt)
# target_include_directories(example_basic_producer_local PRIVATE ${LWEVT_INCLUDE_DIRS})
