#要求するcmakeのバージョン
cmake_minimum_required(VERSION 2.8)

#project name
set(Project testGame)

PROJECT(${Project})
file(GLOB srcFile ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)

#c++0x対応オプション
set(CMAKE_CXX_FLAGS_RELEASE "-Wall -pedantic -O2")
set(CMAKE_CXX_FLAGS_DEBUG "-g -DDEBUG")
set(CMAKE_CXX_FLAGS "-std=c++0x")


set(CMAKE_BUILD_TYPE release)

#about GLUT
find_package(GLUT)
include_directories(${GLUT_INCLUDE_DIRS})
link_directories(${GLUT_LIBRARY_DIRS})
if(NOT GLUT_FOUND)
       message(ERROR " GLUT not found!")
endif(NOT GLUT_FOUND)

#aboud OpenGL
find_package(OPENGL)
include_directories(${OPENGL_INCLUDE_DIRS})
link_directories(${OPENGL_LIBRARY_DIRS})

if(NOT OPENGL_FOUND)
    message(ERROR " OPENGL not found!")
endif(NOT OPENGL_FOUND)

find_package(GLEW)
link_directories(${GLEW_LIBRARY_DIRS})

find_package(GLFW)
link_directories(${GLFW_LIBRARY_DIRS})


find_package(OPENAL)
link
# freeAlut
link_directories(/usr/local/opt/freealut/include)

find_package(OPENAL)
include_directories(${OPENAL_INCLUDE_DIRS})
link_directories(${OPENAL_LIBRARY_DIRS})

include_directories(~/git/DBDG/include)
link_directories(~/git/DBDG/lib)

add_executable(${Project} ${srcFile})
target_link_libraries(${Project} ${OPENGL_LIBRARY} ${GLUT_LIBRARY} ${GLFW_LIBRARY} ${GLEW_LIBRARY} m)

#alutを先にリンクしないといけない
target_link_libraries(${Project} alut ${OPENAL_LIBRARY})

target_link_libraries(${Project} django)

#デバッグ用に, テスト側でライブラリをコンパイル
#file(GLOB libSrc ${CMAKE_CURRENT_SOURCE_DIR}/../src/GL/*.cpp)
#add_library(django STATIC ${libSrc})
#target_link_libraries(django ${OPENGL_LIBRARY} ${GLUT_LIBRARY} glfw3 ${GLEW_LIBRARY} m)


