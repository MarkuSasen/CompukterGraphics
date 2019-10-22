cmake_minimum_required(VERSION 3.14)
project(tetris)

set(CMAKE_CXX_STANDARD 11)

set(OPENGL_LIBRARY_DIR "C:/Program Files (x86)/freeglut/lib")
set(GLUT_ROOT_PATH "C:/Program Files (x86)/freeglut")
set(GLUT_INCLUDE_DIR "C:/Program Files (x86)/freeglut/include")



find_package(GLUT REQUIRED)
include_directories(${GLUT_INCLUDE_DIR})

find_package(OpenGL REQUIRED)
include_directories(${OpenGL_INCLUDE_DIRS})

add_executable(tetris main.cpp tetris.cpp)

target_link_libraries(tetris ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES})


