cmake_minimum_required(VERSION 3.14)
project(Octaedron)

set(CMAKE_CXX_STANDARD 11)

set(OPENGL_LIBRARY_DIR "C:/Program Files (x86)/freeglut/lib")
set(GLUT_ROOT_PATH "C:/Program Files (x86)/freeglut")
set(GLUT_INCLUDE_DIR "C:/Program Files (x86)/freeglut/include")

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

add_executable(Octaedron ohohogangingup.cpp)#main.cpp structures.h )

target_link_libraries(Octaedron ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES})
include_directories(${GLUT_INCLUDE_DIR} ${OPENGL_INCLUDE_DIRS})