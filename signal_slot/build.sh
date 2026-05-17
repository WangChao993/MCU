#!/bin/bash

# 项目构建脚本，支持多种操作
# 使用方法: ./build.sh [clean|build|run|all]

BUILD_DIR="build"
EXECUTABLE_NAME="signal_slot_app"

# 显示帮助信息
show_help() {
    echo "Usage: $0 [clean|build|run|all]"
    echo ""
    echo "Commands:"
    echo "  clean    - Remove build directory"
    echo "  build    - Build the project"
    echo "  run      - Run the built executable"
    echo "  all      - Clean, build, and run the project"
    echo "  help     - Show this help message"
    echo ""
}

# 清除构建目录
clean_build() {
    if [ -d "$BUILD_DIR" ]; then
        echo "Removing build directory..."
        rm -rf "$BUILD_DIR"
        echo "Build directory removed."
    else
        echo "Build directory does not exist."
    fi
}

# 构建项目
build_project() {
    echo "Building project..."
    
    # 检查是否已存在build目录，如果没有则创建
    if [ ! -d "$BUILD_DIR" ]; then
        mkdir -p "$BUILD_DIR"
    fi

    # 进入build目录
    cd "$BUILD_DIR"

    # 运行cmake配置
    cmake .. || { echo "CMake configuration failed!"; exit 1; }

    # 编译项目
    make || { echo "Build failed!"; exit 1; }

    echo "Project built successfully!"
    
    # 返回原目录
    cd ..
}

# 运行可执行文件
run_executable() {
    if [ -f "$BUILD_DIR/$EXECUTABLE_NAME" ]; then
        echo "Running $EXECUTABLE_NAME..."
        ./"$BUILD_DIR/$EXECUTABLE_NAME"
    else
        echo "Executable $EXECUTABLE_NAME not found. Please build first."
        exit 1
    fi
}

# 主逻辑处理命令行参数
case "${1:-help}" in
    clean)
        clean_build
        ;;
    build)
        build_project
        ;;
    run)
        run_executable
        ;;
    all)
        clean_build
        build_project
        run_executable
        ;;
    help|--help|-h)
        show_help
        ;;
    *)
        echo "Unknown command: $1"
        show_help
        exit 1
        ;;
esac