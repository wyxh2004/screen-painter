cmake_minimum_required(VERSION 3.10)
project(MyProject)

set(CMAKE_C_COMPILER "clang")
set(CMAKE_CXX_COMPILER "clang++")

set(SOURCE_DIRS "./src" "./adaptor/sdlv2")
file(GLOB_RECURSE C_SOURCE_FILES "${SOURCE_DIRS}/*.c")

include_directories(
    "./src"
    "./include"
    "./adaptor/sdlv2"
)

# 添加编译标志
add_definitions(
    "-g"
    "-Wall"
    "-Wextra"
    "-Wno-unused"
    "-ffunction-sections"
    "-fdata-sections"
    "-Dmain=SDL_main"
    "-I${CMAKE_CURRENT_SOURCE_DIR}/src"
    "-I${CMAKE_CURRENT_SOURCE_DIR}/include"
    "-I${CMAKE_CURRENT_SOURCE_DIR}/adaptor/sdlv2"
)

# 添加链接标志
set(LINKER_FLAGS
    "-LC:/lib/SDL2-2.30.2/x86_64-w64-mingw32/lib"
    "-LC:/lib/SDL2_image-2.8.2/x86_64-w64-mingw32/lib"
    "-lmingw32"
    "-lSDL2main"
    "-lSDL2"
    "-lSDL2_image"
    "-mwindows"
)

CMAKE_EXPORT_COMPILE_COMMANDS ON

# 设置输出目录
set(BUILD_DIR "${CMAKE_BINARY_DIR}/build")
set(TARGET "target")

# 创建静态库
add_library(${TARGET} STATIC ${C_SOURCE_FILES})

# 设置生成的库的位置
set_target_properties(${TARGET} PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ${BUILD_DIR})

# 设置链接标志
set_target_properties(${TARGET} PROPERTIES LINK_FLAGS "${LINKER_FLAGS}")

# 安装规则
install(DIRECTORY ./include/ DESTINATION C:/lib/${TARGET}/include)
install(TARGETS ${TARGET} DESTINATION C:/lib/${TARGET}/lib)

# 可选：启用编译命令记录
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)