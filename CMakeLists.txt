cmake_minimum_required(VERSION 3.10)

set(PROJECT_NAME "sdl2_game")
project(${PROJECT_NAME} VERSION 0.1.0)


# Set the C++ standard
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add the SDL2
add_subdirectory(SDL)
add_subdirectory(SDL_mixer)
add_subdirectory(SDL_image)
add_subdirectory(SDL_ttf)

include_directories(SDL/include)
include_directories(SDL_mixer/include)
include_directories(SDL_image/include)
include_directories(SDL_ttf)

# Add source code
set(SRC_PATH "source_code")
add_library (source_lib
    ${SRC_PATH}/Object.cpp
    ${SRC_PATH}/Vocabulary.cpp
    ${SRC_PATH}/Enemy_Bullet.cpp
    ${SRC_PATH}/10_Timer.cpp
    ${SRC_PATH}/Bullet.cpp
    ${SRC_PATH}/Button.cpp
    ${SRC_PATH}/LTexture.cpp
    ${SRC_PATH}/shotgun.cpp
    ${SRC_PATH}/character.cpp
    ${SRC_PATH}/initailize.cpp
    ${SRC_PATH}/Enemy.cpp
)

# Copy the images, fonts, sound effects to the build directory
file(GLOB IMAGES "image/*")
file(COPY ${IMAGES} DESTINATION "./")

file(GLOB FONTS "font/*")
file(COPY ${FONTS} DESTINATION "./")

file(GLOB SE "sound_effect/*")
file(COPY ${SE} DESTINATION "./")

add_executable(${PROJECT_NAME} ${SRC_PATH}/main.cpp)
target_link_libraries(${PROJECT_NAME} source_lib)
target_link_libraries(${PROJECT_NAME} SDL2)
target_link_libraries(${PROJECT_NAME} SDL2_image)
target_link_libraries(${PROJECT_NAME} SDL2_ttf)
target_link_libraries(${PROJECT_NAME} SDL2_mixer)
