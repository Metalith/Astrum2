# CMake entry point
cmake_minimum_required (VERSION 2.6)
project (Astrum2)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -O3 -g")

find_package(OpenGL REQUIRED)
FIND_PACKAGE( Boost 1.63 COMPONENTS REQUIRED )

find_package(GLEW REQUIRED)
if (GLEW_FOUND)
    include_directories(${GLEW_INCLUDE_DIRS})
    link_libraries(${GLEW_LIBRARIES})
endif()

# Compile external dependencies
add_subdirectory (lib)

include_directories(
	${Boost_INCLUDE_DIR}
	lib/glfw-3.2.1/include/GLFW/
	lib/glm-0.9.8.4/glm/
	src/
)

set(ALL_LIBS
	${Boost_LIBRARIES}
	${NOISE_LIBRARY}
	${OPENGL_LIBRARY}
	glfw
	GLEW
	GLU
	GL
)

add_definitions(
	-DTW_STATIC
	-DTW_NO_LIB_PRAGMA
	-DTW_NO_DIRECT3D
	-DGLEW_STATIC
	-D_CRT_SECURE_NO_WARNINGS
)

file(GLOB headers
	"src/common/*.cpp"
	"src/common/*.hpp"
	"src/systems/*.cpp"
	"src/systems/*.hpp"
	"src/engine.cpp"
	"src/engine.hpp"
)

add_executable(main
	src/main.cpp
	${headers}
)
target_link_libraries(main
	${ALL_LIBS}
)

add_custom_command(
	TARGET main POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_CFG_INTDIR}/main${CMAKE_EXECUTABLE_SUFFIX}" "${CMAKE_CURRENT_SOURCE_DIR}/bin"
)
