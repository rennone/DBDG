#要求するcmakeのバージョン
cmake_minimum_required(VERSION 2.8)

#project name
set(Project django)

PROJECT(${Project})

#c++0x対応オプション
set(CMAKE_CXX_FLAGS_RELEASE "-Wall -O2")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS "-std=c++0x") 

set(CMAKE_BUILD_TYPE release)

set(serial "1.0.0")

include_directories("../include")

link_directories("~/git/DBDG/buildMac/glew/lib")
link_directories("~/git/DBDG/buildMac/glfw3/lib")

# macにはGLUTがデフォルトとで入っているのでそっちを使う
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

#cppファイルをまとめて, Projetへリンク
file(GLOB libSrc ${CMAKE_CURRENT_SOURCE_DIR}/../src/GL/*.cpp)
add_library(${Project} STATIC ${libSrc})

# error OpenGLとかを, django一つにまとめられない
target_link_libraries(${Project} ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES} glfw3 GLEW m)

install(TARGETS ${Project} DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/../lib)
