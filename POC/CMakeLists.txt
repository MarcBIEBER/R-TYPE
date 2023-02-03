cmake_minimum_required(VERSION 3.17)

set (PROJECT_NAME "POC")
project(POC VERSION 1.0 LANGUAGES CXX)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}../")

file(GLOB SOURCES "src/*.cpp" "src/*/*.cpp" "src/*/*/*.cpp")

set(OpenGL_GL_PREFERENCE GLVND)

set(GLOB HEADERS "src/*.hpp" "src/*/*.hpp" "src/*/*/*.hpp")


set(CMAKE_CXX_STANDARD 17)

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})
target_link_libraries(${PROJECT_NAME} sfml-graphics sfml-window sfml-system sfml-audio)


set_property(TARGET POC PROPERTY MSVC_RUNTIME_LIBRARY "")

set_target_properties(POC PROPERTIES RUNTIME_OUTPUT_DIRECTORY ./)
