cmake_minimum_required(VERSION 3.12)
project(domik)

set(CMAKE_CXX_STANDARD 11)

set(OPENGL_LIBRARY_DIR "C:/Program Files (x86)/freeglut/lib")
set(GLUT_ROOT_PATH "C:/Program Files (x86)/freeglut")
set(GLUT_INCLUDE_DIR "C:/Program Files (x86)/freeglut/include")

find_package(OPENGL REQUIRED)

find_package(GLUT REQUIRED)

add_executable(domik main.cpp painting.cpp painting.h)

target_link_libraries(domik ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES})

include_directories(${GLUT_INCLUDE_DIR} ${OpenGL_INCLUDE_DIRS})