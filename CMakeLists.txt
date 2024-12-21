# 指定CMake的最低版本要求
cmake_minimum_required(VERSION 3.10)

# 设置项目名称
project(mydz)

# 设置C++标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 添加可执行文件


add_executable(mydz
        main.cpp
        PipeManager.cpp
        guandao.cpp
        bengzhan.cpp
        Graph.cpp
        jianmo.cpp
)

# 添加头文件目录
target_include_directories(mydz PRIVATE ${PROJECT_SOURCE_DIR})

# 如果需要链接外部库，可以使用target_link_libraries
#target_link_libraries(mydz PRIVATE some_library)
