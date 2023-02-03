cmake_minimum_required(VERSION 3.17)

set (PROJECT_NAME "server_binary")
project(server_binary VERSION 1.0 LANGUAGES CXX)
find_package(Threads REQUIRED)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}../")

file(GLOB SOURCES "src/*.cpp" "src/*/*.cpp" "*.cpp")

set(OpenGL_GL_PREFERENCE GLVND)

set(HEADERS
    server.hpp
    )


set(CMAKE_CXX_STANDARD 17)

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})
target_link_libraries(${PROJECT_NAME} sfml-graphics sfml-window sfml-system sfml-audio Boost::boost)


set_property(TARGET server_binary PROPERTY MSVC_RUNTIME_LIBRARY "")

set_target_properties(server_binary PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})

install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION .)
