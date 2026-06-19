cmake_minimum_required(VERSION 3.16)
project(UniversalMediaEngine LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_STANDARD 99)

# Find dependencies
find_package(Qt6 REQUIRED COMPONENTS Widgets Network)
find_package(SDL2 REQUIRED)
find_package(PkgConfig REQUIRED)
pkg_check_modules(FFMPEG REQUIRED libavcodec libavformat libavutil libswscale)

# Include directories
include_directories(${FFMPEG_INCLUDE_DIRS} ${SDL2_INCLUDE_DIRS} .)

# Define the executable
add_executable(universal_player 
    main.cpp 
    interface.cpp 
    visualizer.cpp 
    player_impl.c 
    controls.c
)

# Link libraries
target_link_libraries(universal_player 
    Qt6::Widgets 
    Qt6::Network 
    ${SDL2_LIBRARIES} 
    ${FFMPEG_LIBRARIES}
    # Path to the compiled Rust library (after cargo build --release)
    ${CMAKE_CURRENT_SOURCE_DIR}/target/release/librust_video_core.a 
    pthread 
    dl
)
