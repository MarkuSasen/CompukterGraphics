cmake_minimum_required(VERSION 3.14)
project(Octaedron)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-g")

set(OPENGL_LIBRARY_DIR "C:/Program Files (x86)/freeglut/lib")
set(GLUT_ROOT_PATH "C:/Program Files (x86)/freeglut")
set(GLUT_INCLUDE_DIR "C:/Program Files (x86)/freeglut/include")

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

add_executable(Octaedron ohohogangingup.cpp)#main.cpp structures.h )
add_executable(exe main.cpp)
target_link_libraries(Octaedron ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES})
target_link_libraries(exe ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES})
include_directories(${GLUT_INCLUDE_DIR} ${OPENGL_INCLUDE_DIRS} "D:\\Libs\\CImg-2.8.1" "D:\\Libs\\CImg-2.8.1\\plugins")


