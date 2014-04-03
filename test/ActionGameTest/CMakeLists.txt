#要求するcmakeのバージョン
cmake_minimum_required(VERSION 2.8)

#project name
set(Project testGame)

PROJECT(${Project})
file(GLOB srcFile ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)

#c++0x対応オプション
set(CMAKE_CXX_FLAGS_RELEASE "-Wall -pedantic -O2")
set(CMAKE_CXX_FLAGS_DEBUG "-g -W")
set(CMAKE_CXX_FLAGS "-std=c++11")

set(CMAKE_BUILD_TYPE release)

link_directories(~/git/DBDG/buildmac/GLUT)
link_directories(~/git/DBDG/buildmac/GLFW)
link_directories(~/git/DBDG/buildmac/GLEW)
link_directories(~/git/DBDG/buildmac/ALUT)
link_directories(~/git/DBDG/buildmac/assimp)

find_package(OPENGL)
include_directories(${OPENGL_INCLUDE_DIRS})
link_directories(${OPENGL_LIBRARY_DIRS})
if(NOT OPENGL_FOUND)
    message(ERROR " OPENGL not found!")
endif(NOT OPENGL_FOUND)

find_package(OPENAL)
include_directories(${OPENAL_INCLUDE_DIRS})
link_directories(${OPENAL_LIBRARY_DIRS})
if(NOT OPENAL_FOUND)
    message(ERROR " OPENAL not found!")
endif(NOT OPENAL_FOUND)

include_directories(~/git/DBDG/include)
link_directories(~/git/DBDG/lib)

add_executable(${Project} ${srcFile})
target_link_libraries(${Project} ${OPENGL_gl_LIBRARY} glut glfw3 glew m)
target_link_libraries(${Project} alut ${OPENAL_LIBRARY})
target_link_libraries(${Project} assimp.3.0.255)
target_link_libraries(${Project} Leap)
target_link_libraries(${Project} django)


