cmake_minimum_required(VERSION 3.17)

set(CMAKE_TOOLCHAIN_FILE "${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake"
  CACHE STRING "Vcpkg toolchain file")

set (PROJECT_NAME "r-type_client")
project(r-type_client VERSION 0.1.0 LANGUAGES CXX)

# SFML
# if(MSVC)
# 	if(X64_BITS)
# 		set(LIB_SFML_PATH SFML/VS/x64)
# 	else()
# 		set(LIB_SFML_PATH SFML/VS/x86)
# 	endif()
# elseif(MINGW)
# 	if(X64_BITS)
# 		set(LIB_SFML_PATH SFML/MinGW/x64)
# 	else()
# 		set(LIB_SFML_PATH SFML/MinGW/x86)
# 	endif()
# elseif(APPLE)
# 	set(LIB_SFML_PATH SFML/Clang/x64)
# else()
# 	set(LIB_SFML_PATH SFML/GCC/x64)
# endif()
# if(MINGW OR MSVC)
# 	set(BUILD_SHARED_LIBS FALSE)
# 	set(SFML_USE_STATIC_STD_LIBS TRUE)
# endif()

add_subdirectory(SFML)

# set(LIB_SFML_PATH "SFML/camke")


# set(SFML_STATIC_LIBRARIES FALSE)
# set(SFML_DIR "SFML/")
# find_package(SFML COMPONENTS audio graphics window system REQUIRED)

find_package(Threads REQUIRED)
find_package(Boost REQUIRED)
# IF(Boost_FOUND)
#   INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIRS})
#   LINK_DIRECTORIES(${Boost_LIBRARY_DIRS})
# ENDIF(Boost_FOUND)

# add_definitions(-DBOOST_ASIO_DISABLE_CONCEPTS)
# find_package(SFML COMPONENTS REQUIRED system window graphics PATHS ${LIB_SFML_PATH})
# include_directories(${SFML_INCLUDE_DIR})

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/modules/")
set(OpenGL_GL_PREFERENCE GLVND)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -pthread")

set(CMAKE_CXX_STANDARD 17)

file(GLOB SOURCES "src/*.cpp" "src/*/*.cpp" "src/*/*/*.cpp")
file(GLOB HEADERS "src/*.hpp" "src/*/*.hpp" "src/*/*/*.hpp")

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})
message(STATUS "boost libs: ${Boost_LIBRARIES}")
target_link_libraries(${PROJECT_NAME} PRIVATE ${CMAKE_DL_LIBS} ${Boost_LIBRARIES} Boost::boost sfml-system sfml-audio sfml-graphics sfml-window)

set_property(TARGET r-type_client PROPERTY MSVC_RUNTIME_LIBRARY "")

set_target_properties(r-type_client PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})


if (CMAKE_COMPILER_IS_GNUCXX)
  set(COMPILER_TYPE "gcc")
  add_compile_options(
    "-Wall" "-Wextra" "-pedantic" "-Wpointer-arith" "-fpic"
  )

elseif (MSVC)
  set(COMPILER_TYPE "msvc")
  set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
  add_definitions(-D_ITERATOR_DEBUG_LEVEL=0)
  set(CMAKE_MSVC_RUNTIME_LIBRARY "")
else ()
  set(COMPILER_TYPE "gcc")
  add_compile_options(
    "-Wall" "-Wextra" "-pedantic" "-Wpointer-arith" "-fpic"
  )
endif()

add_subdirectory(POC)
add_subdirectory(server)

install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION .)
install(DIRECTORY "${PROJECT_SOURCE_DIR}/assets/" DESTINATION assets)
include(CPack)