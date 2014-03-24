#要求するcmakeのバージョン
cmake_minimum_required(VERSION 2.8)

#project name
set(Project django)

PROJECT(${Project})

#c++0x対応オプション
set(CMAKE_CXX_FLAGS_RELEASE "-Wall -O2 -DDBDG_MAC_OS -static")
set(CMAKE_CXX_FLAGS_DEBUG "-Wall -g -DDBDG_MAC_OS -static")
set(CMAKE_CXX_FLAGS "-std=c++0x") 

set(CMAKE_BUILD_TYPE release)
set(serial "1.0.0")

include_directories("../include")

#GLEW GLFWのリンク
link_directories("GLFW")
link_directories("GLEW")
link_directories("GLUT")
link_directories("ALUT")
link_directories("assimp")
# macにはGLUTがデフォルトとで入っているのでそっちを使う
#find_package(GLUT)
#include_directories(${GLUT_INCLUDE_DIRS})
#link_directories(${GLUT_LIBRARY_DIRS})
#if(NOT GLUT_FOUND)
#       message(ERROR " GLUT not found!")
#endif(NOT GLUT_FOUND)

#ALUTはfindpackageで見つからなかったので, 手打ち
#set(ALUT_INCLUDE_DIR /usr/local/opt/freealut/include)
#set(ALUT_LIBRARY_DIR /usr/local/opt/freealut/lib)
#include_directories(${ALUT_INCLUDE_DIR})
#link_directories(${ALUT_LIBRARY_DIR})

#aboud OpenGL
find_package(OPENGL)
include_directories(${OPENGL_INCLUDE_DIRS})
link_directories(${OPENGL_LIBRARY_DIRS})
if(NOT OPENGL_FOUND)
    message(ERROR " OPENGL not found!")
endif(NOT OPENGL_FOUND)

#aboud OpenAL
find_package(OPENAL)
include_directories(${OPENAL_INCLUDE_DIRS})
link_directories(${OPENAL_LIBRARY_DIRS})
if(NOT OPENAL_FOUND)
    message(ERROR " OPENAL not found!")
endif(NOT OPENAL_FOUND)

#cppファイルをまとめて, Projetへリンク
file(GLOB src ${CMAKE_CURRENT_SOURCE_DIR}/../src/*.cpp)
file(GLOB alSrc ${CMAKE_CURRENT_SOURCE_DIR}/../src/AL/*.cpp) #AL関連
file(GLOB glSrc ${CMAKE_CURRENT_SOURCE_DIR}/../src/GL/*.cpp) #GL関連
file(GLOB glUtilSrc ${CMAKE_CURRENT_SOURCE_DIR}/../src/GL/util/*.cpp) #glUtil

ADD_LIBRARY(${Project} STATIC ${src} ${glSrc} ${alSrc} ${glUtilSrc})

# TODO OpenGLとかを, django一つにまとめられない => DLLをスタティックにリンクしてない???
TARGET_LINK_LIBRARIES(${Project} glut glfw3 GLEW ${OPENGL_gl_LIBRARY} ${OPENGL_glu_LIBRARY} alut ${OPENAL_LIBRARY} assimp.3.0.255 m)

install(TARGETS ${Project} DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/../lib)
#install(TARGETS ${Project} DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/../test/ActionGameTest)
