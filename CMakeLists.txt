# CMake entry point
cmake_minimum_required (VERSION 2.6)
project (Astrum2)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -O0 -g -Wall")

find_package(OpenGL REQUIRED)
FIND_PACKAGE( Boost 1.63 COMPONENTS REQUIRED )

find_library(NOISE_LIBRARY
	NAMES libnoise.so
	PATHS /usr/lib /usr/local/lib
)

find_path(NOISE_INCLUDE_DIR
	NAMES libnoise/noise.h noise/noise.h
	PATHS /usr/include /usr/local/include
)

# Compile external dependencies
add_subdirectory (lib)

include_directories(
	${Boost_INCLUDE_DIR}
	${NOISE_INCLUDE_DIR}
	lib/glfw-3.2.1/include/GLFW/
	lib/glm-0.9.8.4/glm/
	lib/glew-2.1.0/include/
	src/
)

set(ALL_LIBS
	${Boost_LIBRARIES}
	${NOISE_LIBRARY}
	${OPENGL_LIBRARY}
	glfw
	GLEW_210
)

add_definitions(
	-DTW_STATIC
	-DTW_NO_LIB_PRAGMA
	-DTW_NO_DIRECT3D
	-DGLEW_STATIC
	-D_CRT_SECURE_NO_WARNINGS
)

file(GLOB headers
	src/common/*.cpp
	src/common/*.hpp
	src/systems/*.cpp
	src/systems/*.hpp
	src/components/*.cpp
	src/components/*.hpp
	src/engine.cpp
	src/engine.hpp
)

add_executable(main
	src/main.cpp
	${headers}
)

target_link_libraries(main
	${ALL_LIBS}
)
