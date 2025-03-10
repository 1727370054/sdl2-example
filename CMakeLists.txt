cmake_minimum_required(VERSION 3.27)
project(SDL2_example)

# 显式设置64位编译
set(CMAKE_SYSTEM_PROCESSOR x86_64)
set(CMAKE_SYSTEM_NAME Windows)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/../bin")

# 显式设置64位库路径
set(SDL2_IMAGE_DIRS "E:/DevelopSoftware/MSYS2/home/loken/SDL2_image-2.8.8/x86_64-w64-mingw32")
set(SDL2_DIRS "E:/DevelopSoftware/MSYS2/home/loken/SDL2-2.32.0/x86_64-w64-mingw32")
set(SDL2_MIXER_DIRS "E:/DevelopSoftware/MSYS2/home/loken/SDL2_mixer-2.8.1/x86_64-w64-mingw32")

# 包含目录
include_directories(
        ${SDL2_IMAGE_DIRS}/include
        ${SDL2_DIRS}/include/SDL2
        ${SDL2_MIXER_DIRS}/include
)

# 链接目录
link_directories(
        ${SDL2_IMAGE_DIRS}/lib
        ${SDL2_DIRS}/lib
        ${SDL2_MIXER_DIRS}/lib
)

# 创建可执行文件
add_executable(${CMAKE_PROJECT_NAME}
        main.cpp
        create_window.cpp
        create_window.h
        sdl_base.cpp
        sdl_base.h
        load_bmp.cpp
        load_bmp.h
        show_image.cpp
        show_image.h
        sound_mixer.cpp
        sound_mixer.h
        sdl_audio.cpp
        sdl_audio.h
        random_yuv.cpp
        random_yuv.h
        read_file_player_yuv.cpp
        read_file_player_yuv.h
        sdl_2_event.cpp
        sdl_2_event.h
)

# 链接库
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE
        SDL2main
        SDL2
        SDL2_image
        SDL2_mixer
)

# Windows主处理定义
target_compile_definitions(${CMAKE_PROJECT_NAME} PRIVATE SDL_MAIN_HANDLED)